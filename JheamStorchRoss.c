/**
 * @file JheamStorchRoss.c
 * @author Jheam Storch Ross
 * @brief Jogo snake contruido em C
 * @version 1.0
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Contem o tamanho maximo para um caminho suportado pelo programa
 * 
 */
#define TAM_CAMINHO 1001

/**
 * @brief Combina os caminhos @p cmnh1 e @p cmnh2 no caminho @p dest
 * 
 * @param dest  Caminho que resulta da combinacao dos caminhos @p cmnh1 e @p cmnh2
 * @param cmnh1 Caminho que precedera o caminho @p cmnh2
 * @param cmnh2 Caminho que sucedera o caminho @p cmnh1
 */
void combinaCaminho(char dest[], char cmnh1[], char cmnh2[]);

// POSICAO

/**
 * @brief Representa uma posicao em uma matriz bidimensional
 * 
 */
typedef struct {
    int i; ///< Indica sua posicao na i-esima linha
    int j; ///< Indica sua posicao na j-esima coluna
} tPosicao;
/**
 * @brief Inicializa uma struct de tipo @ref tPosicao
 * 
 * @param i Linha da posicao
 * @param j Coluna da posicao
 * @return tPosicao Uma nova instancia de @ref tPosicao na @p i -esima linha e @p j -esima coluna
 * @related tPosicao
 */
tPosicao inicializaPosicao(int i, int j);
/**
 * @brief Adquire a linha I representada na @ref tPosicao @p pos
 * 
 * @param pos A @ref tPosicao
 * @return int A linha i da @ref tPosicao @p pos
 * @related tPosicao
 */
int adquireI(tPosicao pos);
/**
 * @brief Adquire a coluna J representada na @ref tPosicao @p pos
 * 
 * @param pos A @ref tPosicao
 * @return int A coluna J da @ref tPosicao @p pos
 * @related tPosicao
 */
int adquireJ(tPosicao pos);
/**
 * @brief Altera as coordenadas da @ref tPosicao @p pos pelos deltas @p dI e @p dJ
 * 
 * @param pos A @ref tPosicao
 * @param dI O delta que modificara a linha I
 * @param dJ O delta que modificara a coluna J
 * @return tPosicao A nova @ref tPosicao @p pos dados os deltas @p dI e @p dJ
 * @related tPosicao
 */
tPosicao alteraPeloDelta(tPosicao pos, int dI, int dJ);
/**
 * @brief Revela o proximo avanco/salto dada um @p direcao a partir de uma @ref tPosicao @p pos
 * 
 * @param pos A @ref tPosicao
 * @param direcao A direcao para a qual sera o avanco
 * @return tPosicao A @ref tPosicao resultado desse avanco
 * @related tPosicao
 */
tPosicao avancaNaDirecao(tPosicao pos, int direcao);
/**
 * @brief Compara duas @ref tPosicao @p pos1 e @p pos2
 * 
 * @param pos1 A @ref tPosicao que sera comparada com @p pos2
 * @param pos2 A @ref tPosicao que sera comparada com @p pos1
 * @return int Verdadeiro, caso sejam iguais; do contrário, falso
 * @related tPosicao
 */
int comparaPos(tPosicao pos1, tPosicao pos2);

// FIM POSICAO
// FILA

/**
 * @brief Contem o tamanho maximo de uma @ref tFila
 * @related tFila
 */
#define TAM_FILA 100
/**
 * @brief Representa uma estrultura de dados fila, de fluxo FIFO
 * 
 */
typedef struct {
    int tam; ///< Numero de elementos armazenados pela @ref tFila no momento
    tPosicao vet[TAM_FILA]; ///< Vetor de elementos armazenados pela @ref tFila
} tFila;
/**
 * @brief Inicializa uma struct de tipo @ref tFila
 * 
 * @return tFila Uma nova instancia de @ref tFila
 * @related tFila
 */
tFila inicializaFila();
/**
 * @brief Adquire o tamanho da @ref tFila @p fila
 * 
 * @param fila A @ref tFila
 * @return int O numero de elementos armazenados pela @ref tFila @p fila
 * @related tFila
 */
int adquireTam(tFila fila);
/**
 * @brief Adquire o elemento enfileirado no dado @p index
 * 
 * @param fila A @ref tFila
 * @param index O index no qual sera adquirido o elemento
 * @return tPosicao A @ref tPosicao no indice @p index na fila; caso esteja fora dos limites, retorna o elemento no final da fila
 * @related tFila
 */
tPosicao adquireElem(tFila fila, int index);
/**
 * @brief Adiciona um elemento no inicio da @ref tFila @p fila
 * 
 * @param fila A @ref tFila
 * @param pos O elemento @ref tPos que sera adicionado
 * @return tFila A @p fila com o novo elemento
 * @related tFila
 */
tFila enfileira(tFila fila, tPosicao pos);
/**
 * @brief Remove um elemento no final da @ref tFila @p fila
 * 
 * @param fila A @ref tFila
 * @return tFila A @p fila sem o ultimo elemento
 * @related tFila
 */
tFila desenfileira(tFila fila);

// FIM FILA
// COBRA

/**
 * @brief A direcao da cobra para o norte
 * @related tCobra
 */
#define CBR_DIR_N 0
/**
 * @brief A direcao da cobra para o leste
 * @related tCobra
 */
#define CBR_DIR_L 1
/**
 * @brief A direcao da cobra para o sul
 * @related tCobra
 */
#define CBR_DIR_S 2
/**
 * @brief A direcao da cobra para o oeste
 * @related tCobra
 */
#define CBR_DIR_O 3
/**
 * @brief O estado que indica que a cobra esta morta
 * @related tCobra
 */
#define CBR_EST_M 0
/**
 * @brief O estado que indica que a cobra esta viva
 * @related tCobra
 */
#define CBR_EST_V 1
/**
 * @brief Representa a cobra no mapa
 * 
 */
typedef struct {
    tFila corpo; ///< Uma @ref tFila que contem todas as partes do corpo
    int direcaoCabeca; ///< Indica a direcao atual da cabeca
    char devorado; ///< Contem a ultima celula devorada pela cobra (estado dessincronizado com o mapa)
    int estado; ///< Representa o estado atual da cobra, seja vivo ou morto
} tCobra;
/**
 * @brief Inicializa uma struct do tipo @ref tCobra com a cabeca @p posCab e direcao baseada em @p direcaoInicial
 * 
 * @param posCab A posicao da cabeca da @ref tCobra
 * @param direcaoInicial A representacao em @ref char da cabeca da cobra que definira a direcaoCabeca da @ref tCobra
 * @return tCobra Uma nova instancia da @ref tCobra
 * @related tCobra
 */
tCobra inicializaCobra(tPosicao posCab, char direcaoInicial);
/**
 * @brief Adquire a @ref tPosicao da cabeca da @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return tPosicao A posicao da cabeca da @p cobra
 * @related tCobra
 */
tPosicao adquireCabeca(tCobra cobra);
/**
 * @brief Adquire a @ref tFila que contem todo o corpo da @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return tFila As posicoes de todo o corpo da @ref tCobra
 * @related tCobra
 */
tFila adquireCorpo(tCobra cobra);
/**
 * @brief Adquire a direcao da @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return int A direcao da @ref tCobra
 * @related tCobra
 */
int adquireDirecao(tCobra cobra);
/**
 * @brief Define @p direcao como a direcao para a @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @param direcao A nova direcao
 * @return tCobra A @ref tCobra com a nova direcao
 * @related tCobra
 */
tCobra defineDirecao(tCobra cobra, int direcao);
/**
 * @brief Adquire a ultima celula devorada pela @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return char A celula devorada pela @ref tCobra
 * @related tCobra
 */
char adquireDevorado(tCobra cobra);
/**
 * @brief Adquire o estado atual da @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return int O estado, sendo @ref CBR_EST_V para VIVA; @ref CBR_EST_M , para MORTA
 * @related tCobra 
 */
int adquireEstado(tCobra cobra);
/**
 * @brief Define @p estado como o estado para a @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @param estado O novo estado
 * @return tCobra A @ref tCobra com o novo estado
 * @related tCobra 
 */
tCobra defineEstado(tCobra cobra, int estado);
/**
 * @brief Adquire o tamanho atual da @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @return int O tamanho da @ref tCobra somando sua cabeca com seu corpo
 * @related tCobra
 */
int adquireTamanho(tCobra cobra);
/**
 * @brief Move a cabeca da @ref tCobra para a @ref tPosicao @p pos , atualizando tambem os membros estado, devorado, tamanho e o corpo da @ref tCobra @p cobra
 * 
 * @param cobra A @ref tCobra
 * @param pos A nova posicao da cabeca da @ref tCobra
 * @param celDevorado A celula que foi devorada no processo de movimento
 * @return tCobra A @ref tCobra com a posicao da cabeca e do corpo e os membros estado, devorado e tamanho atualizados durante o moviemento
 * @related tCobra
 */
tCobra moveCbr(tCobra cobra, tPosicao pos, char celDevorado);

// FIM COBRA
// MAPA

/**
 * @brief Contem o tamanho maximo para ambas as dimensoes do mapa
 * @related tMapa
 */
#define TAM_MAPA 100
/**
 * @brief Contem o nome do arquivo que contem o mapa a ser lido
 * @related tMapa
 */
#define ARQ_MAPA "/mapa.txt"
/**
 * @brief Contem o nome do arquivo de saida para a exportacao do heatmap
 * @related tMapa
 */
#define ARQ_HMAP "/heatmap.txt"
/**
 * @brief Contem o nome do arquivo de saida para a exportacao do ranking do heatmap
 * @related tMapa
 */
#define ARQ_RANK "/ranking.txt"
/**
 * @brief Contem a representacao para uma celula vazia no mapa
 * @related tMapa
 */
#define CEL_VAZIA ' '
/**
 * @brief Contem a representacao para uma celula de parede no mapa
 * @related tMapa
 */
#define CEL_PARED '#'
/**
 * @brief Contem a representacao para uma celula de tunel no mapa
 * @related tMapa
 */
#define CEL_TUNEL '@'
/**
 * @brief Contem a representacao para uma celula de comida no mapa
 * @related tMapa
 */
#define CEL_COMID '*'
/**
 * @brief Contem a representacao para uma celula de dinheiro no mapa
 * @related tMapa
 */
#define CEL_DINHR '$'
/**
 * @brief Contem a representacao, no mapa, para uma celula de cabeca da cobra com direcao para a direita
 * @related tMapa
 */
#define CEL_CBRCD '>'
/**
 * @brief Contem a representacao, no mapa, para uma celula de cabeca da cobra com direcao para baixo
 * @related tMapa
 */
#define CEL_CBRCB 'v'
/**
 * @brief Contem a representacao, no mapa, para uma celula de cabeca da cobra com direcao para a esquerda
 * @related tMapa
 */
#define CEL_CBRCE '<'
/**
 * @brief Contem a representacao, no mapa, para uma celula de cabeca da cobra com direcao para cima
 * @related tMapa
 */
#define CEL_CBRCC '^'
/**
 * @brief Contem a representacao, no mapa, para uma celula de corpo da cobra
 * @related tMapa
 */
#define CEL_CBRCO 'o'
/**
 * @brief Contem a representacao, no mapa, para uma celula de cobra morta
 * @related tMapa
 */
#define CEL_CBRCM 'X'
/**
 * @brief Contem a representacao para o comando de movimento "continua na direcao"
 * @related tMapa
 */
#define MOV_CBRCT 'c'
/**
 * @brief Contem a representacao para o comando de movimento "horario"
 * @related tMapa
 */
#define MOV_CBRHO 'h'
/**
 * @brief Contem a representacao para o comando de movimento "antihorario"
 * @related tMapa
 */
#define MOV_CBRAH 'a'
/**
 * @brief Representa o mapa no jogo
 * 
 */
typedef struct {
    int nLinhas; ///< Numero de linhas que o mapa possui
    int mColunas; ///< Numero de colunas que o mapa possui
    char vet[TAM_MAPA][TAM_MAPA]; ///< A matriz bidimensional de dimensoes nLinhas x mColunas que contem o mapa
    tCobra cobra; ///< A cobra que esta no mapa
    tFila tuneis; ///< A dupla de tuneis que pode estar no mapa
    int qtdComida; ///< A quatidade de comidas que resta no mapa
    int heatmap[TAM_MAPA][TAM_MAPA]; ///< O heatmap de posicoes no mapa. Representa as posicoes do mapa pelo numero de acessos da cobra
} tMapa;
/**
 * @brief Le um mapa no arquivo @ref ARQ_MAPA dentro do diretorio @p caminhoBase informado
 * 
 * @param caminhoBase O diretorio onde deve estar o arquivo que contem o mapa a ser lido
 * @return tMapa Uma nova instancia de @ref tMapa baseada no arquivo lido
 * @related tMapa
 */
tMapa leMapa(char caminhoBase[]);
int adquireLinhas(tMapa mapa);
int adquireColunas(tMapa mapa);
tCobra adquireCobra(tMapa mapa);
int adquireQtdComida(tMapa mapa);
char adquireCel(tMapa mapa, tPosicao pos);
tMapa defineCel(tMapa mapa, tPosicao pos, char cel);
tPosicao adquireParTunel(tMapa mapa, tPosicao pos);
int estaDentroLimite(tMapa mapa, tPosicao pos);
int ehPosicaoValida(tMapa mapa, tPosicao pos);
tPosicao transformaPosicaoValida(tMapa mapa, tPosicao posicao);
tMapa fazMovimento(tMapa mapa, char movimento);
tMapa limpaMapa(tMapa mapa);
tMapa atualizaMapa(tMapa mapa);
void exportaHeatmap(tMapa mapa, char caminhoBase[]);
void exportaRanking(tMapa mapa, char caminhoBase[]);
void imprimeMapa(tMapa mapa);

// FIM MAPA
// ESTATISTICAS

#define ARQ_STTS "estatisticas.txt"

typedef struct {
    int qtdMov;
    int qtdNPntMov;
    int qtdMovC;
    int qtdMovD;
    int qtdMovB;
    int qtdMovE;
} tEstatisticas;

tEstatisticas inicializaEstatisticas();
int adquireQtdMovimentos(tEstatisticas estatisticas);
tEstatisticas atualizaEstatisticas(tEstatisticas estatisticas, tCobra cobra);
void geraArqEstatisticas(tEstatisticas estatisticas, char caminhoBase[]);

// FIM ESTATISTICAS
// JOGO

#define JOG_PNT_D 10
#define JOG_PNT_C 1

#define JOG_EST_C 0
#define JOG_EST_V 1
#define JOG_EST_D 2

#define DIR_SAID "/saida/"
#define ARQ_INIC "/inicializacao.txt"
#define ARQ_RESM "/resumo.txt"

typedef struct {
    tMapa mapa;
    int pontuacao;
    int estado;
    tEstatisticas estatisticas;
    char caminhoSaida[TAM_CAMINHO];
} tJogo;

tJogo inicializaJogo(char caminhoBase[]);
int acabou(tJogo jogo);
tJogo fazRodada(tJogo jogo, char movimento);
void geraArqInicializacao(tJogo jogo, char caminhoBase[]);
void exportaResumo(tJogo jogo, int currMov, tCobra cobra, char movimento);
void exportaJogo(tJogo jogo, char caminhoBase[]);
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
    
    geraArqInicializacao(jogo, jogo.caminhoSaida);
    do {
        char movimento;
        scanf("%c%*c", &movimento);
        
        jogo = fazRodada(jogo, movimento);

        printf("%c", '\n');
        printf("Estado do jogo apos o movimento '%c':\n", movimento);
        imprimeJogo(jogo);
    } while (!acabou(jogo));

    exportaJogo(jogo, jogo.caminhoSaida);

    return EXIT_SUCCESS;
}

// JOGO
tJogo inicializaJogo(char caminhoBase[]) {
    tMapa mapa = leMapa(caminhoBase);
    tEstatisticas estatisticas = inicializaEstatisticas();

    tJogo jogo = { mapa, 0, 0, estatisticas };

    // faz o o caminho de output
    combinaCaminho(jogo.caminhoSaida, caminhoBase, DIR_SAID);

    return jogo;
}

int acabou(tJogo jogo) {
    return jogo.estado != JOG_EST_C;
}

tJogo fazRodada(tJogo jogo, char movimento) {
    jogo.mapa = limpaMapa(jogo.mapa);
    jogo.mapa = fazMovimento(jogo.mapa, movimento);

    tCobra cbr = adquireCobra(jogo.mapa);

    char devorado = adquireDevorado(cbr);
    if (devorado == CEL_DINHR) {
        jogo.pontuacao += JOG_PNT_D;
    }
    else if (devorado == CEL_COMID) {
        jogo.pontuacao += JOG_PNT_C;
    }

    jogo.mapa = atualizaMapa(jogo.mapa);

    if (adquireEstado(cbr) == CBR_EST_M) {
        jogo.estado = JOG_EST_D;
    }
    else if (adquireQtdComida(jogo.mapa) == 0) {
        jogo.estado = JOG_EST_V;
    }

    jogo.estatisticas = atualizaEstatisticas(jogo.estatisticas, cbr);
    exportaResumo(jogo, adquireQtdMovimentos(jogo.estatisticas), cbr, movimento);

    return jogo;
}

void exportaResumo(tJogo jogo, int currMov, tCobra cobra, char movimento) {
    char devorado = adquireDevorado(cobra);

    // interrompe a exportacao se nao houver nenhum evento relevante
    if (devorado != CEL_DINHR && devorado != CEL_COMID && adquireEstado(cobra) == CBR_EST_V) {
        return;
    }

    char caminhoResm[TAM_CAMINHO];
    combinaCaminho(caminhoResm, jogo.caminhoSaida, ARQ_RESM);
    FILE *arq = fopen(caminhoResm, "a");

    fprintf(arq, "Movimento %d (%c) ", currMov, movimento);
    if (devorado == CEL_DINHR) {
        fprintf(arq, "gerou dinheiro");
    }
    else if (devorado == CEL_COMID) {
        fprintf(arq, "fez a cobra crescer para o tamanho %d", adquireTamanho(cobra));

        if (jogo.estado == JOG_EST_V) {
            fprintf(arq, ", terminando o jogo");
        }        
    }
    else {
        fprintf(arq, "resultou no fim de jogo por conta de colisao");
    }
    fprintf(arq, "%c", '\n');
    
    fclose(arq);
}

void geraArqInicializacao(tJogo jogo, char caminhoBase[]) {
    char caminhoInic[TAM_CAMINHO];
    combinaCaminho(caminhoInic, caminhoBase, ARQ_INIC);
    FILE *arq = fopen(caminhoInic, "w");

    int i;
    for (i = 0; i < adquireLinhas(jogo.mapa); i++) {
        int j;
        for (j = 0; j < adquireColunas(jogo.mapa); j++) {
            fprintf(arq, "%c", adquireCel(jogo.mapa, inicializaPosicao(i, j)));
        }
        fprintf(arq, "%c", '\n');
    }
    tPosicao cbr = adquireCabeca(adquireCobra(jogo.mapa));
    fprintf(arq, "A cobra comecara o jogo na linha %d e coluna %d\n", adquireI(cbr) + 1, adquireJ(cbr) + 1);

    fclose(arq);
}

void exportaJogo(tJogo jogo, char caminhoBase[]) {
    geraArqEstatisticas(jogo.estatisticas, caminhoBase);
    exportaHeatmap(jogo.mapa, caminhoBase);
    exportaRanking(jogo.mapa, caminhoBase);
}

void imprimeJogo(tJogo jogo) {
    imprimeMapa(jogo.mapa);
    printf("Pontuacao: %d\n", jogo.pontuacao);

    if (!acabou(jogo)) {
        return;
    }

    switch (jogo.estado) {
        case JOG_EST_V:
            printf("%s", "Voce venceu!\n");
            break;
        
        case JOG_EST_D:
            printf("%s", "Game over!\n");
            break;
    }

    printf("Pontuacao final: %d\n", jogo.pontuacao);
}
// FIM JOGO

// ESTATISTICAS
tEstatisticas inicializaEstatisticas() {
    tEstatisticas estatisticas = { 0, 0, 0, 0, 0, 0 };
    return estatisticas;
}

int adquireQtdMovimentos(tEstatisticas estatisticas) {
    return estatisticas.qtdMov;
}

tEstatisticas atualizaEstatisticas(tEstatisticas estatisticas, tCobra cobra) {
    estatisticas.qtdMov++;
    switch (adquireDirecao(cobra)) {
        case CBR_DIR_N:
            estatisticas.qtdMovC++;
            break;

        case CBR_DIR_L:
            estatisticas.qtdMovD++;
            break;

        case CBR_DIR_S:
            estatisticas.qtdMovB++;
            break;

        case CBR_DIR_O:
            estatisticas.qtdMovE++;
            break;
    }
    
    char devorado = adquireDevorado(cobra);
    if (devorado != CEL_COMID && devorado != CEL_DINHR) {
        estatisticas.qtdNPntMov++;
    }

    return estatisticas;
}

void geraArqEstatisticas(tEstatisticas estatisticas, char caminhoBase[]) {
    char caminhoStts[TAM_CAMINHO];
    combinaCaminho(caminhoStts, caminhoBase, ARQ_STTS);
    FILE *arq = fopen(caminhoStts, "w");

    fprintf(arq, "Numero de movimentos: %d\n", estatisticas.qtdMov);
    fprintf(arq, "Numero de movimentos sem pontuar: %d\n", estatisticas.qtdNPntMov);
    fprintf(arq, "Numero de movimentos para baixo: %d\n", estatisticas.qtdMovB);
    fprintf(arq, "Numero de movimentos para cima: %d\n", estatisticas.qtdMovC);
    fprintf(arq, "Numero de movimentos para esquerda: %d\n", estatisticas.qtdMovE);
    fprintf(arq, "Numero de movimentos para direita: %d\n", estatisticas.qtdMovD);

    fclose(arq);
}
// FIM ESTATISTICAS

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
    mapa.tuneis = inicializaFila();

    int i;
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            char curr;
            fscanf(arq, "%c", &curr);
            mapa.vet[i][j] = curr;
            mapa.heatmap[i][j] = 0;

            if (curr == CEL_VAZIA || curr == CEL_PARED) {
                continue;
            }

            switch (curr) {
                case CEL_CBRCB:
                case CEL_CBRCC:
                case CEL_CBRCD:
                case CEL_CBRCE:
                    mapa.cobra = inicializaCobra(inicializaPosicao(i, j), curr);
                    mapa.heatmap[i][j] = 1;
                    break;

                case CEL_COMID:
                    mapa.qtdComida++;
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

int adquireLinhas(tMapa mapa) {
    return mapa.nLinhas;
}

int adquireColunas(tMapa mapa) {
    return mapa.mColunas;
}

tCobra adquireCobra(tMapa mapa) {
    return mapa.cobra;
}

int adquireQtdComida(tMapa mapa) {
    return mapa.qtdComida;
}

char adquireCel(tMapa mapa, tPosicao pos) {
    return mapa.vet[pos.i][pos.j];
}

tMapa defineCel(tMapa mapa, tPosicao pos, char cel) {
    mapa.vet[pos.i][pos.j] = cel;
    return mapa;
}

tPosicao adquireParTunel(tMapa mapa, tPosicao pos) {
    tPosicao primeiroTunel = adquireElem(mapa.tuneis, 0);
    return comparaPos(pos, primeiroTunel) ? adquireElem(mapa.tuneis, 1) : primeiroTunel;
}

int estaDentroLimite(tMapa mapa, tPosicao pos) {
    return pos.i >= 0
        && pos.i < mapa.nLinhas
        && pos.j >= 0
        && pos.j < mapa.mColunas;
}

int ehPosicaoValida(tMapa mapa, tPosicao pos) {
    return estaDentroLimite(mapa, pos) && adquireCel(mapa, pos) != CEL_TUNEL;
}

tPosicao transformaPosicaoValida(tMapa mapa, tPosicao pos) {
    if (ehPosicaoValida(mapa, pos)) {
        return pos;
    }
    
    // corrige a posicao para dentro dos limites
    pos = inicializaPosicao(abs((mapa.nLinhas + adquireI(pos)) % mapa.nLinhas), adquireJ(pos));
    pos = inicializaPosicao(adquireI(pos), abs((mapa.mColunas + adquireJ(pos)) % mapa.mColunas));
    
    // trata o eventual teleporte da cobra pelos tuneis
    if (adquireCel(mapa, pos) == CEL_TUNEL) {
        pos = adquireParTunel(mapa, pos);
        int direcao = adquireDirecao(mapa.cobra);
        
        pos = avancaNaDirecao(pos, direcao);
    }

    return transformaPosicaoValida(mapa, pos);
}

tMapa fazMovimento(tMapa mapa, char movimento) {
    int dD = 0;
    if (movimento == MOV_CBRHO)
        dD = 1;
    else if (movimento == MOV_CBRAH)
        dD= -1;

    mapa.cobra = defineDirecao(mapa.cobra, (4 + adquireDirecao(mapa.cobra) + dD) % 4);

    int direcao = adquireDirecao(mapa.cobra);
    tPosicao posDest = adquireCabeca(mapa.cobra);
    posDest = avancaNaDirecao(posDest, direcao);

    posDest = transformaPosicaoValida(mapa, posDest);
    
    char cbrDevorou = adquireCel(mapa, posDest);
    if (cbrDevorou == CEL_COMID) {
        mapa.qtdComida--;
    }
    mapa.cobra = moveCbr(mapa.cobra, posDest, cbrDevorou);
    mapa.heatmap[adquireI(posDest)][adquireJ(posDest)] += 1;
    return mapa;
}

tMapa limpaMapa(tMapa mapa) {
    tFila cbrCorpo = adquireCorpo(mapa.cobra);
    int i;
    for (i = adquireTam(cbrCorpo) - 1; i >= 0; i--) {
        tPosicao curr = adquireElem(cbrCorpo, i);
        mapa = defineCel(mapa, curr, CEL_VAZIA);
    }
    return mapa;
}

tMapa atualizaMapa(tMapa mapa) {    
    tFila cbrCorpo = adquireCorpo(mapa.cobra);
    int i;
    for (i = adquireTam(cbrCorpo) - 1; i >= 0; i--) {
        tPosicao curr = adquireElem(cbrCorpo, i);
        char cbrCh = adquireEstado(mapa.cobra) == CBR_EST_V ? CEL_CBRCO : CEL_CBRCM;
        mapa = defineCel(mapa, curr, cbrCh);
    }
    if (adquireEstado(mapa.cobra) == CBR_EST_V) {
        tPosicao curr = adquireCabeca(mapa.cobra);
        char cbrCh;
        switch (adquireDirecao(mapa.cobra)){
            case CBR_DIR_N:
                cbrCh = CEL_CBRCC;
                break;

            case CBR_DIR_L:
                cbrCh = CEL_CBRCD;
                break;

            case CBR_DIR_S:
                cbrCh = CEL_CBRCB;
                break;

            case CBR_DIR_O:
                cbrCh = CEL_CBRCE;
                break;
        }
        mapa = defineCel(mapa, curr, cbrCh);
    }

    return mapa;
}

void exportaHeatmap(tMapa mapa, char caminhoBase[]) {
    char caminhoHeatmap[TAM_CAMINHO];
    combinaCaminho(caminhoHeatmap, caminhoBase, ARQ_HMAP);
    FILE *arq = fopen(caminhoHeatmap, "w");

    int i;
    for (i = 0; i < mapa.nLinhas; i++) {
        int j;
        for (j = 0; j < mapa.mColunas; j++) {
            fprintf(arq, "%d", mapa.heatmap[i][j]);
            if (j < mapa.mColunas - 1)
                fprintf(arq, "%c", ' ');
        }
        fprintf(arq, "%c", '\n');
    }

    fclose(arq);
}

void exportaRanking(tMapa mapa, char caminhoBase[]) {
    tPosicao posicoes[mapa.nLinhas * mapa.mColunas];
    int heats[mapa.nLinhas * mapa.mColunas];
    int tam = 0;
    
    // planifica heatmap
    int i;
    for (i = 0; i < mapa.nLinhas; i++) {
        int j;
        for (j = 0; j < mapa.mColunas; j++) {
            if (mapa.heatmap[i][j] > 0) {
                posicoes[tam] = inicializaPosicao(i, j);
                heats[tam] = mapa.heatmap[i][j];
                tam++;
            }
        }
    }

    // ordena o ranking
    for (i = 1; i < tam; i++) {
        if (heats[i] > heats[i - 1]) {
            tPosicao tmpPos = posicoes[i];
            int tmpHeat = heats[i];
            posicoes[i] = posicoes[i - 1];
            heats[i] = heats[i - 1];
            posicoes[i - 1] = tmpPos;
            heats[i - 1] = tmpHeat;

            i = 0;
        }
    }

    // exporta
    char caminhoRank[TAM_CAMINHO];
    combinaCaminho(caminhoRank, caminhoBase, ARQ_RANK);
    FILE *arq = fopen(caminhoRank, "w");
    for (i = 0; i < tam; i++) {
        tPosicao curr = posicoes[i];
        fprintf(arq, "(%d, %d) - %d\n", adquireI(curr), adquireJ(curr), heats[i]);
    }

    fclose(arq);
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
    cobra.corpo = enfileira(cobra.corpo, posCab);

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
    
    cobra.devorado = '\0';
    cobra.estado = 1;
    return cobra;
}

tPosicao adquireCabeca(tCobra cobra) {
    return adquireElem(cobra.corpo, 0);
}

tFila adquireCorpo(tCobra cobra) {
    return cobra.corpo;
}

int adquireDirecao(tCobra cobra) {
    return cobra.direcaoCabeca;
}

tCobra defineDirecao(tCobra cobra, int direcao) {
    cobra.direcaoCabeca = direcao;
    return cobra;
}

char adquireDevorado(tCobra cobra) {
    return cobra.devorado;
}

int adquireEstado(tCobra cobra) {
    return cobra.estado;
}

tCobra defineEstado(tCobra cobra, int estado) {
    cobra.estado = estado;
    return cobra;
}

int adquireTamanho(tCobra cobra) {
    return adquireTam(cobra.corpo);
}

tCobra moveCbr(tCobra cobra, tPosicao pos, char celDevorado) {
    cobra.devorado = celDevorado;
    cobra.corpo = enfileira(cobra.corpo, pos);
    if (celDevorado != CEL_COMID) {
        cobra.corpo = desenfileira(cobra.corpo);
    }
    
    if (celDevorado == CEL_PARED) {
        cobra.estado = CBR_EST_M;
    }
    else {
        int i;
        for (i = adquireTam(cobra.corpo) - 1; i > 0; i--) {
            if (comparaPos(adquireElem(cobra.corpo, i), pos)) {
                cobra.estado = CBR_EST_M;
                break;
            }
        }
    }

    return cobra;
}
// FIM COBRA

// FILA
tFila inicializaFila() {
    tFila fila = { 0 };
    return fila;
}

int adquireTam(tFila fila) {
    return fila.tam;
}

tPosicao adquireElem(tFila fila, int index) {
    if (index < 0 || index >= fila.tam) {
        index = fila.tam - 1;
    }

    return fila.vet[index];
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
// FIM FILA

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

tPosicao avancaNaDirecao(tPosicao pos, int direcao) {
    // adquire os respectivos deltas para a posicao resultado do avanco
    int dI = 0, dJ = 0;
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
    pos = alteraPeloDelta(pos, dI, dJ);
    return pos;
}

int comparaPos(tPosicao pos1, tPosicao pos2) {
    return pos1.i == pos2.i && pos1.j == pos2.j;
}
// FIM POSICAO

void combinaCaminho(char dest[], char cmnh1[], char cmnh2[]) {
    strcpy(dest, cmnh1);
    strcat(dest, cmnh2);
}
