#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CAMINHO 1001

#define TAM_MAPA 100
#define ARQ_MAPA "/mapa.txt"

#define CEL_VAZIA ' '
#define CEL_PARED '#'
#define CEL_COMID '*'
#define CEL_DINHR '$'
#define CEL_CDCBR '>'
#define CEL_CBCBR 'v'
#define CEL_CECBR '<'
#define CEL_CCCBR '^'
#define CEL_COCBR 'o'

#define JOG_EST_T 0

// JOGO
typedef struct {
    tMapa mapa;
    int pontuacao;
    int estado;
} tJogo;

tJogo inicializaJogo(char const caminhoBase[]);
int acabou(tJogo jogo);
void imprimeJogo(tJogo jogo);
// FIM JOGO

// MAPA
typedef struct {
    int nLinhas;
    int mColunas;
    char arr[TAM_MAPA][TAM_MAPA];
} tMapa;

tMapa leMapa(char const caminhoBase[]);
void imprimeMapa(tMapa mapa);
// FIM MAPA

void combinaCaminho(char dest[], char const base[], char const arq[]);

int main(int argc, char const *argv[]) {
    if (argc <= 1) {
        printf("%s\n", "ERRO: O diretorio de arquivos de configuracao nao foi informado");
        return EXIT_FAILURE;
    }
    
    char const caminhoBase[TAM_CAMINHO];
    strcpy(caminhoBase, argv[1]);
    

    tJogo jogo = inicializaJogo(caminhoBase);
    do {

    } while (!acabou(jogo));

    return EXIT_SUCCESS;
}

// JOGO
tJogo inicializaJogo(char const caminhoBase[]) {
    tMapa mapa = leMapa(caminhoBase);

    tJogo jogo = { mapa, 0, 0 };
    return jogo;
}

int acabou(tJogo jogo) {
    return jogo.estado != JOG_EST_T;
}

void imprimeJogo(tJogo jogo) {
    imprimeMapa(jogo.mapa);
    printf("Pontuacao: %d\n", jogo.pontuacao);
}
// FIM JOGO

// MAPA
tMapa leMapa(char const caminhoBase[]) {
    char caminhoMapa[TAM_CAMINHO];
    combinaCaminho(caminhoMapa, caminhoBase, ARQ_MAPA);
    FILE *arq = fopen(caminhoMapa, "r");

    if (arq == NULL){
        printf("ERRO: O arquivo de configuração do mapa (%s) nao foi encontrado\n", caminhoMapa);
        exit(EXIT_FAILURE);
    }
    
    int n, m;
    fscanf(arq, "%d %d%*c", &n, &m);
    tMapa mapa = { n, m };

    int i;
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            char curr;
            fscanf(arq, "%c", &curr);
            mapa.arr[i][j] = curr;
        }
        fscanf(arq, "%*c");
    }
    fclose(arq);

    return mapa;
}

void imprimeMapa(tMapa mapa) {
    int i;
    for (i = 0; i < mapa.nLinhas; i++) {
        int j;
        for (j = 0; j < mapa.mColunas; j++) {
            printf("%c", mapa.arr[i][j]);
        }
        printf("%c", '\n');
    }
}
// FIM MAPA

void combinaCaminho(char dest[], char const base[], char const arq[]) {
    strcpy(dest, base);
    strcat(dest, arq);
}
