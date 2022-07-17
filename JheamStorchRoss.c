#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CAMINHO 1001

#define TAM_MAPA 100
#define ARQ_MAPA "/mapa.txt"

void combinaCaminho(char dest[], char const base[], char const arq[]);

// MAPA
typedef struct {
    char mapa[TAM_MAPA];
    int nLinhas;
    int mColunas;
} tMapa;

tMapa leMapa(char const caminhoBase[]);
// FIM MAPA

// JOGO
typedef struct {
    tMapa mapa;
    
} tJogo;

tJogo inicializaJogo(char const caminhoBase[]);
// FIM JOGO

int main(int argc, char const *argv[]) {
    if (argc <= 1) {
        printf("%s\n", "ERRO: O diretorio de arquivos de configuracao nao foi informado");
        return EXIT_FAILURE;
    }
    
    char const *caminhoBase = argv[1];

    tJogo jogo = inicializaJogo(caminhoBase);

    return EXIT_SUCCESS;
}

void combinaCaminho(char dest[], char const base[], char const arq[]) {
    strcpy(dest, base);
    strcat(dest, arq);
}

// MAPA
tMapa leMapa(char const caminhoBase[]) {
    char caminhoMapa[TAM_CAMINHO];
    combinaCaminho(caminhoMapa, caminhoBase, ARQ_MAPA);
    FILE *arq = fopen(caminhoMapa, "r");

    if (arq == NULL){
        printf("ERRO: O arquivo de configuração do mapa (%s) nao foi encontrado\n", caminhoMapa);
        exit(EXIT_FAILURE);
    }
    
}
// FIM MAPA

// JOGO
tJogo inicializaJogo(char const caminhoBase[]) {
    tMapa mapa = leMapa(caminhoBase);

    tJogo jogo = { mapa };
    return jogo;
}
// FIM JOGO
