#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "jogadores.h"
#include "tabuleiro.h"
#include "registoJogadas.h"

void umJogador()
{

}

void doisJogadores(int numJogadas, jogadores jogadorA, jogadores jogadorB, tabuleiro tab, ponteiroJogadas listaJogadas)
{
    int checkJogada = 0;
    char opcao;

    jogadores arrayJogadores[2] = {jogadorA,jogadorB};

    int linha, coluna;

    char infoJogada[100];
    int nJogadasAnteriores = 0;

    int vitoria = 0;

    while(1)
    {
        printf("\n\n--------------------------------------------------\n");
        printf("Jogador %c.\n\n", arrayJogadores[numJogadas%2].identificacao);

        mostraTabuleiro(tab);
        menuJogadas();
        printf("--------------------------------------------------\n");
        do{

            printf("Escolha uma jogada: ");
            scanf("%d", &opcao);
        }while(opcao < 0 || opcao > 7 && opcao != 9);

        switch(opcao)
        {
            case 1:
                pedeCoordenadas(tab,&linha,&coluna);
                checkJogada = verificaPeca(tab, &arrayJogadores[numJogadas%2],linha,coluna,'G');

                if(checkJogada == 1)
                    break;

                //registo de jogadas
                sprintf(infoJogada, "Peca Verde na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                vitoria = verificaVitoria(tab);

                if(vitoria == 1)
                {
                    declararVitoria(arrayJogadores[(numJogadas)%2].identificacao);

                    //registo de jogadas
                    sprintf(infoJogada, "O jogador %c ganhou o jogo.\n", arrayJogadores[numJogadas%2].identificacao);
                    listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas+1, 0, 0, infoJogada);

                    //terminar jogo
                    terminarJogo(listaJogadas, &tab);
                }

                break;

            case 2:
                pedeCoordenadas(tab,&linha,&coluna);
                checkJogada = verificaPeca(tab,&arrayJogadores[numJogadas%2],linha,coluna,'Y');

                if(checkJogada == 1)
                    break;

                //registo de jogadas
                sprintf(infoJogada, "Peca Amarela na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                vitoria = verificaVitoria(tab);

                if(vitoria == 1)
                {
                    declararVitoria(arrayJogadores[(numJogadas)%2].identificacao);

                    //registo de jogadas
                    sprintf(infoJogada, "O jogador %c ganhou o jogo.\n", arrayJogadores[numJogadas%2].identificacao);
                    listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas+1, 0, 0, infoJogada);

                    //terminar jogo
                    terminarJogo(listaJogadas, &tab);
                }

                break;

            case 3:
                pedeCoordenadas(tab,&linha,&coluna);
                checkJogada = verificaPeca(tab,&arrayJogadores[numJogadas%2],linha,coluna,'R');

                if(checkJogada == 1)
                    break;

                //registo de jogadas
                sprintf(infoJogada, "Peca Vermelha na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                vitoria = verificaVitoria(tab);

                if(vitoria == 1)
                {

                    declararVitoria(arrayJogadores[(numJogadas)%2].identificacao);

                    //registo de jogadas
                    sprintf(infoJogada, "O jogador %c ganhou o jogo.\n", arrayJogadores[numJogadas%2].identificacao);
                    listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas+1, 0, 0, infoJogada);

                    //terminar jogo
                    terminarJogo(listaJogadas, &tab);
                }

                break;

            case 4:
                if(arrayJogadores[numJogadas%2].pedra == 0)
                {
                    printf("\nEste jogador esgotou as Pedras.\n");
                    checkJogada = 1;
                    break;
                }
                pedeCoordenadas(tab,&linha,&coluna);
                checkJogada = verificaPeca(tab,&arrayJogadores[numJogadas%2],linha,coluna,'P');

                //registo de jogadas
                sprintf(infoJogada, "Pedra na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                break;

            case 5:
                if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                {
                    printf("\nEste jogador esgotou os seus aumentos do tabuleiro.\n");
                    checkJogada = 1;
                    break;
                }

                tab = aumentaLinhas(tab, &arrayJogadores[numJogadas%2], &checkJogada);

                //registo de jogadas
                sprintf(infoJogada, "Aumento de uma linha ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, tab.nLinhas, 0, infoJogada);

                break;

            case 6:
                if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                {
                    printf("\nEste jogador esgotou os seus aumentos do tabuleiro.\n");
                    checkJogada = 1;
                    break;
                }

                tab = aumentaColunas(tab, &arrayJogadores[numJogadas%2], &checkJogada);

                //registo de jogadas
                sprintf(infoJogada, "Aumento de uma coluna ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, 0, tab.nColunas, infoJogada);

                break;

            case 7:

                printf("\nOcorreram ate agora %d jogadas.\n", numJogadas);
                do{

                    printf("Ver ultimas 'x' jogadas: ");
                    scanf("%d", &nJogadasAnteriores);
                }while(nJogadasAnteriores < 0 || nJogadasAnteriores > numJogadas);

                printf("\n");

                ponteiroJogadas aux;
                aux = listaJogadas;

                for(int i = 1; i <= (numJogadas-nJogadasAnteriores);i++)
                {
                    aux = aux->next;
                }

                for(int i = 0; i < nJogadasAnteriores; i++)
                {
                    mostrarJogada(aux);
                    aux = aux->next;
                }
                checkJogada = 1;
                break;

            case 9:
                break;

            case 0:
                printf("\nPretende mesmo desistir(y/n): ");
                scanf(" %c", &opcao);

                if(opcao == 'y' || opcao == 'Y')
                {
                    declararVitoria(arrayJogadores[(numJogadas+1)%2].identificacao);

                    //registo de jogadas
                    sprintf(infoJogada, "O jogador %c desistiu.\n", arrayJogadores[numJogadas%2].identificacao);
                    listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, 0, 0, infoJogada);

                    //terminar jogo
                    terminarJogo(listaJogadas, &tab);
                } else{
                    checkJogada = 1;
                }

                break;

            default:
                printf("Ocorreu  um erro, tente novamente!\n");
                break;

        }

        if(checkJogada == 0)
            numJogadas++;

    }
}

void terminarJogo(ponteiroJogadas listaJogadas, tabuleiro *tab)
{

    ponteiroJogadas aux;
    int resultadoFicheiroJogadas;
    char nomeFicheiro[99];

    printf("Indique o nome do ficheiro onde pretende guardar as jogadas: ");
    scanf("%s", nomeFicheiro);

    strcat(nomeFicheiro, ".txt");

    resultadoFicheiroJogadas = escreveJogadasFicheiro(nomeFicheiro, listaJogadas);

    if(resultadoFicheiroJogadas)
    {
        printf("\nOcorreu um erro a guardar as jogadas no seu ficheiro!\n\n");
    } else
    {
        printf("\nO ficheiro com as jogadas foi criado.\n\n");
    }

    // liberta cada linha da tabela
    for(int i = 0; i < tab->nLinhas; i++)
        free(tab->tabuleiro[i]);

    // liberta a tabela em si
    free(tab->tabuleiro);

    while(listaJogadas != NULL)
    {

        aux = listaJogadas;
        listaJogadas = listaJogadas->next;

        // liberta a tabela
        for(int i = 0; i < aux->tab.nLinhas; i++)
            free(aux->tab.tabuleiro[i]);

        free(aux->tab.tabuleiro);

        // leberta o n�
        free(aux);
    }

    exit(0);
}

int main()
{

    int opcao;

    initRandom();

    menuPrincipal();
    do{

        printf("Insira uma opcao: ");
        scanf(" %d", &opcao);

    }while(opcao < 0 || opcao > 2 && opcao != 9);

    printf("\n");

    switch(opcao)
    {
        case 0:
            //continuar jogo
            break;
        case 1:
            // 1 jogador
            break;
        case 2:
            doisJogadores(0, inicializarJogador('A'), inicializarJogador('B'), inicializarTabuleiro(), NULL);
            break;
        case 9:
            printf("Obrigado por jogar.\n");
            return 0;
        default:
            printf("Ocorreu  um erro, tente novamente!\n");
            return 0;
    }

    return 0;
}
