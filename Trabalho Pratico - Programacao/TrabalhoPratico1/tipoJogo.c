#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "jogadores.h"
#include "tabuleiro.h"
#include "registoJogadas.h"
#include "interromperJogo.h"

//fun��o de jogo para um jogador
void umJogador(int numJogadas, jogadores jogadorA, jogadores jogadorB, tabuleiro tab, ponteiroJogadas listaJogadas)
{
    //declara��o de vari�veis
    int linha, coluna;
    int opcao;

    int checkJogada = 0;

    //cria��o de um array para os jogadores para alternar entre os dois conforme a jogada
    jogadores arrayJogadores[2] = {jogadorA,jogadorB};

    char infoJogada[100];
    int nJogadasAnteriores = 0;

    int vitoria = 0;

    //inicia o jogo
    while(1)
    {

        //caso seja a vez do computador jogar, Jogador B
        if(arrayJogadores[numJogadas%2].identificacao == 'B')
        {

            //recebe um n�mero random entre '1' e o limite do tabuleiro, para as linhas e para as colunas
            linha = intUniformRnd(1,tab.nLinhas);
            coluna = intUniformRnd(1,tab.nColunas);

            //mostra o jogador que est� a jogar
            printf("\n\n--------------------------------------------------\n");
            printf("Jogador %c.\n\n", arrayJogadores[numJogadas%2].identificacao);

            //mostra o tabuleiro
            mostraTabuleiro(tab);

            //enquanto n�o realizar um jogada v�lida
            do{
                //se na posi��o gerada aleatoriamente estiver uma pedra ou uma pe�a vermelha volta a gerar as linhas e colunas e volta ao in�cio do ciclo "do while"
                if(tab.tabuleiro[linha-1][coluna-1] == 'P' || tab.tabuleiro[linha-1][coluna-1] == 'R')
                {
                    linha = intUniformRnd(1,tab.nLinhas);
                    coluna = intUniformRnd(1,tab.nColunas);
                    continue;
                }

                //gera um n�mero aleat�rio entre 1 e 4 para a opera��o que o computador realizar
                opcao = intUniformRnd(1,4);

                //caso a op��o gerada for
                switch(opcao)
                {
                    // '1' coloca uma pe�a de cor no local gerado anteriormente aleatoriamente
                    case 1:

                        if(tab.tabuleiro[linha-1][coluna-1] == ' ')
                        {
                            //se o local gerado anteriormente estiver em branco coloca uma pe�a verde
                            checkJogada = verificaPeca(tab,linha,coluna,'G');
                            sprintf(infoJogada, "Peca Verde na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);

                        } else if(tab.tabuleiro[linha-1][coluna-1] == 'G')
                        {
                            //se tiver uma pe�a verde coloca uma pe�a amarela
                            checkJogada = verificaPeca(tab,linha,coluna,'Y');
                            sprintf(infoJogada, "Peca Amarela na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);

                        }else if(tab.tabuleiro[linha-1][coluna-1] == 'Y')
                        {
                            //se tiver uma pe�a amarela coloca um pe�a vermelha
                            checkJogada = verificaPeca(tab,linha,coluna,'R');
                            sprintf(infoJogada, "Peca Vermelha na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);

                        }else{
                            //caso contr�rio diz que est� numa jogada inv�lida
                            checkJogada = 1;
                        }

                        //se estiver em uma jogada invalida sai do switch
                        if(checkJogada == 1)
                            break;

                        //registo de jogadas
                        //adiciona � lista de jogadas a jogada atual
                        listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                        //verifica se o computador ganhou, e se sim declara vit�ria ao chamar a fun��o "vitoriaJogo"
                        if(verificaVitoria(tab) == 1)
                        {
                            vitoriaJogo(numJogadas, arrayJogadores[numJogadas%2], tab, listaJogadas);
                        }
                        break;

                    //caso selecione 2 coloca uma pedra no local gerado
                    case 2:

                        // se o computador n�o tiver mais pedras diz que � uma jogada invalida e sai do switch
                        if(arrayJogadores[numJogadas%2].pedra == 0)
                        {
                            checkJogada = 1;
                            break;
                        }

                        //caso ainda tenha pedras restantes tenta colocar a pedra no local gerado anteriormente
                        checkJogada = verificaPeca(tab,linha,coluna,'P');

                        //se a jogada correu bem decrementa o n�mero de pedras do jogador
                        if(checkJogada == 0)
                            arrayJogadores[numJogadas%2].pedra -= 1;

                        //registo de jogadas
                        // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                        sprintf(infoJogada, "Pedra na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                        //adiciona � lista de jogadas a jogada atual
                        listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                        break;

                    //caso selecione 3 incrementa o n�mero de linhas do tabuleiro
                    case 3:

                        //verifica se o utilizador ainda pode incrementar o tabuleiro caso contr�rio diz que � jogada inv�lida e sai do switch
                        if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                        {
                            checkJogada = 1;
                            break;
                        }

                        //tenta aumentar o tabuleiro
                        tab = aumentaLinhas(tab, &checkJogada);

                        //caso a opera��o seja realizada com sucesso decrementa o n�mero de vezes que o utilizador pode incrementar o tabuleiro
                        if(checkJogada == 0)
                            arrayJogadores[numJogadas%2].aumentarTabuleiro -= 1;

                        //registo de jogadas
                        // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                        sprintf(infoJogada, "Aumento de uma linha ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                        //adiciona � lista de jogadas a jogada atual
                        listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, tab.nLinhas, 0, infoJogada);

                        break;

                    //caso selecione 4 incrementa o n�mero de colunas do tabuleiro
                    case 4:

                        //verifica se o utilizador ainda pode incrementar o tabuleiro caso contr�rio diz que � jogada inv�lida e sai do switch
                        if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                        {
                            checkJogada = 1;
                            break;
                        }

                        //tenta aumentar o tabuleiro
                        tab = aumentaColunas(tab, &checkJogada);

                        //caso a opera��o seja realizada com sucesso decrementa o n�mero de vezes que o utilizador pode incrementar o tabuleiro
                        if(checkJogada == 0)
                            arrayJogadores[numJogadas%2].aumentarTabuleiro -= 1;

                        //registo de jogadas
                        // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                        sprintf(infoJogada, "Aumento de uma coluna ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                        //adiciona � lista de jogadas a jogada atual
                        listaJogadas = adicionarJogada(listaJogadas, tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, 0, tab.nColunas, infoJogada);

                        break;

                    //caso a op��o recebida n�o for uma das anteriores mostra esta mensagem de erro
                    default:
                        printf("Ocorreu  um erro, tente novamente!\n");
                        break;

                }

                //caso a jogada seja v�lida incrementa o n�mero de jogadas para passar para o pr�ximo jogador
                if(checkJogada == 0)
                {
                    numJogadas++;
                    break;
                }

            }while(checkJogada == 1);

            //imprime a informa��o sobre a jogada que ocorreu para o utilizador
            printf("%s\n", infoJogada);

            printf("--------------------------------------------------\n");
        }
        else
        {
            //caso seja a vez do utilizador a jogar
            while(1)
            {
                //mostra o utilizador atual
                printf("\n\n--------------------------------------------------\n");
                printf("Jogador %c.\n\n", arrayJogadores[numJogadas%2].identificacao);

                //mostra o estado do tabuleiro e as poss�veis jogadas do utilizador
                mostraTabuleiro(tab);
                menuJogadas(arrayJogadores[numJogadas%2]);
                printf("--------------------------------------------------\n");

                //verifica��o da op��o inserida pelo utilizador
                do{

                    printf("Escolha uma jogada: ");
                    scanf("%d", &opcao);
                }while(opcao < 0 || opcao > 7 && opcao != 9);

                //chama a fun��o "switchHumano" para decifrar, verificar e executar a opera��o desejada pelo utilizador
                switchJogadorHumano(numJogadas, &arrayJogadores, &tab, &listaJogadas, opcao, &checkJogada, 1);

                //se a jogada for v�lida incrementa o n�mero de jogadas para passar para o pr�ximo jogador e sai do ciclo "while"
                if(checkJogada == 0)
                {
                    numJogadas++;
                    break;
                }

            }
        }
    }
}

//fun��o de jogo para dois jogadores
void doisJogadores(int numJogadas, jogadores jogadorA, jogadores jogadorB, tabuleiro tab, ponteiroJogadas listaJogadas)
{
    //declara��o de vari�veis
    int checkJogada = 0;
    int opcao;

    //cria��o de um array para os jogadores para alternar entre os dois conforme a jogada
    jogadores arrayJogadores[2] = {jogadorA,jogadorB};

    //inicio do jogo
    while(1)
    {
        //mostra o jogador atual
        printf("\n\n--------------------------------------------------\n");
        printf("Jogador %c.\n\n", arrayJogadores[numJogadas%2].identificacao);

        //mostra o tabuleiro
        mostraTabuleiro(tab);
        //mostra as jogadas poss�veis para o utilizador
        menuJogadas(arrayJogadores[numJogadas%2]);
        printf("--------------------------------------------------\n");
        //verifica��o da op��o selecionada pelo utilizador
        do{

            printf("Escolha uma jogada: ");
            scanf("%d", &opcao);
        }while(opcao < 0 || opcao > 7 && opcao != 9);

        //envia para a fun��o os dados necess�rios para realizar a jogada selecionada
        switchJogadorHumano(numJogadas, &arrayJogadores, &tab, &listaJogadas, opcao, &checkJogada,2);

        //se a jogada correr bem passa para a pr�xima jogada
        if(checkJogada == 0)
            numJogadas++;

    }
}

//fun��o que determina o que fazer, dada um opera��o por um jogador
void switchJogadorHumano(int numJogadas, jogadores *arrayJogadores, tabuleiro *tab, ponteiroJogadas *listaJogadas, int opcao, int *checkJogada, int tipoJogo)
{
    //declara��o de vari�veis
    int linha, coluna;
    int nJogadasAnteriores = 0;

    char infoJogada[100];

    //caso o utilizador selecione a op��o
    switch(opcao)
        {
            // op��o 1 -> colocar pe�a verde
            case 1:
                //pede as coordenadas do tabuleiro onde pretende colocar a pe�a
                pedeCoordenadas(*tab,&linha,&coluna);
                //verifica se � possivel colocar a pe�a, e se sim coloca-a
                *checkJogada = verificaPeca(*tab,linha,coluna,'G');

                //se a fun��o de colocar pe�a devolver 1 significa que n�o foi possivel colocar a pe�a
                if(*checkJogada == 1)
                {
                    printf("\n\nJogada Invalida!\n");
                    //sai do switch
                    break;
                }

                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Peca Verde na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                //verifica se ap�s esta jogada existe uma condi��o de vit�ria
                if(verificaVitoria(*tab) == 1)
                {
                    //se sim chama a fun��o "vitoriaJogo"
                    vitoriaJogo(numJogadas, arrayJogadores[numJogadas%2], *tab, *listaJogadas);
                }

                break;

            // op��o 2 -> colocar pe�a amarela
            case 2:
                //pede as coordenadas do tabuleiro onde pretende colocar a pe�a
                pedeCoordenadas(*tab,&linha,&coluna);
                //verifica se � possivel colocar a pe�a, e se sim coloca-a
                *checkJogada = verificaPeca(*tab,linha,coluna,'Y');

                //se a fun��o de colocar pe�a devolver 1 significa que n�o foi possivel colocar a pe�a
                if(*checkJogada == 1)
                {
                    printf("\n\nJogada Invalida!\n");
                    //sai do switch
                    break;
                }

                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Peca Amarela na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                //verifica se ap�s esta jogada existe uma condi��o de vit�ria
                if(verificaVitoria(*tab) == 1)
                {
                    //se sim chama a fun��o "vitoriaJogo"
                    vitoriaJogo(numJogadas, arrayJogadores[numJogadas%2], *tab, *listaJogadas);
                }

                break;

            // op��o 3 -> colocar pe�a vermelha
            case 3:
                //pede as coordenadas do tabuleiro onde pretende colocar a pe�a
                pedeCoordenadas(*tab,&linha,&coluna);
                //verifica se � possivel colocar a pe�a, e se sim coloca-a
                *checkJogada = verificaPeca(*tab,linha,coluna,'R');

                //se a fun��o de colocar pe�a devolver 1 significa que n�o foi possivel colocar a pe�a
                if(*checkJogada == 1)
                {
                    printf("\n\nJogada Invalida!\n");
                    //sai do switch
                    break;
                }

                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Peca Vermelha na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                //verifica se ap�s esta jogada existe uma condi��o de vit�ria
                if(verificaVitoria(*tab) == 1)
                {
                    //se sim chama a fun��o "vitoriaJogo"
                    vitoriaJogo(numJogadas, arrayJogadores[numJogadas%2], *tab, *listaJogadas);
                }

                break;

            // op��o 4 -> colocar pedra
            case 4:
                //verifica se o jogador que est� a jogar atualmente ainda tem pedras para colocar
                if(arrayJogadores[numJogadas%2].pedra == 0)
                {
                    //se n�o tiver imprime uma mensagem na consola e sai do switch
                    printf("\nEste jogador esgotou as Pedras.\n");
                    *checkJogada = 1;
                    break;
                }

                //caso ainda tenha pedras para colocar, pede as coordenadas do tabuleiro onde pretende colocar a pedra
                pedeCoordenadas(*tab,&linha,&coluna);
                //verifica se � possivel colocar a pedra, e se sim coloca-a
                *checkJogada = verificaPeca(*tab,linha,coluna,'P');

                //se a fun��o de colocar pedra devolver 1 significa que n�o foi possivel colocar a pedra
                if(*checkJogada == 1)
                {
                    printf("\n\nJogada Invalida!\n");
                    //sai do switch
                    break;
                }

                //caso devolva 0 significa que colocou a pedra e por isso decrementa o n�mero de pedras do utilizador
                if(*checkJogada == 0)
                    arrayJogadores[numJogadas%2].pedra -= 1;

                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Pedra na linha %d, coluna %d pelo jogador %c.\n", linha, coluna, arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, linha, coluna, infoJogada);

                //neste caso � impossivel ganhar por colocar uma pedra

                break;

            // op��o 5 -> aumentar linhas do tabuleiro
            case 5:
                //verifica se o utilizador a jogar atualmente ainda pode fazer alguma altera��o ao tamanho do tabuleiro
                if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                {
                    //se n�o puder imprime uma mensagem na consola e sai do switch
                    printf("\nEste jogador esgotou os seus aumentos do tabuleiro.\n");
                    *checkJogada = 1;
                    break;
                }

                //caso ainda tenha aumentos para fazer, chama a fun��o que aumenta o n�mero de linhas do tabuleiro
                *tab = aumentaLinhas(*tab, checkJogada);

                //se a fun��o de aumentar o tabuleiro devolver '0' significa que conseguiu aumentar o tabuleiro
                if(*checkJogada == 0)
                {
                    //como aumentou o tabuleiro vai decrementar os aumentos restantes do utilizador
                    arrayJogadores[numJogadas%2].aumentarTabuleiro -= 1;
                } else
                {
                    //sen�o sai do switch
                    break;
                }


                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Aumento de uma linha ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, tab->nLinhas, 0, infoJogada);

                break;

            // op��o 6 -> aumentar colunas do tabuleiro
            case 6:
                //verifica se o utilizador a jogar atualmente ainda pode fazer alguma altera��o ao tamanho do tabuleiro
                if(arrayJogadores[numJogadas%2].aumentarTabuleiro == 0)
                {
                    //se n�o puder imprime uma mensagem na consola e sai do switch
                    printf("\nEste jogador esgotou os seus aumentos do tabuleiro.\n");
                    *checkJogada = 1;
                    break;
                }

                //caso ainda tenha aumentos para fazer, chama a fun��o que aumenta o n�mero de colunas do tabuleiro
                *tab = aumentaColunas(*tab, checkJogada);

                //se a fun��o de aumentar o tabuleiro devolver '0' significa que consegui aumentar o tabuleiro
                if(*checkJogada == 0)
                {
                    //como aumentou o tabuleiro vai decrementar os aumentos restantes do utilizador
                    arrayJogadores[numJogadas%2].aumentarTabuleiro -= 1;
                } else
                {
                    //sen�o sai do switch
                    break;
                }

                //registo de jogadas
                // imprime para a string "infoJogada" um pequeno coment�rio sobre a jogada que ocorreu
                sprintf(infoJogada, "Aumento de uma coluna ao tabuleiro pelo jogador %c.\n", arrayJogadores[numJogadas%2].identificacao);
                //adiciona � lista de jogadas a jogada atual
                *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, 0, tab->nColunas, infoJogada);

                break;

            // op��o 7 -> ver 'k' jogadas anteriores
            case 7:

                //imprime na consola uma mensagem a indicar o n�mero de jogadas que decorreram at� ao momento no jogo
                printf("\nOcorreram ate agora %d jogadas.\n", numJogadas);
                do{
                    //pede o n�mero de jogadas que o utilizador pretende ver e verifica o n�mero introduzido
                    printf("Ver ultimas 'k' jogadas: ");
                    scanf("%d", &nJogadasAnteriores);
                }while(nJogadasAnteriores < 0 || nJogadasAnteriores > numJogadas);

                printf("\n");

                //cria uma lista ligada auxiliar para ajudar na manipula��o da principal
                ponteiroJogadas aux;
                aux = *listaJogadas;

                //come�a no primeiro n� e vai at� ao n� n�mero de jogadas atual menos n�mero de jogadas que o utilizador pretende ver
                for(int i = 1; i <= (numJogadas-nJogadasAnteriores);i++)
                {
                    //passa para o pr�ximo n� da lista
                    aux = aux->next;
                }

                //neste momento encontra-se no primeiro n� que pretende mostrar ao utilizador e vai at� ao �ltimo n� da lista
                for(int i = 0; i < nJogadasAnteriores; i++)
                {
                    //mostra os dados do n� atual
                    mostrarJogada(aux);
                    //passa para o n� seguinte
                    aux = aux->next;
                }
                //coloca o checkJogada a '1', pois esta opera��o n�o significa que se ir� passar para a vez do outro jogador
                *checkJogada = 1;
                break;

            // op��o 9 -> interromper jogo
            case 9:
                //chama a fun��o interromper jogo e envia as vari�veis necess�rias para a func�o
                interromperJogo(tipoJogo,numJogadas,arrayJogadores[0],arrayJogadores[1],*tab,*listaJogadas);
                break;

            // op��o 0 -> desitir
            case 0:

                //pergunta ao utilizador se este pretende mesmo desistir
                printf("\nPretende mesmo desistir(y/n): ");
                scanf(" %c", &opcao);

                //caso o utilizador indique que sim
                if(opcao == 'y' || opcao == 'Y')
                {
                    //declara vit�ria ao outro jogador
                    printf("\n\n\n\n\nO jogador %c ganhou o jogo.\n\n\n", arrayJogadores[(numJogadas+1)%2].identificacao);

                    //registo de jogadas
                    // imprime para a string "infoJogada" que o jogador atual desistiu
                    sprintf(infoJogada, "O jogador %c desistiu.\n", arrayJogadores[numJogadas%2].identificacao);
                    //adiciona � lista de jogadas a jogada atual
                    *listaJogadas = adicionarJogada(*listaJogadas, *tab, arrayJogadores[numJogadas%2].identificacao, numJogadas, 0, 0, infoJogada);

                    //chama a fun��o terminar jogo
                    terminarJogo(*listaJogadas, tab);
                } else{
                    //caso o utilizador indique que n�o quer desistir volta a ser a sua vez de jogar
                    *checkJogada = 1;
                }

                break;

            //caso a op��o recebida n�o for uma das anteriores mostra esta mensagem de erro
            default:
                printf("Ocorreu  um erro, tente novamente!\n");
                break;

        }
}

//fun��o que termina o jogo
void terminarJogo(ponteiroJogadas listaJogadas, tabuleiro *tab)
{
    //declara��o de vari�veis
    int resultadoFicheiroJogadas;
    char nomeFicheiro[99];

    //pede ao utilizador o nome do ficheiro onde ser�o guardados os registos das jogadas realizadas
    printf("Indique o nome do ficheiro onde pretende guardar as jogadas: ");
    scanf("%s", nomeFicheiro);

    //adiciona ao nome a extens�o de ficheiro de texto, ".txt"
    strcat(nomeFicheiro, ".txt");

    //guarda as jogadas no ficheiro e recebe se correu bem ou n�o
    resultadoFicheiroJogadas = escreveJogadasFicheiro(nomeFicheiro, listaJogadas);

    //mostra no ecr� uma mensagem conforme tenha ou n�o conseguido guardar os dados no ficheiro de texto
    if(resultadoFicheiroJogadas)
    {
        printf("\nOcorreu um erro a guardar as jogadas no seu ficheiro!\n\n");
    } else
    {
        printf("\nO ficheiro com as jogadas foi criado.\n\n");
    }

    //liberta a mem�ria das vari�veis din�micas
    libertarMemoria(listaJogadas, tab);

    //termina o programa
    exit(0);
}

//fun��o que declara qual jogador ganhou e adiciona a jogada ao registo
void vitoriaJogo(int numJogadas, jogadores jogador, tabuleiro tab, ponteiroJogadas listaJogadas)
{
    //declara��o de vari�veis
    char infoJogada[100];

    //mostra na consola o jogador que ganhou e o estado do tabuleiro final
    printf("\n\n--------------------------------------------------");

    printf("\n\n\n\n\nO jogador %c ganhou o jogo.\n\n\n", jogador.identificacao);
    mostraTabuleiro(tab);

    printf("\n\n\n--------------------------------------------------\n\n");

    //adiciona ao registo de jogadas a jogada final, ou seja, a indicar qual jogador ganhou
    sprintf(infoJogada, "O jogador %c ganhou o jogo.\n", jogador.identificacao);
    listaJogadas = adicionarJogada(listaJogadas, tab, jogador.identificacao, numJogadas+1, 0, 0, infoJogada);

    //chama a fun��o "terminar jogo"
    terminarJogo(listaJogadas, &tab);

}

//fun��o que liberta a mem�ria alocada dinamicamente
void libertarMemoria(ponteiroJogadas listaJogadas, tabuleiro *tab)
{
    //lista jogadas auxiliar para ajudar na manipula��o da lista
    ponteiroJogadas aux;

    //libertar a tabela
    // liberta cada linha da tabela
    for(int i = 0; i < tab->nLinhas; i++)
        free(tab->tabuleiro[i]);

    // liberta a tabela em si
    free(tab->tabuleiro);

    //para cada jogada
    while(listaJogadas != NULL)
    {

        aux = listaJogadas;
        listaJogadas = listaJogadas->next;

        // liberta a tabela
        for(int i = 0; i < aux->tab.nLinhas; i++)
            free(aux->tab.tabuleiro[i]);

        free(aux->tab.tabuleiro);

        // liberta o n�
        free(aux);
    }
}
