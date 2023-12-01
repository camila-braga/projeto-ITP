
#include "Tabela.h"

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

// retorna -1 se o valor não estiver presente, caso contrário, retorna a posição do valor na coluna
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
    fprintf(arquivo, "%d\n", tabela.quantidadeDeLinhas - 1);

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