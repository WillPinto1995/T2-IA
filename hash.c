#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

#define SEED 5381

// Função hash DJB2
uint32_t hashf(const char *str, uint32_t seed) {
    uint32_t hash = seed;
    while (*str) {
        hash = ((hash << 5) + hash) + (unsigned char)(*str++);
    }
    return hash;
}

// Segunda função para hash duplo (deve ser ímpar)
uint32_t hashf2(const char *str, uint32_t seed) {
    uint32_t h = 0;
    while (*str) {
        h = (h * 131) + *str++;
    }
    h = (h == 0) ? 1 : h;
    if (h % 2 == 0) h++;
    return h;
}

tcep_data *aloca_cep_data(const char *prefix, const char *city, const char *state) {
    tcep_data *dado = malloc(sizeof(tcep_data));
    strncpy(dado->cep_prefix, prefix, 6);
    strncpy(dado->city, city, 50);
    strncpy(dado->state, state, 3);
    return dado;
}

char *get_key(void *reg) {
    return ((tcep_data *)reg)->cep_prefix;
}

thash *hash_constroi(int nbuckets, int hash_type, float load_factor_threshold, char *(*get_key)(void *)) {
    thash *h = malloc(sizeof(thash));
    h->table = calloc(nbuckets, sizeof(void *));
    h->deleted = calloc(nbuckets, sizeof(int));
    h->max = nbuckets;
    h->size = 0;
    h->initial_buckets = nbuckets;
    h->load_factor_threshold = load_factor_threshold;
    h->hash_type = hash_type;
    h->get_key = get_key;
    return h;
}

void hash_apaga(thash *h) {
    for (int i = 0; i < h->max; i++) {
        if (h->table[i] && !h->deleted[i]) {
            free(h->table[i]);
        }
    }
    free(h->table);
    free(h->deleted);
    free(h);
}

int hash_insere(thash *h, void *bucket) {
    if (((float)(h->size + 1) / h->max) > h->load_factor_threshold) {
        hash_resize(h);
    }

    char *key = h->get_key(bucket);
    uint32_t hash1 = hashf(key, SEED) % h->max;
    uint32_t hash2 = (h->hash_type == 1) ? hashf2(key, SEED) : 1;

    int pos = hash1;
    int i = 0;
    while (h->table[pos] && !h->deleted[pos]) {
        i++;
        pos = (hash1 + i * hash2) % h->max;
    }

    h->table[pos] = bucket;
    h->deleted[pos] = 0;
    h->size++;
    return 1;
}

void *hash_busca(thash *h, const char *key) {
    uint32_t hash1 = hashf(key, SEED) % h->max;
    uint32_t hash2 = (h->hash_type == 1) ? hashf2(key, SEED) : 1;

    int pos = hash1;
    int i = 0;
    while (h->table[pos]) {
        if (!h->deleted[pos] && strcmp(h->get_key(h->table[pos]), key) == 0) {
            return h->table[pos];
        }
        i++;
        pos = (hash1 + i * hash2) % h->max;
    }
    return NULL;
}

void *hash_remove(thash *h, const char *key) {
    uint32_t hash1 = hashf(key, SEED) % h->max;
    uint32_t hash2 = (h->hash_type == 1) ? hashf2(key, SEED) : 1;

    int pos = hash1;
    int i = 0;
    while (h->table[pos]) {
        if (!h->deleted[pos] && strcmp(h->get_key(h->table[pos]), key) == 0) {
            h->deleted[pos] = 1;
            h->size--;
            return h->table[pos];
        }
        i++;
        pos = (hash1 + i * hash2) % h->max;
    }
    return NULL;
}

void hash_resize(thash *h) {
    int old_max = h->max;
    void **old_table = h->table;
    int *old_deleted = h->deleted;

    int new_max = 2 * old_max;
    h->table = calloc(new_max, sizeof(void *));
    h->deleted = calloc(new_max, sizeof(int));
    h->max = new_max;
    h->size = 0;

    for (int i = 0; i < old_max; i++) {
        if (old_table[i] && !old_deleted[i]) {
            hash_insere(h, old_table[i]);
        }
    }

    free(old_table);
    free(old_deleted);
}


