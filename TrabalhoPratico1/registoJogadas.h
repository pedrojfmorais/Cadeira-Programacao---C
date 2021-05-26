#ifndef REGISTOJOGADAS_H_INCLUDED
#define REGISTOJOGADAS_H_INCLUDED

#include "tabuleiro.h"

//d� os apelidos "jogada" para a "struct Jogada" e "ponteiroJogadas" para um ponteiro desta mesma estrutura
typedef struct Jogada jogada, *ponteiroJogadas;

//estrutura para guardar as jogadas numa lista ligada
struct Jogada{

    //guarda um tabuleiro
    tabuleiro tab;
    //guarda o caractere que identifica o jogador
    char jogador;
    //guarda o numero da jogada, linha e coluna afetada
    int nJogada;
    int linhaAfetada;
    int colunaAfetada;
    //guarda ainda uma pequena descri��o da jogada
    char infoJogada[100];

    //ponteiro para o pr�ximo n� da lista ligada
    jogada *next;

};

//declara��o das fun��es criadas no ficheiro "registoJogadas.c"
ponteiroJogadas adicionarJogada(ponteiroJogadas listaJogadas, tabuleiro tab, char idJogador, int nJogada, int linha, int coluna, char infoJogada[]);
void mostrarJogada(ponteiroJogadas listaJogadas);
int escreveJogadasFicheiro(char *nomeFicheiro, ponteiroJogadas listaJogadas);

#endif // REGISTOJOGADAS_H_INCLUDED
