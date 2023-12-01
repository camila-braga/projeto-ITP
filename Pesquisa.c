
#include "Dados.h"
#include "Tabela.h"
#include "Pesquisa.h"

typedef enum
{
    MAIOR = 1,
    MAIOR_OU_IGUAL = 2,
    IGUAL = 3,
    MENOR_OU_IGUAL = 4,
    MENOR = 5,
    PROXIMO = 6
} Regra;

// retorna
// -1 se o primeiro valor for menor que o segundo
// 0 se os valores são iguais
// 1 se o primeiro é maior que o segundo valor
int compararValores(Texto primeiro, Texto segundo, char tipo)
{
    switch (tipo)
    {
    case 'c':
        return primeiro.vetor[0] - segundo.vetor[0];
    case 'i':
    {
        int aint, bint;
        sscanf(primeiro.vetor, "%d", &aint);
        sscanf(segundo.vetor, "%d", &bint);
        return aint - bint;
    }
    case 's':
        return strcmp(primeiro.vetor, segundo.vetor);
    case 'f':
    case 'd':
    {
        // TODO incluir no readme
        double adouble, bdouble;
        sscanf(primeiro.vetor, "%lf", &adouble);
        sscanf(segundo.vetor, "%lf", &bdouble);
        return adouble - bdouble;
    }
    }
    return 0;
}

int compararProximo(Texto primeiro, Texto segundo)
{
    return strstr(primeiro.vetor, segundo.vetor) != NULL;
}

int deveExibir(Texto valor, Texto comparar, Regra regra, char tipo)
{
    // TODO FIX incluir no readme
    if (strcmp("NULL", comparar.vetor) == 0)
    {
        return 0;
    }

    int exibir = 0;
    if (regra == PROXIMO)
    {
        exibir = compararProximo(comparar, valor);
    }
    else
    {
        int resultado = compararValores(comparar, valor, tipo);
        switch (regra)
        {
        case MENOR_OU_IGUAL:
            exibir = resultado <= 0;
            break;
        case MENOR:
            exibir = resultado < 0;
            break;
        case IGUAL:
            exibir = resultado == 0;
            break;
        case MAIOR:
            exibir = resultado > 0;
            break;
        case MAIOR_OU_IGUAL:
            exibir = resultado >= 0;
        }
    }
    return exibir;
}

void pesquisa_exibir(Tabela tabela, int indice, Texto valor, Regra regra)
{
    tabela_exibirCabecalho(tabela);

    for (int linha = 0; linha < tabela.quantidadeDeLinhas; linha++)
    {
        char tipo = tabela.colunas[indice].tipo;
        Texto comparar = tabela.colunas[indice].dados[linha];
        if (deveExibir(valor, comparar, regra, tipo))
        {
            printf("|");
            for (int i = 0; i < tabela.quantidadeDeColunas; i++)
            {
                printf(" %14s |", tabela.colunas[i].dados[linha].vetor);
            }
            printf("\n");
        }
    }
    printf("----------------------------------------------------------------------\n");
}

void pesquisar(Tabela tabela, int indice)
{
    printf("Qual o valor a ser comparado: ");
    char tipo = tabela.colunas[indice].tipo;
    Texto valor = texto_lerValorComTipo(tipo);

    printf("-----------    Opcoes de Busca    -----------\n");
    printf("Valores maiores que o valor informado (%d)\n", MAIOR);
    printf("Valores maiores ou iguais que o valor informado (%d)\n", MAIOR_OU_IGUAL);
    printf("Valores iguais ao valor informado (%d)\n", IGUAL);
    printf("Valores menores ou iguais que o valor informado (%d)\n", MENOR_OU_IGUAL);
    printf("Valores menores que o valor informado (%d)\n", MENOR);
    if (tipo == 's')
    {
        printf("Valores proximos ao valor informado (%d)\n", PROXIMO);
    }
    printf("Qual a opcao de busca: ");
    Regra regra;
    scanf("%d", &regra);
    fflush(stdin);
    if (regra >= 1 && regra <= 5 || (regra == 6 && tipo == 's'))
    {
        pesquisa_exibir(tabela, indice, valor, regra);
    }
    else
    {
        printf("\t\tNao e possivel realizar essa acao: nao existe a opcao \"%d\".\n", regra);
    }
}
