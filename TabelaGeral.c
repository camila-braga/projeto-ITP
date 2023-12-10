#include <stdio.h>
#include <stdlib.h>

#include "Dados.h"
#include "TabelaGeral.h"

#define NOME_DA_TABELA_GERAL "tabela geral.data"

/**
 * Faz a leitura dos dados de um arquivo aberto em modo de leitura, atribuindo os dados lidos em uma estrutura de strings. Os dados do arquivo estão organizados na seguinte sequência: o primeiro dado corresponde à quantidade de tabelas existentes, enquanto que os dados restantes correspondem aos nomes das tabelas, representados pela estrutura Texto.
 * 
 * @param arquivo Arquivo a ser lido.
 * @param n Ponteiro para quantidade de tabelas.
 * @return Uma estrutura de Texto contendo os dados lidos, além de passar por referência o dado correspondente à quantidade de tabelas.
 */
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

/**
 * Grava no arquivo os dados atualizados sobre a quantidade de tabelas e seus nomes.
 *
 * @param arquivo Arquivo a ter dados gravados. Deve estar aberto no modo de escrita.
 * @param quantidadeDeTabelas Quantidade atualizada.
 * @param nomesDasTabelas Texto com os dados atualizados.
 */
void tabelaGeral_gravarDados(FILE *arquivo, int quantidadeDeTabelas, Texto nomesDasTabelas[])
{
  fprintf(arquivo, "%d\n", quantidadeDeTabelas);
  for (int i = 0; i < quantidadeDeTabelas; i++)
  {
    texto_gravar(nomesDasTabelas[i], arquivo);
  }
}

/**
 * Cria ou atualiza um arquivo contendo a quantidade de tabelas e seus respectivos nomes, sempre que uma nova tabela é criada.
 * 
 * Caso o arquivo não exista, um novo é criado. Caso contrário, seus dados são atualizados.
 *
 * @param nomeDaNovaTabela Estrutura com o nome da nova tabela criada previamente.
 */
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
    for(int i=0;i<quantidadeDeTabelas;i++){
      free(nomesDasTabelas[i].vetor);
    }
    free(nomesDasTabelas);
  }
}

/**
 * Recebe uma estrutura de texto que corresponde a um nome e verifica se esse nome já existe dentro de um arquivo.
 * 
 * Abre um arquivo em modo leitura, realiza a leitura de seus dados e compara se o dado recebido é igual a algum dado lido. Retorna 1 em caso de sucesso e 0, caso contrário.
 * 
 * @param nome Estrutura de Texto.
 * @return 1 se o nome já existir e 0, caso contrário.
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
    free(nomesDasTabelas);
  }
  return contem;
}

/**
 * Apaga do disco rígido todos os arquivos salvos.
 */
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
    for(int i=0;i<quantidadeDeTabelas;i++){
      free(nomesDasTabelas[i].vetor);
    }
    free(nomesDasTabelas);
  }
}

/**
 * Apaga do disco rígido uma tabela específica e atualiza o arquivo que lista os nomes das tabelas existentes.
 * 
 * Recebe como argumento uma estrutura contendo o nome da tabela a ser apagada e atualiza os dados do arquivo que contém os nomes de todas as tabelas existentes, excluindo-se o nome da tabela que foi apagada. 
 * @param excluindo Estrutura contendo os dados a serem deletados.
 * @return 1 se a tabela existir e a remoção for realizada e 0, caso a tabela não exista.
 */
int tabelaGeral_apagar(Texto excluindo)
{
  FILE *arquivo = fopen(NOME_DA_TABELA_GERAL, "r");
  if (arquivo != NULL)
  {
    int quantidadeDeTabelas;
    Texto *nomesDasTabelas = tabelaGeral_recuperarDados(arquivo, &quantidadeDeTabelas);
    fclose(arquivo);

    int indice = -1;
    for (int i = 0; i < quantidadeDeTabelas; i++)
    {
      if (strcmp(excluindo.vetor, nomesDasTabelas[i].vetor) == 0)
      {
        indice = i;
      }
    }

    if (indice != -1)
    {
      arquivo = fopen(NOME_DA_TABELA_GERAL, "w");
      fprintf(arquivo, "%d\n", quantidadeDeTabelas - 1);
      for (int i = 0; i < quantidadeDeTabelas; i++)
      {
        if (i != indice)
          texto_gravar(nomesDasTabelas[i], arquivo);
      }
      fclose(arquivo);
      remove(excluindo.vetor);
      return 1;
    }
    for(int i=0;i<quantidadeDeTabelas;i++){
      free(nomesDasTabelas[i].vetor);
    }
    free(nomesDasTabelas);
  }
  return 0;
}

/**
 * Lista os nomes das tabelas existentes.
 * 
 * Faz a leitura dos dados do arquivo 'tabela geral.data' e exibe na tela os dados correspondentes aos nomes das tabelas.
 */
void tabelaGeral_listar(){
  FILE *arquivo = fopen(NOME_DA_TABELA_GERAL, "r");
  if (arquivo != NULL)
  {
    int quantidadeDeTabelas;
    Texto *nomesDasTabelas = tabelaGeral_recuperarDados(arquivo, &quantidadeDeTabelas);
    fclose(arquivo);

    printf("-----  Tabelas  -----\n");
    for(int i=0;i<quantidadeDeTabelas;i++){
      printf("%s\n", nomesDasTabelas[i].vetor);
    }
    printf("---------------------\n\n");
    
    for(int i=0;i<quantidadeDeTabelas;i++){
      free(nomesDasTabelas[i].vetor);
    }
    free(nomesDasTabelas);
  }
}