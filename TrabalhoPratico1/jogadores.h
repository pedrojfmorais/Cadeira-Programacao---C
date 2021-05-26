#ifndef JOGADORES_H_INCLUDED
#define JOGADORES_H_INCLUDED

//estrutura para guardar os dados de um jogador
struct dadosJogadores{

    char identificacao;
    int pedra;
    int aumentarTabuleiro;

};

//d� o apelido "jogadores" para a "struct dadosJogadores"
typedef struct dadosJogadores jogadores;

//declara as fun��es criadas no ficheiro "jogadores.c"
jogadores inicializarJogador(char identificacao);
void mostraJogador(jogadores jogador);

#endif // JOGADORES_H_INCLUDED
