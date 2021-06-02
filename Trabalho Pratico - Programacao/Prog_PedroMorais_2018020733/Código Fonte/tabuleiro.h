#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

#include "jogadores.h"

//estrutura do tabuleiro
struct Tabuleiro {

    //guarda num array bidimensional din�mico o estado do tabuleiro
    char **tabuleiro;

    //guarda o n�mero de linhas e de colunas do tabuleiro
    int nLinhas;
    int nColunas;
};

//cria um alias para "struct Tabuleiro" de "tabuleiro"
typedef struct Tabuleiro tabuleiro;

//declara��o das fun��es criadas no ficheiro "tabuleiro.c"
tabuleiro inicializarTabuleiro();
void mostraTabuleiro(tabuleiro tab);
void pedeCoordenadas(tabuleiro tab, int *linha, int *coluna);

int verificaPeca(tabuleiro tab, int linha, int coluna, char pecaColocar);
tabuleiro aumentaLinhas(tabuleiro tab, int *checkJogada);
tabuleiro aumentaColunas(tabuleiro tab, int *checkJogada);

tabuleiro copiarTabuleiro(tabuleiro tabRecebido);

int verificaVitoria(tabuleiro tab);

#endif // TABULEIRO_H_INCLUDED
