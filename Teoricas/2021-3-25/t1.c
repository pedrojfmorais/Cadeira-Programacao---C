#include <stdio.h>
#include <string.h>

#define MAX 100

struct data
{
    int dia, mes, ano;
};

struct dados
{
    char nome[100];
    char nConta[15];
    int montante;
    struct data in;
};

typedef struct dados cliente;

void escreve_info(cliente a)
{

    printf("\n Nome: %s\t N Conta: %s \t Saldo: %d \n", 
           a.nome, a.nConta, a.montante);

}

cliente obtem_info()
{
    cliente t;
    
    printf("\n");

    printf("Nome: ");
    scanf(" %99[^\n]", t.nome);
    
    printf("N Conta: ");
    scanf(" %14s", t.nConta);
    
    printf("Saldo: ");
    scanf(" %d", &(t.montante));

    return t;

}

void mostraTodos(cliente banco[], int totalClientes)
{

    printf("\nExistem %d clientes: \n", totalClientes);

    for (int i = 0; i < totalClientes; i++)
    {
        escreve_info(banco[i]);
    }
    
}

void adicionaCliente(cliente banco[], int *totalClientes)
{

    if (*totalClientes == MAX)
    {
        printf("Tabela completa \n");
        return;
    }
    
    cliente novo;
    novo = obtem_info();
    
    banco[(*totalClientes)] = novo;
    (*totalClientes)+=1;
}

void eliminaCliente(cliente banco[], int *totalClientes)
{
    int i;
    char nContaEliminar[100];

    printf("Insira o numero de conta do cliente a eliminar: ");
    scanf(" %s", nContaEliminar);

    for (i = 0; i < *totalClientes && strcmp(nContaEliminar, banco[i].nConta); i++);

    if (i == *totalClientes)
    {
        printf("\n\n !! -- Cliente nao existe -- !! \n\n");
        return;
    }
    
    banco[i] = banco[*totalClientes-1];
    (*totalClientes)--;

}

int main(int argc, char const *argv[])
{
    
    cliente banco[MAX];
    int totalClientes = 0;
    int input = 0;

    while (1)
    {   
        printf("\n");
        printf(" 1 - Novo Cliente\n");
        printf(" 2 - Mostrar Clientes\n");
        printf(" 3 - Eliminar Cliente\n");
        printf(" 0 - Sair\n");

        printf("\n Opcao: ");
        scanf(" %d", &input);

        switch (input)
        {
        case 1:
            adicionaCliente(banco, &totalClientes);
            break;
        case 2:
            mostraTodos(banco, totalClientes);
            break;
        case 3:
            eliminaCliente(banco, &totalClientes);
            break;
        case 0:
            return 0;
            break;
        
        default:
            printf("\n Opcao incorreta, tente novamente! \n\n");
            break;
        }
    }  

    return 0;
}
