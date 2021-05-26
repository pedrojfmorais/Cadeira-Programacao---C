#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "jogadores.h"
#include "tabuleiro.h"
#include "tipoJogo.h"


int main()
{

    //variavel para guardar a opcao inserida pelo utilizador
    int opcao;

    //chama a fun��o initRandom() que permitir� utilizar a fun��o de n�meros random
    initRandom();

    //mostra as op��es de jogo que o jogador pode escolher
    printf("\n\n --------- Bem vindo ao Jogo do Semaforo ---------\n\n\n");
    printf("Escolha um tipo de jogo: \n\n");
    menuPrincipal();

    //verifica��o do input do utilizador
    do{

        printf("Insira uma opcao: ");
        scanf(" %d", &opcao);

    }while(opcao < 0 || opcao > 2 && opcao != 9);

    printf("\n");

    //se o utilizador selecionar
    switch(opcao)
    {
        //continuar jogo, este vai ler o ficheiro "jogo.bin" e voltar ao estado do jogo em que tinha ficado
        case 0:
            lerJogoGuardado();
            break;

        //1 jogador, come�a um novo jogo contra o computador
        case 1:
            umJogador(0, inicializarJogador('A'), inicializarJogador('B'), inicializarTabuleiro(), NULL);
            break;

        //2 jogadores, come�a um jogo com dois jogadores humanos
        case 2:
            doisJogadores(0, inicializarJogador('A'), inicializarJogador('B'), inicializarTabuleiro(), NULL);
            break;

        //sair, termina o programa
        case 9:
            printf("Obrigado por jogar.\n");
            return 0;

        //caso ocorra um erro e n�o seja nenhuma das op��es acima mostra um erro e termina o programa
        default:
            printf("Ocorreu  um erro, tente novamente!\n");
            return 0;
    }

    return 0;
}
