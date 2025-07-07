#ifndef HASH_H
#define HASH_H

#include <stdint.h>

typedef struct {
    char cep_prefix[6];  // 5 dígitos + '\0'
    char city[50];
    char state[3];       // 2 letras + '\0'
} tcep_data;

typedef struct thash {
    void **table;
    int *deleted;
    int max;
    int size;
    int hash_type;                 // 0 = simples, 1 = duplo
    float load_factor_threshold;  // ex: 0.7
    int initial_buckets;

    char *(*get_key)(void *);
} thash;

// Funções principais
thash *hash_constroi(int nbuckets, int hash_type, float load_factor_threshold, char *(*get_key)(void *));
void hash_apaga(thash *h);
int hash_insere(thash *h, void *bucket);
void *hash_busca(thash *h, const char *key);
void *hash_remove(thash *h, const char *key);
void hash_resize(thash *h);

// Funções de hash
uint32_t hashf(const char *str, uint32_t seed);
uint32_t hashf2(const char *str, uint32_t seed); // para hash duplo

// Helpers
tcep_data *aloca_cep_data(const char *prefix, const char *city, const char *state);
char *get_key(void *reg);

#endif



