#include <stdio.h>
#include <stdlib.h>

#include "Dados.h"
#include "TabelaGeral.h"

#define NOME_DA_TABELA_GERAL "tabela geral.data"

Texto *tabelaGeral_recuperarDados(FILE *arquivo, int *n)
{
  int quantidadeDeTabelas;
  fscanf(arquivo, "%d ", &quantidadeDeTabelas);
  Texto *nomes = calloc(quantidadeDeTabelas, sizeof(Texto));
  for (int i = 0; i < quantidadeDeTabelas; i++)
  {
    nomes[i] = texto_recuperar(arquivo);
  }
  *n = quantidadeDeTabelas;
  return nomes;
}

void tabelaGeral_gravarDados(FILE *arquivo, int quantidadeDeTabelas, Texto nomesDasTabelas[])
{
  fprintf(arquivo, "%d\n", quantidadeDeTabelas);
  for (int i = 0; i < quantidadeDeTabelas; i++)
  {
    texto_gravar(nomesDasTabelas[i], arquivo);
  }
}

void tabelaGeral_adicionarTabela(Texto nomeDaNovaTabela)
{
  FILE *arquivo = fopen(NOME_DA_TABELA_GERAL, "r");
  if (arquivo == NULL)
  {
    arquivo = fopen(NOME_DA_TABELA_GERAL, "w");
    fprintf(arquivo, "1\n");
    texto_gravar(nomeDaNovaTabela, arquivo);
    fclose(arquivo);
  }
  else
  {
    int quantidadeDeTabelas;
    Texto *nomesDasTabelas = tabelaGeral_recuperarDados(arquivo, &quantidadeDeTabelas);
    fclose(arquivo);

    nomesDasTabelas = realloc(nomesDasTabelas, (quantidadeDeTabelas + 1) * sizeof(Texto));
    nomesDasTabelas[quantidadeDeTabelas] = nomeDaNovaTabela;

    arquivo = fopen(NOME_DA_TABELA_GERAL, "w");
    tabelaGeral_gravarDados(arquivo, quantidadeDeTabelas + 1, nomesDasTabelas);
    fclose(arquivo);
  }
}

/**
 * @return 1 se o nome estiver presente e 0 em caso contrário.
 */
int tabelaGeral_contemTabela(Texto nome)
{
  int contem = 0;
  FILE *arquivo = fopen(NOME_DA_TABELA_GERAL, "r");
  if (arquivo != NULL)
  {
    int quantidadeDeTabelas;
    Texto *nomesDasTabelas = tabelaGeral_recuperarDados(arquivo, &quantidadeDeTabelas);
    fclose(arquivo);

    for (int i = 0; i < quantidadeDeTabelas; i++)
    {
      if (strcmp(nome.vetor, nomesDasTabelas[i].vetor) == 0)
      {
        contem = 1;
      }
      free(nomesDasTabelas[i].vetor);
    }
  }
  return contem;
}

void tabelaGeral_limpar()
{
  FILE *arquivo = fopen(NOME_DA_TABELA_GERAL, "r");
  if (arquivo != NULL)
  {
    int quantidadeDeTabelas;
    Texto *nomesDasTabelas = tabelaGeral_recuperarDados(arquivo, &quantidadeDeTabelas);
    fclose(arquivo);

    for (int i = 0; i < quantidadeDeTabelas; i++)
    {
      remove(nomesDasTabelas[i].vetor);
    }
    remove(NOME_DA_TABELA_GERAL);
  }
}