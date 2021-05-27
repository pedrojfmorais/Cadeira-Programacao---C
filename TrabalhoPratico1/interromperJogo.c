#include <stdio.h>
#include <stdlib.h>

#include "jogadores.h"
#include "tabuleiro.h"
#include "registoJogadas.h"
#include "tipoJogo.h"

//fun��o que guarda o estado do jogo, de forma a puder ser retomado mais tarde
int interromperJogo(int tipoJogo, int numJogadas, jogadores jogadorA, jogadores jogadorB, tabuleiro tab, ponteiroJogadas listaJogadas)
{
    /*
        recebe:
            tipoJogo -> 1 = 1 jogador; 2 = 2 jogadoress
            numJogadas -> n�mero de jogadas
            jogadorA -> estrutura com os dados do jogador A
            jogadorB -> estrutura com os dados do jogador B
            tab -> tabuleiro atual de jogo
            listaJogadas -> lista ligada com o registo de todas as jogadas
    */

    //lista ligada auxiliar para manipular as jogadas anteriores
    ponteiroJogadas aux = listaJogadas;

    //abre o ficheiro "jogo.bin" para escrita bin�ria
    FILE *f = fopen("jogo.bin", "wb");

    //verifica se o ficheiro foi bem aberto
    if (f == NULL)
    {
        printf("Erro ao aceder ao ficheiro! \n");
        return 1;
    }

    //escreve no ficheiro bin�rio o tipo de jogo e o n�mero de jogadas
    fwrite(&tipoJogo, sizeof(int), 1, f);
    fwrite(&numJogadas, sizeof(int), 1, f);

    //escreve no ficheiro a estrutura dos jogadores
    fwrite(&jogadorA, sizeof(jogadores), 1, f);
    fwrite(&jogadorB, sizeof(jogadores), 1, f);

    //escreve tabuleiro
    //primeiro escreve o n�mero de linhas e colunas
    fwrite(&tab.nLinhas, sizeof(int), 1, f);
    fwrite(&tab.nColunas, sizeof(int), 1, f);

    //depois escreve a informa��o do tabuleiro em si, linha a linha
    for(int i = 0; i < tab.nLinhas; i++)
    {
        fwrite(tab.tabuleiro[i], sizeof(char)*tab.nColunas, 1, f);
    }

    //escreve listaJogadas
    //para cada jogada que ocorreu
    for(int i = 0; i < numJogadas; i++)
    {
        //escreve as informa��es simples,
        fwrite(&aux->jogador, sizeof(char), 1, f); //identifica��o jogador
        fwrite(&aux->nJogada, sizeof(int), 1, f); //n�mero da jogada
        fwrite(&aux->linhaAfetada, sizeof(int), 1, f); // linha afetada pela jogada
        fwrite(&aux->colunaAfetada, sizeof(int), 1, f); // coluna afetada pela jogada
        fwrite(&aux->infoJogada, sizeof(char), 100, f); //texto descritivo da jogada

        //escreve o tabuleiro resultado da jogada
        // escreve o numero de linhas e colunas do tabuleiro
        fwrite(&aux->tab.nLinhas, sizeof(int), 1, f);
        fwrite(&aux->tab.nColunas, sizeof(int), 1, f);

        //escreve o tabuleiro linha a linha no ficheiro
        for(int j = 0; j < aux->tab.nLinhas; j++)
        {
            fwrite(aux->tab.tabuleiro[j], sizeof(char)*aux->tab.nColunas, 1, f);
        }

        //ap�s escrever todos os dados da jogada passa para o pr�ximo n� da lista
        aux = aux->next;

    }

    //fecha o ficheiro
    fclose(f);

    //mostra uma mensagem a indicar que foi tudo guardado com sucesso
    printf("\n\n O seu jogo foi guardado, volte mais tarde para continuar. \n\n");

    //liberta a mem�ria alocada dinamicamente para a tabela e para a lista ligada
    libertarMemoria(listaJogadas, &tab);

    //termina o programa
    exit(0);
}

//fun��o que retoma o jogo a partir do ficheiro bin�rio
void lerJogoGuardado()
{
    //declara��o das vari�veis necess�rias para receber os dados do ficheiro
    int tipoJogo;
    int numJogadas;
    jogadores jogadorA;
    jogadores jogadorB;
    tabuleiro tab;
    ponteiroJogadas listaJogadas = NULL;

    //abertura do ficheiro "jogo.bin" para leitura bin�ria
    FILE *f;
    f = fopen("jogo.bin", "rb");

    //verifica se o ficheiro foi bem aberto
    if (f == NULL)
    {
        printf("Erro ao aceder ao ficheiro! \n");
        return 1;
    }

    //l� o tipo de jogo e o n�mero de jogadas
    fread(&tipoJogo, sizeof(int), 1, f);
    fread(&numJogadas, sizeof(int), 1, f);

    //l� os dados das estruturas dos jogadores
    fread(&jogadorA, sizeof(jogadores), 1, f);
    fread(&jogadorB, sizeof(jogadores), 1, f);

    //l� tabuleiro
    // l� o n�mero de linhas e colunas do tabuleiro
    fread(&tab.nLinhas, sizeof(int), 1, f);
    fread(&tab.nColunas, sizeof(int), 1, f);

    //aloca espa�o para as diversas linhas do tabuleiro
    tab.tabuleiro = (char**)malloc(sizeof(char*)*tab.nLinhas);

    //verifica se a aloca��o de mem�ria correu bem
    if(tab.tabuleiro == NULL)
    {
        printf("Ocorreu um erro a alocar mem�ria!");
        return;
    }

    //para cada linha tabela vai
    for(int i = 0; i < tab.nLinhas; i++)
    {
        //alocar espa�o para as diversas colunas da tabela
        tab.tabuleiro[i] = (char*)malloc(sizeof(char)* tab.nColunas);

        //verifica a aloca��o de mem�ria
        if(tab.tabuleiro[i] == NULL)
        {
            printf("Ocorreu um erro a alocar mem�ria!");
            return;
        }

        //l� a linha atual do ficheiro
        fread(tab.tabuleiro[i], sizeof(char)*tab.nColunas, 1, f);
    }

    //para cada registo de jogadas
    for(int i = 0; i < numJogadas; i++)
    {
        //cria uma variavel do tipo estrutura jogadas auxiliar para ler os dados do ficheiro
        jogada aux;

        //l� os dados simples do ficheiro
        fread(&aux.jogador, sizeof(char), 1, f);
        fread(&aux.nJogada, sizeof(int), 1, f);
        fread(&aux.linhaAfetada, sizeof(int), 1, f);
        fread(&aux.colunaAfetada, sizeof(int), 1, f);
        fread(&aux.infoJogada, sizeof(char), 100, f);

        // l� o n�mero de linhas e colunas do ficheiro
        fread(&aux.tab.nLinhas, sizeof(int), 1, f);
        fread(&aux.tab.nColunas, sizeof(int), 1, f);

        //aloca espa�o para as diversas linhas da tabela
        aux.tab.tabuleiro = (char**)malloc(sizeof(char*)*aux.tab.nLinhas);

        //verifica a aloca��o de mem�ria
        if(aux.tab.tabuleiro == NULL)
        {
            printf("Ocorreu um erro a alocar mem�ria!");
            return;
        }

        //para cada linha
        for(int j = 0; j < aux.tab.nLinhas; j++)
        {
            //aloca espa�o para as diversas colunas
            aux.tab.tabuleiro[j] = (char*)malloc(sizeof(char)* aux.tab.nColunas);

            //verifica a aloca��o de mem�ria
            if(aux.tab.tabuleiro[j] == NULL)
            {
                printf("Ocorreu um erro a alocar mem�ria!");
                return;
            }

            //l� a linha atual da tabela
            fread(aux.tab.tabuleiro[j], sizeof(char)*aux.tab.nColunas, 1, f);
        }

        //coloca o pr�ximo n� da lista como "NULL"
        aux.next = NULL;

        //adiciona � lista ligada o novo n� da lista
        listaJogadas = adicionarJogada(listaJogadas, aux.tab, aux.jogador, aux.nJogada-1, aux.linhaAfetada, aux.colunaAfetada, aux.infoJogada);
    }

    //fecha o ficheiro
    fclose(f);
    //elimina o ficheiro
    remove("jogo.bin");

    //verifica o tipo de jogo
    if(tipoJogo == 1)
    {
        // inicia um jogo contra o computador com os dados lidos do ficheiro
        printf("\n\n\n\n------------- A retomar UM JOGADOR -------------\n\n\n\n");
        umJogador(numJogadas, jogadorA, jogadorB, tab, listaJogadas);
    }
    else if(tipoJogo == 2)
    {
        //inicia um jogo contra o computador com os dados recebidos do ficheiro lido
        printf("\n\n\n\n------------ A retomar DOIS JOGADORES ------------\n\n\n\n");
        doisJogadores(numJogadas, jogadorA, jogadorB, tab, listaJogadas);
    }
}
