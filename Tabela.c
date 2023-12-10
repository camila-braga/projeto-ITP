
#include "Tabela.h"

/**
 * Cria uma tabela.
 * 
 * Recebe como argumentos o nome da tabela, a quantidade de colunas que a tabela terá, um vetor com os nomes das colunas e outro com os tipos de dados associados à elas. Retorna uma estrutura preenchida com essas informações.
 * 
 * @param nome Estrutura contendo os dados do nome da tabela.
 * @param quantidadeDeColunas A quantidade de colunas que a tabela terá.
 * @param nomesDasColunas Vetor de string contendo os nomes das colunas.
 * @param tiposDasColunas Vetor de string contendo os tipos de dados associados às colunas.
 * @return Estrutura preenchidas com as informações recebidas.
 */
Tabela tabela_criar(Texto nome, int quantidadeDeColunas, Texto nomesDasColunas[], char tiposDasColunas[])
{
    Tabela tabela;
    tabela.nome = nome;
    tabela.quantidadeDeColunas = quantidadeDeColunas;
    tabela.quantidadeDeLinhas = 0;
    tabela.colunas = calloc(quantidadeDeColunas, sizeof(ColunaDaTabela));
    for (int i = 0; i < quantidadeDeColunas; i++)
    {
        ColunaDaTabela coluna;
        coluna.quantidadeDeLinhas = 0;
        coluna.nome = nomesDasColunas[i];
        coluna.tipo = tiposDasColunas[i];
        coluna.dados = NULL;
        tabela.colunas[i] = coluna;
    }
    return tabela;
}

/**
 * Cria um arquivo referente a uma tabela.
 * 
 * Recebe como argumento uma estrutura contendo informações de uma tabela adquiridas previamente em outra função e cria um arquivo para essa tabela, repassando as informações contidas na estrutura para esse arquivo.
 * 
 * Observação: o arquivo será nomeado pelo nome da tabela.
 * @param tabela Estrutura contendo as informações de uma tabela.
 */
void tabela_gravar(Tabela tabela)
{
    FILE *arquivo = fopen(tabela.nome.vetor, "w");
    texto_gravar(tabela.nome, arquivo);
    fprintf(arquivo, "%d\n", tabela.quantidadeDeColunas);
    fprintf(arquivo, "%d\n", tabela.quantidadeDeLinhas);
    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        ColunaDaTabela aux;
        aux = tabela.colunas[i];
        fprintf(arquivo, "%c\n", aux.tipo);
        texto_gravar(aux.nome, arquivo);
        for (int j = 0; j < tabela.quantidadeDeLinhas; j++)
        {
            Texto linha = aux.dados[j];
            texto_gravar(linha, arquivo);
        }
    }
    fclose(arquivo);
}

/**
 * Faz a leitura dos dados de um arquivo referente a uma tabela.
 * 
 * Recebe como argumento uma estrutura de texto contendo os dados do nome de uma tabela, abre o arquivo correspondente à essa tabela, em modo leitura e faz a leitura de seus dados, retornando uma estrutura contendo os dados lidos.
 * 
 * @param nome Estrutura de texto contendo os dados do nome da tabela.
 * @return Uma estrutura contendo os dados lidos.
 */
Tabela tabela_recuperar(Texto nome)
{
    Tabela tabela;
    FILE *arquivo = fopen(nome.vetor, "r");
    tabela.nome = texto_recuperar(arquivo);
    fscanf(arquivo, "%d", &tabela.quantidadeDeColunas);
    fscanf(arquivo, "%d", &tabela.quantidadeDeLinhas);
    tabela.colunas = calloc(tabela.quantidadeDeColunas, sizeof(ColunaDaTabela));
    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        ColunaDaTabela aux;
        fscanf(arquivo, " %c", &aux.tipo);
        aux.nome = texto_recuperar(arquivo);
        aux.dados = calloc(tabela.quantidadeDeLinhas, sizeof(Texto));
        aux.quantidadeDeLinhas = tabela.quantidadeDeLinhas;
        for (int j = 0; j < tabela.quantidadeDeLinhas; j++)
        {
            aux.dados[j] = texto_recuperar(arquivo);
        }
        tabela.colunas[i] = aux;
    }
    fclose(arquivo);
    return tabela;
}

/**
 * Liberação da memória alocada dinamicamente para a estrutura tabela.
 *  
 * @param tabela Estrutura de texto contendo os dados da tabela.
 */
void tabela_liberar(Tabela tabela)
{
    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        ColunaDaTabela aux = tabela.colunas[i];
        for (int j = 0; j < tabela.quantidadeDeLinhas; j++)
        {
            free(aux.dados[j].vetor);
        }
        free(aux.dados);
        free(aux.nome.vetor);
    }
    free(tabela.nome.vetor);
    free(tabela.colunas);
}

/**
 * Exibe na tela o cabeçalho de uma tabela. 
 * 
 * Recebe como parâmetro uma estrutura contendo o nome de uma tabela, a quantidade de linhas e colunas, os nomes e os tipos das colunas e exibe essas informações na tela.
 *  
 * @param tabela Estrutura de texto contendo os dados da tabela.
 */
void tabela_exibirCabecalho(Tabela tabela)
{
    printf("----------------------------------------------------------------------\n");
    printf("| \tTabela: %s (%d x %d)\n", tabela.nome.vetor, tabela.quantidadeDeLinhas, tabela.quantidadeDeColunas);
    printf("----------------------------------------------------------------------\n");
    printf("|");
    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        printf(" %10s (%c) |", tabela.colunas[i].nome.vetor, tabela.colunas[i].tipo);
    }
    printf("\n----------------------------------------------------------------------\n");
}

/**
 * Exibe na tela os dados das colunas de uma tabela.
 * 
 * Recebe como parâmetro uma estrutura contendo os dados de uma tabela e exibe na tela os dados de cada coluna.
 *  
 * @param tabela Estrutura de texto contendo os dados da tabela.
 */
void tabela_exibirDados(Tabela tabela)
{
    for (int linha = 0; linha < tabela.quantidadeDeLinhas; linha++)
    {
        printf("|");
        for (int i = 0; i < tabela.quantidadeDeColunas; i++)
        {
            printf(" %14s |", tabela.colunas[i].dados[linha].vetor);
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------\n");
}

/**
 * Adiciona uma linha para cada coluna de uma tabela.
 * 
 * Recebe como parâmetro uma estrutura texto contendo os dados a serem adicionados e uma estrutura contendo os dados da tabela. Em seguida, atualiza a estrutura Tabela com os dados da estrutura Texto retornando-a no final.
 *  
 * @param tabela Estrutura de texto contendo os dados da tabela.
 * @param dados Estrutura de string contendo os dados a serem adicionados nas colunas da tabela.
 * @return Estrutura Tabela contendo os dados da tabela atualizados.
 */
Tabela tabela_adicionarLinha(Tabela tabela, Texto dados[])
{
    tabela.quantidadeDeLinhas += 1;
    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        tabela.colunas[i].quantidadeDeLinhas = tabela.quantidadeDeLinhas;
        tabela.colunas[i].dados = realloc(tabela.colunas[i].dados, tabela.quantidadeDeLinhas * sizeof(Texto));
        tabela.colunas[i].dados[tabela.quantidadeDeLinhas - 1] = dados[i];
    }
    return tabela;
}

/**
 * Verifica se um dado existe nas colunas de uma tabela.
 * 
 * Recebe como parâmetros uma estrutura contendo os dados da coluna de uma tabela e outra contendo os dados de um valor. Depois, compara cada dado da coluna com esse valor, retornando a posição do dado valor na coluna em caso de sucesso (quando são iguais) e -1, caso contrário.
 *  
 * @param coluna Estrutura de texto contendo os dados da tabela.
 * @param valor Estrutura de texto contendo os dados de um valor.
 * @return -1 se o valor não estiver presente. Caso contrário, retorna a posição do valor na coluna.
 */
int coluna_buscarValor(ColunaDaTabela coluna, Texto valor)
{
    for (int i = 0; i < coluna.quantidadeDeLinhas; i++)
    {
        if (strcmp(valor.vetor, coluna.dados[i].vetor) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Remove uma linha (tupla) de uma tabela.
 * 
 * Recebe como parâmetros uma estrutura contendo os dados de uma tabela e outra contendo os dados de um valor correspondente à chave da linha a ser removida. Depois, localiza sua posição na coluna, caso ela exista e atualiza o arquivo da tabela com os dados restantes, excluindo-se os referentes à essa posição. Retorna 1 caso a remoção da linha seja realizada com sucesso e 0 caso a chave solicitada não exista.
 *  
 * @param tabela Estrutura de texto contendo os dados da tabela.
 * @param chave Estrutura de texto contendo os dados da chave referente à linha a ser removida
 * @return 1 caso a remoção da linha seja realizada com sucesso e 0 caso a chave não exista.
 */
int tabela_removeChave(Tabela tabela, Texto chave)
{
    int indice = -1;
    for (int i = 0; i < tabela.quantidadeDeLinhas && indice == -1; i++)
    {
        if (strcmp(chave.vetor, tabela.colunas[0].dados[i].vetor) == 0)
        {
            indice = i;
        }
    }
    if (indice == -1)
    {
        return 0;
    }

    FILE *arquivo = fopen(tabela.nome.vetor, "w");
    texto_gravar(tabela.nome, arquivo);
    fprintf(arquivo, "%d\n", tabela.quantidadeDeColunas);
    fprintf(arquivo, "%d\n", tabela.quantidadeDeLinhas - 1); //Pois removerá a tupla

    for (int i = 0; i < tabela.quantidadeDeColunas; i++)
    {
        ColunaDaTabela aux;
        aux = tabela.colunas[i];
        fprintf(arquivo, "%c\n", aux.tipo);
        texto_gravar(aux.nome, arquivo);
        for (int j = 0; j < tabela.quantidadeDeLinhas; j++)
        {
            if (j != indice)
            {
                Texto linha = aux.dados[j];
                texto_gravar(linha, arquivo);
            }
        }
    }
    fclose(arquivo);
    tabela_liberar(tabela);
    return 1;
}