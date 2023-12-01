
#include <string.h>

#include "Dados.h"

// Funções auxiliares para verificação de nomes válidos para as tabelas

/**
 * Verifica se o caractere é uma letra minúscula
 *
 * @param c Caractere sendo verificado
 * @return 1 se o caractere for uma letra minúscula e 0 em caso contrário
 */
int ehMinuscula(char c) { return c >= 'a' && c <= 'z'; }

/**
 * Verifica se o caractere é uma letra maiúscula
 *
 * @param c Caractere sendo verificado
 * @return 1 se o caractere for uma letra maiúscula e 0 em caso contrário
 */
int ehMaiscula(char c) { return c >= 'A' && c <= 'Z'; }

// TODO comentar
int ehDigito(char c) { return c >= '0' && c <= '9'; }

// TODO comentar
int ehSimbolo(char c) { return c == '.' || c == '_' || c == ' ' || c == '-'; }

/**
 * Verifica se um nome é válido
 *
 * Os nomes das tabelas possuem restrições quanto aos caracteres. Os nomes podem ser compostos
 * por letras, dígitos e os símbolos '-', '_', '.' e espaço.
 * @param nome Ponteiro para nome a ser verificado.
 * @param tamanho Quantidade de caracteres do nome.
 * @return 1 caso o nome seja válido e 0 em caso contrário.
 */
int verificaNomeDaTabelaValido(char *nome, int tamanho)
{
    int condicao = (tamanho > 0) && !ehSimbolo(nome[0]);
    for (int i = 0; i < tamanho; i++)
    {
        char c = nome[i];
        int min = ehMinuscula(c);
        int mai = ehMaiscula(c);
        int dig = ehDigito(c);
        int sim = ehSimbolo(c);
        if (min + mai + dig + sim == 0)
        {
            condicao = 0;
        }
    }
    return condicao;
}

/**
 * Grava os dados do texto em um arquivo aberto em modo de escrita de caracteres.
 *
 * Os dados são salvos em dois campos no seguinte formato: "%d %s\n".
 * @param texto Texto a ser gravado.
 * @param FILE Arquivo onde serão gravados os dados. Ele deve estar aberto em modo de escrita de caracteres.
 */
void texto_gravar(Texto texto, FILE *arquivo)
{
    fprintf(arquivo, "%d %s\n", texto.tamanho, texto.vetor);
}

/**
 * Recupera os dados de um texto de um arquivo aberto em modo de leitura de caracteres.
 *
 * Assume que os dados foram salvos no formato da função @see salvarTexto.
 * @param arquivo Arquivo que será lido. Deve estar aberto no formado de leitura de caracteres.
 * @return uma estrutura de Texto com os dados lidos.
 */
Texto texto_recuperar(FILE *arquivo)
{
    Texto lido;
    lido.tamanho = 0;
    lido.capacidade = 0;
    lido.vetor = NULL;
    fscanf(arquivo, " %d ", &lido.tamanho);
    lido.capacidade = lido.tamanho + 1;
    lido.vetor = calloc(lido.capacidade, sizeof(char));
    fgets(lido.vetor, lido.capacidade, arquivo);
    fflush(stdin);
    return lido;
}

Texto texto_lerTerminalEmLoop(int capacidade)
{
    Texto lido;
    lido.capacidade = capacidade;
    lido.tamanho = 0;
    lido.vetor = calloc(lido.capacidade, sizeof(char));
    int nomeValido = 1;
    do
    {
        fgets(lido.vetor, lido.capacidade, stdin);
        lido.tamanho = strlen(lido.vetor);
        if (lido.tamanho > 0 && lido.vetor[lido.tamanho - 1] == '\n')
        {
            lido.vetor[lido.tamanho - 1] = '\0';
            lido.tamanho -= 1;
        }
        nomeValido = verificaNomeDaTabelaValido(lido.vetor, lido.tamanho);
        if (nomeValido == 0)
        {
            printf("\t\tNome \"%s\" invalido! Deve conter apenas letras, numeros, ' ', '_', '-' ou '.' e deve iniciar por letra ou digito.\n", lido.vetor);
            printf("\t\tPor favor, tente outra vez: ");
        }
    } while (nomeValido == 0);
    return lido;
}

int texto_lerValorPositivoEmLoop()
{
    int valor;
    scanf("%d", &valor);
    while (valor <= 0)
    {
        printf("\t\tValor invalido! O valor deve ser positivo.\n");
        printf("\t\tPor favor, tente outra vez: ");
        scanf("%d", &valor);
    }
    fflush(stdin);
    return valor;
}

char texto_lerTipoEmLoop()
{
    printf("\tDigite o tipo de dado ('i', 'f', 'd', 'c' ou 's'): ");
    char tipo;
    scanf(" %c", &tipo);
    while (tipo != 'i' && tipo != 'f' && tipo != 'd' && tipo != 'c' && tipo != 's')
    {
        printf("\t\tValor invalido! O tipo deve ser um caractere 'i', 'f', 'd', 'c' ou 's'.\n");
        printf("\t\tPor favor, tente outra vez: ");
        scanf(" %c", &tipo);
    }
    fflush(stdin);
    return tipo;
}

Texto texto_lerValorDoTipoString()
{
    Texto texto;
    texto.capacidade = 0;
    texto.tamanho = 0;
    texto.vetor = NULL;
    char c;
    do
    {
        scanf("%c", &c);
        texto.vetor = realloc(texto.vetor, texto.capacidade + 1);
        texto.vetor[texto.capacidade] = c;
        texto.capacidade += 1;
    } while (c != '\0' && c != '\n');
    texto.vetor[texto.capacidade - 1] = '\0';
    texto.tamanho = texto.capacidade - 1;
    fflush(stdin);
    return texto;
}


Texto texto_lerValorComTipo(char tipo)
{
    if(tipo == 's'){
        return texto_lerValorDoTipoString();
    }

    Texto texto;
    texto.capacidade = 32;
    texto.tamanho = 0;
    texto.vetor = calloc(texto.capacidade, sizeof(char));
    switch(tipo){
        case 'i':
        {
            int valor;
            scanf("%d", &valor);
            sprintf(texto.vetor, "%d", valor);
            break;
        }
        case 'f':
        case 'd':
        {
            double valor;
            scanf("%lf", &valor);
            sprintf(texto.vetor, "%lf", valor);
            break;
        }
        case 'c':
        {
            char valor;
            scanf("%c", &valor);
            sprintf(texto.vetor, "%c", valor);
            break;
        }
    }
    fflush(stdin);
    texto.tamanho = strlen(texto.vetor);
    return texto;
}

int mainTeste()
{
    /*
    Entrada:
    9 palavra 1
    9 palavra 2
    9 palavra 3
    Saída:
    10 9 palavra 1
    10 9 palavra 2
    */
    Texto texto = texto_recuperar(stdin);
    printf("%d %d %s\n", texto.capacidade, texto.tamanho, texto.vetor);
    texto = texto_recuperar(stdin);
    printf("%d %d %s\n", texto.capacidade, texto.tamanho, texto.vetor);

    return 0;
}
