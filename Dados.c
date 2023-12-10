
#include <string.h>

#include "Dados.h"

// Funções auxiliares para verificação de nomes válidos para as tabelas

/**
 * Verifica se o caractere é uma letra minúscula.
 *
 * @param c Caractere sendo verificado.
 * @return 1 se o caractere for uma letra minúscula e 0 em caso contrário.
 */
int ehMinuscula(char c) { return c >= 'a' && c <= 'z'; }

/**
 * Verifica se o caractere é uma letra maiúscula.
 *
 * @param c Caractere sendo verificado.
 * @return 1 se o caractere for uma letra maiúscula e 0 em caso contrário.
 */
int ehMaiscula(char c) { return c >= 'A' && c <= 'Z'; }

/**
 * Verifica se o caractere é um dígito.
 *
 * @param c Caractere sendo verificado.
 * @return 1 se o caractere for um dígito e 0 em caso contrário.
 */
int ehDigito(char c) { return c >= '0' && c <= '9'; }

/**
 * Verifica se o caractere é um símbolo.
 *
 * @param c Caractere sendo verificado.
 * @return 1 se o caractere for um símbolo e 0 em caso contrário.
 */
int ehSimbolo(char c) { return c == '.' || c == '_' || c == ' ' || c == '-'; }

/**
 * Verifica se um nome é válido.
 *
 * Os nomes das tabelas possuem restrições quanto aos caracteres. Para serem válidos, os nomes devem ser compostos por letras, dígitos, símbolos '-', '_', '.' ou espaço, além de não poderem ser vazios nem começarem por espaço ou símbolo.
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
 * Os dados são salvos em dois campos no seguinte formato: "%d %s\n", correspondendo ao tamanho do texto e ao texto em si.
 * @param texto texto a ser gravado.
 * @param arquivo Arquivo onde serão gravados os dados. Ele deve estar aberto em modo de escrita de caracteres.
 */
void texto_gravar(Texto texto, FILE *arquivo)
{
    fprintf(arquivo, "%d %s\n", texto.tamanho, texto.vetor);
}

/**
 * Recupera os dados de um texto de um arquivo aberto em modo de leitura de caracteres.
 *
 * Assume que os dados foram salvos no formato da função @see texto_gravar.
 * @param arquivo Arquivo que será lido. Deve estar aberto no formado de leitura de caracteres.
 * @return Uma estrutura de Texto com os dados lidos.
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

/**
 *Faz a leitura de um texto e verifica se ele é válido. Caso seja válido, retorna uma estrutura com os dados lidos e, em caso contrário, solicita ao usuário que digite outro texto.
 *  
 * Para ser válido, o texto digitado deve conter apenas letras, numeros, ' ', '_', '-' ou '.' além de iniciar apenas por letra ou dígito.
 * @param capacidade Espaço do vetor para leitura dos dados.
 * @return Uma estrutura de texto com os dados lidos.
 */
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

/**
 * Realiza a leitura de um inteiro positivo e verifica se é um dado válido. Caso seja válido, retorna o dado lido e, em caso contrário, solicia ao usuário um novo dado.
 * 
 * Para ser válido, o número deve ser um inteiro não negativo.
 * @return Um inteiro contendo o dado lido.
 */
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

/**
 * Faz a leitura de um caractere e verifica se o dado digitado é válido. Para ser válido, o caractere deve ser apenas 'i', 'f', 'd', 'c' ou 's'. Em caso de sucesso, retorna o dado. Caso contrário, solicita ao usuário um dado novo.
 *
 * @return Um caractere contendo o dado lido.
 */
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

/**
 * Faz a leitura e tratamento de um texto, retornando uma estrutura com os dados desse texto.
 * 
 * Realiza a leitura caractere a caractere, enquanto não for digitado um '\\n' ou um '\\0'. Caso seja digitado '\\n', realiza o tratamento que consiste em sobrepor esse último caractere digitado por '\\0'.
 * 
 * @return Uma estrutura de texto com os dados lidos.
 */
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

/**
 * Faz a leitura e conversão de dados de acordo com a opção escolhida pelo usuário.
 * 
 * Recebe como argumento o tipo de dado da coluna escolhida pelo usuário, faz a leitura dos dados, os converte em string e depois armazena os dados convertidos no vetor de string. 
 * Observação: Para a variável "tipo" igual a 'f' ou 'd', a leitura e tratamento serão as mesmas.
 * @param tipo Tipo de dado da coluna escolhida previamente pelo usuário.
 * @return Uma estrutura de texto com os dados lidos.
 */
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
