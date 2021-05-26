#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registoJogadas.h"
#include "jogadores.h"
#include "tabuleiro.h"

//fun��o que adiciona um novo n� � lista ligada, no fim da lista fornecida
ponteiroJogadas adicionarJogada(ponteiroJogadas listaJogadas, tabuleiro tab, char idJogador, int nJogada, int linha, int coluna, char infoJogada[])
{
    //cria dois ponteiro, um para o novo n� da lista e outro auxiliar para maniopular a lista ligada
    ponteiroJogadas nova, aux;

    //aloca mem�ria para o novo n� da lista
    nova = malloc(sizeof(jogada));

    //verifica se a mem�ria foi bem alocada
    if (nova == NULL)
    {
        printf("Erro na realocacao!\n");
        return listaJogadas;
    }

    //chama a fun��o copiarTabuleiro para criar uma c�pia do tabuleiro atual
    nova->tab = copiarTabuleiro(tab);

    //guarda os dados recebidos como par�metro nas vari�veis do n�
    nova->jogador = idJogador;
    nova->nJogada = nJogada+1; //guarda nJogada+1, pois o n�mero de jogada � iniciado em '0', e para o utilizador as jogadas come�am em '1'
    nova->linhaAfetada = linha;
    nova->colunaAfetada = coluna;
    strcpy(nova->infoJogada,infoJogada);

    //coloca o pr�ximo n� da lista como NULL, pois, este ainda n�o existe
    nova->next = NULL;

    //se a lista fornecida estiver vazia coloca o novo n� no inicio da lista
    if(listaJogadas == NULL)
    {
        listaJogadas = nova;
    } else
    {
        //caso contr�rio percorre a lista fornecida at� chegar ao �ltimo n�
        aux = listaJogadas;

        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        // e coloca o novo n� como o �ltimo n� da lista
        aux->next = nova;
    }

    //devolve o primeiro n� da lista
    return listaJogadas;
}

//fun��o que mostra as vari�veis de um n� da listya fornecido
void mostrarJogada(ponteiroJogadas listaJogadas)
{

    printf("-------------------- Jogada %d --------------------\n", listaJogadas->nJogada);
    mostraTabuleiro(listaJogadas->tab);
    printf("Jogador %c\n", listaJogadas->jogador);
    printf("Jogada numero %d\n", listaJogadas->nJogada);
    printf("Linha %d, Coluna %d\n", listaJogadas->linhaAfetada, listaJogadas->colunaAfetada);
    printf("%s", listaJogadas->infoJogada);
    printf("--------------------------------------------------\n\n");

}

//fun��o que escreve a lista de jogadas para um ficheiro
int escreveJogadasFicheiro(char *nomeFicheiro, ponteiroJogadas listaJogadas)
{

    //abre o ficheiro para escrita, nome do ficheiro � recebido por par�metro
    FILE *f = fopen(nomeFicheiro, "w");

    //verifica se conseguiu abrir o ficheiro
    if(f == NULL)
    {
        fclose(f);
        return 1;
    }

    //enquanto n�o chegar ao fim da lista de jogadas
    while(listaJogadas != NULL)
    {

        //declara duas vari�veis
        char linhaTabela[99], auxTexto[99];

        //coloca no ficheiro o n�mero da jogada
        fprintf(f,"-------------------- Jogada %d --------------------\n", listaJogadas->nJogada);

        //copia para a vari�vel "linhaTabela" dois espa�os em branco, quest�o apenas visual para o ficheiro
        strcpy(linhaTabela, "  ");

        //para cada coluna
        for(int i = 0; i < listaJogadas->tab.nColunas;i++)
        {
            //imprime na vari�vel "auxTexto" o n�mero da coluna
            sprintf(auxTexto, " %d", i+1);

            //e concateniza com o conteudo de "linhaTabela"
            strcat(linhaTabela, auxTexto);
        }

        //imprime para o ficheiro as colunas da tabela
        fprintf(f,"%s", linhaTabela);

        //para cada linha da tabela
        for(int i = 0; i < listaJogadas->tab.nLinhas; i++)
        {
            //imprime para "auxTexto" o n�mero da linha
            sprintf(auxTexto, "\n%d |", i+1);
            //e copia para a vari�vel "linhaTabela"
            strcpy(linhaTabela, auxTexto);

            //para cada coluna
            for(int j = 0; j < listaJogadas->tab.nColunas; j++)
            {
                //imprime para "auxTexto" a pe�a guardada naquela linha e coluna
                sprintf(auxTexto, "%c|", listaJogadas->tab.tabuleiro[i][j]);
                //e concateniza com o que j� tinha a pe�a em "auxTexto"
                strcat(linhaTabela, auxTexto);
            }
            //imprime esta linha para o ficheiro
            fprintf(f,"%s", linhaTabela);
        }
        //adiciona duas linhas ao tabuleiro, apenas visual
        fprintf(f,"\n\n", linhaTabela);

        //guarda no ficheiro os retantes dados da jogada
        fprintf(f,"Jogador %c\n", listaJogadas->jogador);
        fprintf(f,"Jogada numero %d\n", listaJogadas->nJogada);
        fprintf(f,"Linha %d, Coluna %d\n", listaJogadas->linhaAfetada, listaJogadas->colunaAfetada);
        fprintf(f,"%s", listaJogadas->infoJogada);
        fprintf(f,"--------------------------------------------------\n\n");

        //ap�s escrever todos os dados deste n� passa para o pr�ximo
        listaJogadas = listaJogadas->next;

    }

    //fecha o ficheiro
    fclose(f);

    return 0;
}
