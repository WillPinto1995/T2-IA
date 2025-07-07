#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define MAX_CEPS 10000

// Função para carregar dados do arquivo para um vetor
int carregar_dados(const char *arquivo, tcep_data **vetor) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    char linha[200];
    int count = 0;
    while (fgets(linha, sizeof(linha), fp) && count < MAX_CEPS) {
        char cep[6], cidade[50], estado[3];
        if (sscanf(linha, "%5[^;];%49[^;];%2s", cep, cidade, estado) == 3) {
            vetor[count++] = aloca_cep_data(cep, cidade, estado);
        }
    }

    fclose(fp);
    return count;
}

// Função de busca genérica para medir tempo com gprof
void busca_simples(thash *h, tcep_data **vetor, int total) {
    for (int i = 0; i < total; i++) {
        hash_busca(h, vetor[i]->cep_prefix);
    }
}

void busca_dupla(thash *h, tcep_data **vetor, int total) {
    for (int i = 0; i < total; i++) {
        hash_busca(h, vetor[i]->cep_prefix);
    }
}

int main() {
    tcep_data *dados[MAX_CEPS];
    int total = carregar_dados("ceps_formatados.txt", dados);
    if (total == 0) {
        printf("Nenhum dado carregado!\n");
        return 1;
    }

    printf("Total de CEPs carregados: %d\n", total);

    // Teste com hash simples
    thash *hash_s = hash_constroi(6100, 0, 0.9, get_key);
    for (int i = 0; i < total; i++) {
        hash_insere(hash_s, dados[i]);
    }
    busca_simples(hash_s, dados, total);
    hash_apaga(hash_s);

    // Alocar novamente porque os ponteiros foram liberados
    for (int i = 0; i < total; i++) {
        dados[i] = aloca_cep_data(dados[i]->cep_prefix, dados[i]->city, dados[i]->state);
    }

    // Teste com hash duplo
    thash *hash_d = hash_constroi(6100, 1, 0.9, get_key);
    for (int i = 0; i < total; i++) {
        hash_insere(hash_d, dados[i]);
    }
    busca_dupla(hash_d, dados, total);
    hash_apaga(hash_d);

    return 0;
}
