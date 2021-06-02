#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"

#include "utils.h"

//fun��o que cria um estrutura do tipo tabuleiro e a inicializa
tabuleiro inicializarTabuleiro()
{

    //declara a estrutura do tipo tabuleiro
    tabuleiro tab;

    //recebe um n�mero random entre 3 e 5, valor este que vai ser o n�mero de linhas/colunas do tabuleiro de jogo
    int tam = intUniformRnd(3,5);

    //cria array din�mico com 'tam' n�mero de linhas
    tab.tabuleiro = (char**)malloc(sizeof(char*)*tam);

    //verifica se a aloca��o de mem�ria foi realizada com sucesso
    if(tab.tabuleiro == NULL)
    {
        printf("Ocorreu um erro a alocar mem�ria!");
        return;
    }

    //para cada linha cria 'tam' n�mero de colunas
    for (int i=0; i<tam; i++)
    {
        //aloca o espa�o para cada coluna
        tab.tabuleiro[i] = (char*)malloc(sizeof(char)* tam );

        //verifica se estas foram alocadas com sucesso
        if(tab.tabuleiro[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            free(tab.tabuleiro);
            return;
        }

        //inicializar o tabuleiro com espa�os em branco
        for (int j = 0; j < tam; j++)
        {
            tab.tabuleiro[i][j] = ' ';
        }

    }

    //inicializa o n�mero de linhas e colunas com o n�mero random recebido em "tam"
    tab.nLinhas = tam;
    tab.nColunas = tam;

    return tab;
}

//fun��o que imprime o estado do tabuleiro na consola
void mostraTabuleiro(tabuleiro tab)
{
    printf("  ");
    //mostra o n�mero das colunas
    for(int i = 0; i < tab.nColunas;i++)
        printf(" %d", i+1);

    //para cada linha
    for(int i = 0; i < tab.nLinhas; i++)
    {
        //imprime o n�mero da linha
        printf("\n%d |", i+1);

        //para cada coluna da linha
        for(int j = 0; j < tab.nColunas; j++)
        {
            //imprime o caractere nessa linha e coluna do tabuleiro
            printf("%c|", tab.tabuleiro[i][j]);
        }
    }
    printf("\n\n");
}

//fun��o que pede as coordenadas do tabuleiro que ele pretende afetar
void pedeCoordenadas(tabuleiro tab, int *linha, int *coluna)
{
    //verifica o input do utilizador e verifica se � um valor de linhas corretas
    do{
        printf("Linha: ");
        scanf("%d", linha);
    }while((*linha) < 1 || (*linha) > tab.nLinhas);

    //verifica o input do utilizador e verifica se � um valor de colunas corretas
    do{
        printf("Coluna: ");
        scanf("%d", coluna);
    }while((*coluna) < 1 || (*coluna) > tab.nColunas);

}

//fun��o que verifica se � possivel colocar a pe�a que o pretende no local dito pelo mesmo
int verificaPeca(tabuleiro tab, int linha, int coluna, char pecaColocar)
{
    //ao valor introduzido pelo utilizador para as linhas e colunas � decrementado um para se tornar no �ndice para a tabela
    linha = linha-1;
    coluna = coluna-1;

    //vari�vel que guarda a pe�a que � necess�ria no local designado para colocar a pe�a que o utilizador pretende
    char pecaRequerida = ' ';

    switch(pecaColocar)
    {

        // para a pedra e para a pe�a verde � necess�rio uma local vazio
        case 'P':
            //a peca requerida a estar no local para a Pedra e igual a da peca Verde
        case 'G':
            pecaRequerida = ' ';
            break;

        // para a pe�a amarela tem que estar no local um pe�a amarela
        case 'Y':
            pecaRequerida = 'G';
            break;

        //para a pe�a vermelha tem que estar um pe�a amarela
        case 'R':
            pecaRequerida = 'Y';
            break;

        //caso n�o seja nenhuma desta a pe�a do utilizador mostra erro e sai da fun��o
        default:
            printf("Peca invalida, tente novamente!\n");
            return 1;
    }

    //se a pe�a no tabuleiro n�o for a requerida devolve '1'
    if(tab.tabuleiro[linha][coluna] != pecaRequerida)
    {
        return 1;
    }

    //como a pe�a no tabuleiro � a requerida pode colocar a pe�a do utilizador e devolve '0'
    tab.tabuleiro[linha][coluna] = pecaColocar;

    return 0;
}

//fun��o que aumenta o n�mero de linhas do tabuleiro
tabuleiro aumentaLinhas(tabuleiro tab, int *checkJogada)
{
    //a variavel "checkJogada" aponta para uma vari�vel onde � guardado um inteiro que indica se esta fun��o conseguiu atingir o seu objetivo com sucesso

    //cria uma nova estrutura tabuleiro auxiliar
    tabuleiro aux;

    //copia do tabuleiro recebido o n�mero de linhas e colunas, mas como queremos aumentar as linhas incrementamos as linhas em 1
    aux.nLinhas = tab.nLinhas+1;
    aux.nColunas = tab.nColunas;

    // realoca espa�o para o novo n�mero de linhas, sendo que usa o tabuleiro recebido como primeiro par�metro para manter os dados da tabela para as linhas que j� estavam criadas
    aux.tabuleiro = (char**)realloc(tab.tabuleiro, sizeof(char*)*aux.nLinhas);

    //verifica se a aloca��o correu bem
    if(aux.tabuleiro == NULL)
    {
        printf("Ocorreu um erro a alocar mem�ria!");
        //coloca '1' no endere�o apontado por "checkJogada" caso corra mal a aloca��o
        *checkJogada = 1;
        return tab;
    }

    //para a �ltima linha que � a nova, aloca espa�o para as diversas colunas
    aux.tabuleiro[aux.nLinhas-1] = (char*)malloc(sizeof(char)* aux.nColunas);

    //verifica se a aloca��o correu bem
    if(aux.tabuleiro[aux.nLinhas-1] == NULL)
    {
        printf("Erro na alocacao de memoria");
        //coloca '1' no endere�o apontado por "checkJogada" caso corra mal a aloca��o
        *checkJogada = 1;
        return tab;
    }

    // inicializa as colunas da �ltima linha como espa�os em branco
    for (int j = 0; j < aux.nColunas; j++)
    {
        aux.tabuleiro[aux.nLinhas-1][j] = ' ';
    }

    //devolve o tabuleiro auxiliar e coloca '0' no endere�o apontado por "checkJogada"
    *checkJogada = 0;
    return aux;
}

//fun��o que aumenta o n�mero de colunas do tabuleiro
tabuleiro aumentaColunas(tabuleiro tab, int *checkJogada)
{
    //a vari�vel "checkJogada" aponta para uma vari�vel onde � guardado um inteiro que indica se esta fun��o conseguiu atingir o seu objetivo com sucesso

    //estrutura tabuleiro auxiliar onde ser�o realizadas as altera��es
    tabuleiro aux;

    //utiliza o mesmo n�mero de linhas do tabuleiro recebido, mas incrementa em 1 o n�mero de colunas
    aux.nLinhas = tab.nLinhas;
    aux.nColunas = tab.nColunas+1;

    //d� realloc �s linhas do tabuleiro recebido para o auxilizar para preservar os dados do tabuleiro
    aux.tabuleiro = (char**)realloc(tab.tabuleiro, sizeof(char*)*aux.nLinhas);

    //verifica se a aloca��o foi realizada com sucesso
    if(aux.tabuleiro == NULL)
    {
        printf("Ocorreu um erro a alocar mem�ria!");
        //coloca o checkJogada a '1', pois deu erro
        *checkJogada = 1;
        return tab;
    }

    //para cada uma das linhas do tabuleiro
    for(int i = 0; i < aux.nLinhas; i++)
    {
        //realoca as colunas com o novo n�mero de colunas, realloc para preservar os dados anteriores
        aux.tabuleiro[i] = (char*)realloc(aux.tabuleiro[i], sizeof(char)* aux.nColunas);

        //verifica se a aloca��o foi realizada com sucesso
        if(aux.tabuleiro[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            //coloca o checkJogada a '1', pois deu erro
            *checkJogada = 1;
            return tab;
        }

        //inicializa a nova coluna como vazio
        aux.tabuleiro[i][aux.nColunas-1] = ' ';
    }

    //devolve o tabuleiro auxiliar e coloca o checkJogada a '0'
    *checkJogada = 0;
    return aux;
}

//fun��o que cria uma c�pia do tabuleiro recebido
tabuleiro copiarTabuleiro(tabuleiro tabRecebido)
{

    //cria uma nova estrutura tabuleiro
    tabuleiro tab;

    //aloca o mesmo n�mero de linhas do tabuleiro recebido
    tab.tabuleiro = (char**)malloc(sizeof(char*)*tabRecebido.nLinhas);

    //verifica se a aloca��o correu bem
    if(tab.tabuleiro == NULL)
    {
        printf("Ocorreu um erro a alocar mem�ria!");
        return;
    }

    //para cada linha
    for (int i=0; i<tabRecebido.nLinhas; i++)
    {
        //aloca espa�o para as colunas
        tab.tabuleiro[i] = (char*)malloc(sizeof(char)*tabRecebido.nColunas);

        //verifica se a aloca��o correu bem
        if(tab.tabuleiro[i] == NULL)
        {
            printf("Erro na alocacao de memoria");
            free(tab.tabuleiro);
            return;
        }

        //para cada c�lula da tabela copia o valor da tabela recebida
        for (int j = 0; j < tabRecebido.nColunas; j++)
        {
            tab.tabuleiro[i][j] = tabRecebido.tabuleiro[i][j];
        }

    }

    //coloca o n�mero de linhas e colunas iguais aos da tabela recebida
    tab.nLinhas = tabRecebido.nLinhas;
    tab.nColunas = tabRecebido.nColunas;

    //devolve a nova estrutura tabela
    return tab;
}

//fun��o que verifica se um dos jogadores ganhou
int verificaVitoria(tabuleiro tab)
{
    //devolve 1 se se encontrar um condi��o de vit�ria


    int verifica;

    //verifica��o das linhas
    //para cada linha
    for(int i = 0; i < tab.nLinhas; i++)
    {
        //reseta o contador "verifica" para cada verifica��o de linha
        verifica = 0;

        //se a primeira coluna estiver vazia passa para a pr�xima linha
        if(tab.tabuleiro[i][0] == ' ')
            continue;

        //para cada coluna da linha
        for(int j = 0; j < tab.nColunas; j++)
        {
            //verifica se � igual � primeira, se for igual e diferente de um espa�o em branco incrementa o contador "verifica"
            if(tab.tabuleiro[i][j] == tab.tabuleiro[i][0] && tab.tabuleiro[i][j] != ' ')
            {

                verifica++;
            }else
            {
                //caso uma falhe n�o vale a pena verificar as restantes colunas por isso sai do segundo ciclo for
                break;
            }
        }

        //se o contador "verifica" tiver o mesmo n�mero que o n�mero de colunas significa que ganhou
        if(verifica == tab.nColunas)
            return 1;
    }

    //verifica��o das colunas
    //para cada coluna
    for(int i = 0; i < tab.nColunas; i++)
    {
        //reseta o contador "verifica"
        verifica = 0;

        //se a primeira linha da coluna estiver vazia passa para a pr�xima coluna
        if(tab.tabuleiro[0][i] == ' ')
            continue;

        //para cada linha
        for(int j = 0; j < tab.nLinhas; j++)
        {

            //verifica se o conteudo da atual � igual � primeira e diferente de um espa�o em branco, se forem verdade estas condi��es incrementa o contador "verifica"
            if(tab.tabuleiro[j][i] == tab.tabuleiro[0][i] && tab.tabuleiro[j][i] != ' ')
            {
                verifica++;
            }else
            {
                //se uma das linhas dessa coluna estiver incorreta sai do segundo ciclo for
                break;
            }
        }

        //se o n�mero no "verifica" for igual ao n�mero de linhas significa que tem uma coluna completa igual
        if(verifica == tab.nLinhas)
            return 1;
    }

    //verifica��o diagonais
    //se o n�mero de linhas for igual ao n�mero de colunas, ou seja, a matriz for quadrada verifica as diagonais
    if(tab.nLinhas == tab.nColunas)
    {

        //verifica diagonal principal
        //verificamos as c�lulas nas posi��es 1x1, 2x2, 3x3, etc
        verifica = 0;

        //o valor de i vai de '0' at� 'nLinhas-1', pois � 'i' menor que nLinhas
        for(int i = 0; i < tab.nLinhas; i++)
        {
            //verifica se as c�lulas da diagonal principal s�o iguais � primeira posi��o da diagonal e se s�o diferentes de espa�o em branco
            if(tab.tabuleiro[i][i] == tab.tabuleiro[0][0] && tab.tabuleiro[i][i] != ' ')
            {
                verifica++;
            }else
            {
                // se for diferente ou um espa�o em branco n�o acaba a verifica��o, pois, uma j� falhou
                break;
            }
        }

        //se o n�mero em "verifica" for igual ao n�mero de linhas significa que foi encontrada vit�ria na diagonal principal
        if(verifica == tab.nLinhas)
            return 1;


        //verifica diagonal secund�ria
        //verificamos as c�lulas nas posi��es 3x1, 2x2, 3x1, exemplo para uma matriz 3x3
        verifica = 0;

        //come�a na primeira linha, '0', e na �ltima coluna, 'nLinhas-1', enquanto o 'i' for menor que o n�mero total de linhas executa,
        // e incremeta o n�mero de linhas e decrementa o n�mero de colunas
        for(int i = 0, j = tab.nLinhas-1; i < tab.nLinhas; i++, j--)
        {

            //verifica se as c�lulas da diagonal secund�ria s�o iguais � �ltima, encontrada no canto inferior esquerdo do tabuleiro
            // verifica ainda se alguma delas � um espa�o em branco
            if(tab.tabuleiro[i][j] == tab.tabuleiro[tab.nLinhas-1][0] && tab.tabuleiro[i][j] != ' ')
            {
                verifica++;
            }else
            {
                //se n�o for verdade significa que pelo menos uma c�lula est� incorreta, por isso, n�o vale a pena continuar
                break;
            }

        }

        //se o valor de "verifica" for igual ao n�mero de linhas significa que encontrou vit�ria na diagonal secund�ria
        if(verifica == tab.nLinhas)
            return 1;
    }

    //caso n�o encontre vit�ria devolve '0'
    return 0;
}
