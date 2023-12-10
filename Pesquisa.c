
#include "Dados.h"
#include "Tabela.h"
#include "Pesquisa.h"

/**
 * Representa as opções de escolha do usuário referente à pesquisa de valores. 
 */
typedef enum
{               /**Para valores maiores do que o solicitado;*/
    MAIOR = 1, /**Para valores maiores ou iguais ao solicitado;*/
    MAIOR_OU_IGUAL = 2,  /**Para valores iguais ao solicitado;*/
    IGUAL = 3, /**Para valores menores ou iguais ao solicitado;*/
    MENOR_OU_IGUAL = 4, /**Para valores menores do que o solicitado;*/
    MENOR = 5, /**Para valores próximos ao solicitado. Apenas para valores do tipo string.*/
    PROXIMO = 6 
} Regra;

/**
 *  Compara valores de duas estruturas, convertendo-os nos tipos 'c', 'i', 'f', 'd', 's', retornando um valor negativo se o primeiro valor for menor do que o segundo, 0 se os valores forem iguais ou um valor positivo se o primeiro valor for maior do que o segundo.
 * 
 * Observação: Para o caso em que o tipo de dado for 'f', a implementação será idêntica ao caso em que o tipo de dado for 'd'. 
 * @param primeiro Estrutura contendo os dados do primeiro valor
 * @param segundo Estrutura contendo os dados do segundo valor
 * @param tipo Tipo de dado referente aos valores a serem comparados
 * @return um valor negativo se o primeiro valor for menor do que o segundo, 0 se os valores forem iguais ou um valor positivo se o primeiro valor for maior do que o segundo.
 */
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
        double adouble, bdouble;
        sscanf(primeiro.vetor, "%lf", &adouble);
        sscanf(segundo.vetor, "%lf", &bdouble);
        return adouble - bdouble;
    }
    }
    return 0;
}

/**
 * Verifica se o segundo argumento é substring do primeiro. Retorna 1 em caso de sucesso e 0, caso contrário.
 * 
 * @param primeiro Estrutura de texto.
 * @param segundo Estrutura de texto.
 * @return 1 caso de sucesso e 0, caso contrário.
 */
int compararProximo(Texto primeiro, Texto segundo)
{
    return strstr(primeiro.vetor, segundo.vetor) != NULL; //A função strstr retorna um ponteiro para a primeira ocorrência da substring.
}

/**
 * Verifica a linha satisfaz a regra informada.
 * 
 * @param valor Estrutura de texto contendo o valor solicitado pelo usuário.
 * @param comparar Estrutura de texto contendo os valores a serem comparados.
 * @param regra Opção de pesquisa escolhida pelo usuário.
 * @param tipo Tipo de dado
 * @return 1 em caso de sucesso e 0, caso contrário. 
 */
int deveExibir(Texto valor, Texto comparar, Regra regra, char tipo)
{
    if (strcmp("NULL", comparar.vetor) == 0) //caso o valor a ser comparado seja NULL
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

/**
 * Exibe na tela os resultados da pesquisa de valores.
 * 
 * @param tabela Estrutura contendo os dados da tabela.
 * @param indice posição da coluna
 * @param valor Estrutura contendo os dados do valor a ser pesquisado
 * @param regra Estrutura referente à opção de pesquisa escolhida pelo usuário.
 */
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

/**
 * Exibe na tela o menu com as opções de pesquisa, faz a leitura da escolha do usuário e do valor a ser comparado e exibe os resultados da pesquisa.
 * 
 * @param tabela Estrutura contendo os dados da tabela
 * @param indice Posição da coluna
 */
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
