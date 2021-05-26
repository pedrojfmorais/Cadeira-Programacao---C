#ifndef INTERROMPERJOGO_H_INCLUDED
#define INTERROMPERJOGO_H_INCLUDED

#include "jogadores.h"
#include "tabuleiro.h"
#include "registoJogadas.h"

//declara as fun��es criadas no ficheiro "interromperJogo.c"
int interromperJogo(int tipoJogo, int numJogadas, jogadores jogadorA, jogadores jogadorB, tabuleiro tab, ponteiroJogadas listaJogadas);
void lerJogoGuardado();

#endif // INTERROMPERJOGO_H_INCLUDED
