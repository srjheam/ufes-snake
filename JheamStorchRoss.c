#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CAMINHO 1001

void combinaCaminho(char dest[], char base[], char arq[]);

// POSICAO
typedef struct {
    int i;
    int j;
} tPosicao;

tPosicao inicializaPosicao(int i, int j);
int adquireI(tPosicao pos);
int adquireJ(tPosicao pos);
tPosicao alteraPeloDelta(tPosicao pos, int dI, int dJ);
// FIM POSICAO

// FILA
#define TAM_FILA 100

typedef struct {
    int tam;
    tPosicao vet[TAM_FILA];
} tFila;

tFila inicializaFila();
tFila enfileira(tFila fila, tPosicao pos);
tFila desenfileira(tFila fila);
tPosicao adquirePos(tFila fila, int index);
// FIM FILA

// COBRA
#define CBR_DIR_N 0
#define CBR_DIR_L 1
#define CBR_DIR_S 2
#define CBR_DIR_O 3

typedef struct {
    tFila corpo;
    int direcaoCabeca;
} tCobra;

tCobra inicializaCobra(tPosicao posCab, char direcaoInicial);
tPosicao adquireCabeca(tCobra cobra);
int adquireDirecao(tCobra cobra);
tCobra defineDirecao(tCobra cobra, int direcao);
// FIM COBRA

// MAPA
#define TAM_MAPA 100
#define ARQ_MAPA "/mapa.txt"

#define CEL_VAZIA ' '
#define CEL_PARED '#'
#define CEL_TUNEL '@'
#define CEL_COMID '*'
#define CEL_DINHR '$'
#define CEL_CBRCD '>'
#define CEL_CBRCB 'v'
#define CEL_CBRCE '<'
#define CEL_CBRCC '^'
#define CEL_CBRCO 'o'
#define CEL_CBRCM 'X'

#define MOV_CBRCT 'c'
#define MOV_CBRHO 'h'
#define MOV_CBRAH 'a'

typedef struct {
    int nLinhas;
    int mColunas;
    char vet[TAM_MAPA][TAM_MAPA];
    tCobra cobra;
    tFila tuneis;
    int qtdDinheiro;
    int qtdComida;
} tMapa;

tMapa leMapa(char caminhoBase[]);
char adquireCel(tMapa mapa, tPosicao pos);
int estaDentroLimite(tMapa mapa, tPosicao pos);
tPosicao transformaPosicaoValida(tMapa mapa, tPosicao posicao);
tMapa fazMovimento(tMapa mapa, char movimento);
void imprimeMapa(tMapa mapa);
// FIM MAPA

// JOGO
#define JOG_EST_T 0
#define JOG_EST_V 1
#define JOG_EST_D 2

typedef struct {
    tMapa mapa;
    int pontuacao;
    int estado;
} tJogo;

tJogo inicializaJogo(char caminhoBase[]);
int acabou(tJogo jogo);
tJogo fazRodada(tJogo jogo, char movimento);
void imprimeJogo(tJogo jogo);
// FIM JOGO

int main(int argc, char const *argv[]) {
    if (argc <= 1) {
        printf("%s\n", "ERRO: O diretorio de arquivos de configuracao nao foi informado");
        return EXIT_FAILURE;
    }
    
    char caminhoBase[TAM_CAMINHO];
    strcpy(caminhoBase, argv[1]);
    
    tJogo jogo = inicializaJogo(caminhoBase);
    do {
        char movimento;
        scanf("%c%*c", &movimento);
        
        jogo = fazRodada(jogo, movimento);

        printf("%c", '\n');
        printf("Estado do jogo apos o movimento '%c':\n", movimento);
        imprimeJogo(jogo);
    } while (!acabou(jogo));

    return EXIT_SUCCESS;
}

// JOGO
tJogo inicializaJogo(char caminhoBase[]) {
    tMapa mapa = leMapa(caminhoBase);

    tJogo jogo = { mapa, 0, 0 };
    return jogo;
}

int acabou(tJogo jogo) {
    return jogo.estado != JOG_EST_T;
}

tJogo fazRodada(tJogo jogo, char movimento) {
    jogo.mapa = fazMovimento(jogo.mapa, movimento);

    return jogo;
}

void imprimeJogo(tJogo jogo) {
    imprimeMapa(jogo.mapa);
    printf("Pontuacao: %d\n", jogo.pontuacao);

    if (!acabou(jogo)) {
        return;
    }

    switch (jogo.estado) {
        case JOG_EST_V:
            printf("%s", "Você venceu!\n");
            break;
        
        case JOG_EST_D:
            printf("%s", "Game over!\n");
            break;
    }

    printf("Pontuacao final: %d\n", jogo.pontuacao);
}
// FIM JOGO

// MAPA
tMapa leMapa(char caminhoBase[]) {
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
    mapa.qtdComida = 0;
    mapa.qtdDinheiro = 0;
    mapa.tuneis = inicializaFila();

    int i;
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            char curr;
            fscanf(arq, "%c", &curr);
            mapa.vet[i][j] = curr;

            if (curr == CEL_VAZIA || curr == CEL_PARED) {
                continue;
            }

            switch (curr) {
                case CEL_CBRCB:
                case CEL_CBRCC:
                case CEL_CBRCD:
                case CEL_CBRCE:
                    mapa.cobra = inicializaCobra(inicializaPosicao(i, j), curr);
                    break;

                case CEL_COMID:
                    mapa.qtdComida++;
                    break;

                case CEL_DINHR:
                    mapa.qtdDinheiro++;
                    break;

                case CEL_TUNEL:
                    mapa.tuneis = enfileira(mapa.tuneis, inicializaPosicao(i, j));
                    break;
            }
        }
        fscanf(arq, "%*c");
    }
    fclose(arq);

    return mapa;
}

char adquireCel(tMapa mapa, tPosicao pos) {
    return mapa.vet[pos.i, pos.j];
}

int estaDentroLimite(tMapa mapa, tPosicao pos) {
    return pos.i >= 0
        && pos.i < mapa.nLinhas
        && pos.j >= 0
        && pos.j < mapa.mColunas;
}

tPosicao transformaPosicaoValida(tMapa mapa, tPosicao pos) {
    if (estaDentroLimite(mapa, pos) && adquireCel(mapa, pos) != CEL_TUNEL) {
        return pos;
    }
    
    // corrige a posicao para dentro dos limites
    pos = inicializaPosicao(abs((mapa.nLinhas + adquireI(pos)) % mapa.nLinhas), adquireJ(pos));
    pos = inicializaPosicao(adquireI(pos), abs((mapa.mColunas + adquireJ(pos)) % mapa.mColunas));
    


    return transformaPosicaoValida(mapa, pos);
}

tMapa fazMovimento(tMapa mapa, char movimento) {
    int direcao = adquireDirecao(mapa.cobra);

    // adquire os respectivos deltas para o que tende
    // a ser a posicao apos dado movimento e define a
    // nova direcao da cobra
    int dI = 0, dJ = 0;
    if (movimento == MOV_CBRCT) {
        if (direcao == CBR_DIR_N) {
            dI = -1;
        }
        else if (direcao == CBR_DIR_L) {
            dJ = 1;
        }
        else if (direcao == CBR_DIR_S) {
            dI = 1;
        }
        else if (direcao == CBR_DIR_O) {
            dJ = -1;
        }
    }
    else if (movimento == MOV_CBRHO) {
        if (direcao == CBR_DIR_N) {
            dJ = 1;
        }
        else if (direcao == CBR_DIR_L) {
            dI = 1;
        }
        else if (direcao == CBR_DIR_S) {
            dJ = -1;
        }
        else if (direcao == CBR_DIR_O) {
            dI = -1;
        }

        mapa.cobra = defineDirecao(mapa.cobra, );
    }
    else if (movimento == MOV_CBRAH) {
        if (direcao == CBR_DIR_N) {
            dJ = -1;
        }
        else if (direcao == CBR_DIR_L) {
            dI = -1;
        }
        else if (direcao == CBR_DIR_S) {
            dJ = 1;
        }
        else if (direcao == CBR_DIR_O) {
            dI = 1;
        }
    }

    tPosicao posDest = adquireCabeca(mapa.cobra);
    posDest = alteraPeloDelta(posDest, dI, dJ);

    posDest = transformaPosicaoValida(mapa, posDest);
    
}

void imprimeMapa(tMapa mapa) {
    int i;
    for (i = 0; i < mapa.nLinhas; i++) {
        int j;
        for (j = 0; j < mapa.mColunas; j++) {
            printf("%c", mapa.vet[i][j]);
        }
        printf("%c", '\n');
    }
}
// FIM MAPA

// COBRA
tCobra inicializaCobra(tPosicao posCab, char direcaoInicial) {
    tCobra cobra;
    cobra.corpo = inicializaFila();
    enfileira(cobra.corpo, posCab);

    // transforma a representacao da cabeca da cobra, em char,
    // na sua respectiva representacao no formato CBR_DIR
    switch (direcaoInicial) {
        case CEL_CBRCD:
            cobra.direcaoCabeca = CBR_DIR_L;
            break;
        
        case CEL_CBRCB:
            cobra.direcaoCabeca = CBR_DIR_S;
            break;
        
        case CEL_CBRCE:
            cobra.direcaoCabeca = CBR_DIR_O;
            break;
        
        case CEL_CBRCC:
            cobra.direcaoCabeca = CBR_DIR_N;
            break;
    }
    
    return cobra;
}

tPosicao adquireCabeca(tCobra cobra) {
    return adquirePos(cobra.corpo, 0);
}

int adquireDirecao(tCobra cobra) {
    return cobra.direcaoCabeca;
}

tCobra defineCobra(tCobra cobra, int direcao) {
    cobra.direcaoCabeca = direcao;
    return cobra;
}
// FIM COBRA

// LISTA
tFila inicializaFila() {
    tFila fila = { 0 };
    return fila;
}

tFila enfileira(tFila fila, tPosicao pos) {
    int i;
    for (i = fila.tam; i > 0; i--) {
        fila.vet[i] = fila.vet[i - 1];
    }
    fila.vet[0] = pos;
    fila.tam++;

    return fila;
}

tFila desenfileira(tFila fila) {
    fila.tam--;
    return fila;
}

tPosicao adquirePos(tFila fila, int index) {
    if (index < 0 || index >= fila.tam) {
        index = fila.tam - 1;
    }

    return fila.vet[index];
}
// FIM LISTA

// POSICAO
tPosicao inicializaPosicao(int i, int j) {
    tPosicao pos = { i, j };
    return pos;
}

int adquireI(tPosicao pos) {
    return pos.i;
}

int adquireJ(tPosicao pos) {
    return pos.j;
}

tPosicao alteraPeloDelta(tPosicao pos, int dI, int dJ) {
    pos.i += dI;
    pos.j += dJ;

    return pos;
}
// FIM POSICAO

void combinaCaminho(char dest[], char base[], char arq[]) {
    strcpy(dest, base);
    strcat(dest, arq);
}
