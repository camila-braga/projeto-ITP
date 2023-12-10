/***
 * @file
 * @brief Responsável pela execução inicial do programa.
 *
 * Gerencia o menu do programa invocando os módulos adequados para cada opção.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Dados.h"
#include "Tabela.h"
#include "Pesquisa.h"
#include "TabelaGeral.h"

/**
 * Representa as opções de escolha do menu do programa.
 */
typedef enum
{
  CRIAR_TABELA = 1,
  LISTAR_TABELA = 2,
  CRIAR_LINHA = 3,
  LISTAR_DADOS = 4,
  PESQUISAR_VALOR = 5,
  APAGAR_TUPLA = 6,
  APAGAR_TABELA = 7,
  SAIR = 8,
  LIMPAR = 0 /**Apaga os arquivos do disco rígido*/
} Opcoes;

/**
 * Exibe na tela as opções do menu.
 */
void menu()
{
  printf("\n\n-------------------------------------------------------\n");
  printf("          Menu Principal. Opcoes disponiveis:\n");
  printf("-------------------------------------------------------\n");
  printf("%d - Criar tabela;\n", CRIAR_TABELA);
  printf("%d - Listar todas as tabelas;\n", LISTAR_TABELA);
  printf("%d - Criar uma nova linha na tabela;\n", CRIAR_LINHA);
  printf("%d - Listar todos os dados de uma tabela;\n", LISTAR_DADOS);
  printf("%d - Pesquisar valor em uma tabela;\n", PESQUISAR_VALOR);
  printf("%d - Apagar uma tupla (registro ou linha) de uma tabela;\n", APAGAR_TUPLA);
  printf("%d - Apagar uma tabela;\n", APAGAR_TABELA);
  printf("%d - SAIR.\n", SAIR);
  printf("%d - Excluir arquivos.\n", LIMPAR);
  printf("-------------------------------------------------------\n\n");
  printf("Digite a opcao desejada: ");
}

/**
 * Verifica se já existe um texto registrado igual ao requerido.
 * 
 * Recebe um vetor de textos e verifica se existe dois textos iguais nesse vetor. Retorna 0 se não existirem valores iguais ou, caso contrário, a posição de maior valor entre os dois textos comparados, ou seja, nunca retorna zero em caso verdadeiro.
 * 
 * @param n quantidade de textos a serem comparadas.
 * @param linhaASerInserida vetor com todos os textos.
 * @return retorna 0 se não existir dois textos iguais no vetor, caso contrário, retorna valor maior que zero.
 */
int verificarNomesIguais(int n, Texto linhaASerInserida[])
{
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      Texto a = linhaASerInserida[i];
      Texto b = linhaASerInserida[j];
      if (strcmp(a.vetor, b.vetor) == 0)
      {
        return j;
      }
    }
  }
  return 0;
}

/**
 * Representa a opção do menu de criar uma tabela.
 * 
 * Realiza a leitura do nome da tabela, verificando se este é válido, da quantidade de colunas da tabela, dos nomes das colunas (incluindo a chave primária) e seus tipos, criando um arquivo contendo essas informações e outro contendo a quantidade de tabelas e seus nomes (tabela geral.data).
 */
void criarTabela()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256); //Os nomes são limitados a 256 caracteres.
  while (tabelaGeral_contemTabela(nome))
  {
    printf("\t\tNao e possivel realizar essa acao: ja existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
    printf("\t\tDigite o nome da tabela: ");
    nome = texto_lerTerminalEmLoop(256);
  }

  printf("\tDigite a quantidade de colunas para tabela \"%s\": ", nome.vetor);
  int quantidadeColunas = texto_lerValorPositivoEmLoop();
  printf("\tDigite o nome da coluna de chave primaria para tabela \"%s\": ", nome.vetor);
  Texto nomeDasColunas[quantidadeColunas];
  char tiposDasColunas[quantidadeColunas];
  nomeDasColunas[0] = texto_lerTerminalEmLoop(256);
  tiposDasColunas[0] = 'i';
  int erro = 0;

  for (int i = 1; i < quantidadeColunas && !erro; i++)
  {
    printf("\tDigite o nome da coluna %d: ", i + 1);
    nomeDasColunas[i] = texto_lerTerminalEmLoop(256);

    int iguais = verificarNomesIguais(i + 1, nomeDasColunas);
    if (iguais)
    {
      erro = 1;
      printf("\t\tNao e possivel realizar essa acao: duas colunas com o nome \"%s\".\n", nomeDasColunas[iguais].vetor);
    }
    else
    {
      tiposDasColunas[i] = texto_lerTipoEmLoop();
    }
  }

  if (!erro)
  {
    Tabela tabela = tabela_criar(nome, quantidadeColunas, nomeDasColunas, tiposDasColunas);

    tabela_gravar(tabela);
    tabelaGeral_adicionarTabela(nome);

    printf("\n\n");
    tabela_exibirCabecalho(tabela);
    printf(">>Tabela criada com sucesso.\n\n");

    tabela_liberar(tabela);
  }
}

/**
 * Representa a opção do menu de exibir os dados de uma tabela.
 * 
 * Faz a leitura do nome da tabela, abre seu arquivo correspondente e exibe na tela seu cabeçalho com seus dados.
 */
void exibirDados()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    tabela_exibirCabecalho(tabela);
    tabela_exibirDados(tabela);
    tabela_liberar(tabela); // libera a estrutura nome também
    printf("\n");
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
  }
}

/**
 * Faz a leitura da chave primária retornando uma estrutura contendo suas informações.
 * 
 * @return Estrutura com os dados lidos. 
 */
Texto leituraDaChavePrimaria()
{
  int valor = texto_lerValorPositivoEmLoop();
  Texto texto;
  texto.capacidade = 32;
  texto.tamanho = 0;
  texto.vetor = calloc(32, sizeof(char));
  sprintf(texto.vetor, "%d", valor);
  texto.tamanho = strlen(texto.vetor);
  return texto;
}

/**
 * Faz as leituras dos dados da linha a ser inserida, retornando uma estrutura com os dados lidos.
 * 
 * Observação: Insere 'NULL' caso o usuário não queira adicionar um dado.
 * 
 * @param n quantidade de colunas
 * @param colunas Estrutura contendo os dados das colunas
 * @return Uma estrutura com os dados lidos
 */
Texto * leituraDeDados(int n, ColunaDaTabela colunas[])
{
  printf("\tDigite o valor da chave primaria: ");
  Texto *linhaASerInserida = calloc(n, sizeof(Texto));
  linhaASerInserida[0] = leituraDaChavePrimaria();
  for (int i = 1; i < n; i++)
  {
    ColunaDaTabela aux = colunas[i];
    printf("\tDeseja inserir um valor para coluna %s (s-sim , n-nao)?: ", aux.nome.vetor);
    char inserir;
    scanf("%c", &inserir);
    fflush(stdin);
    if (inserir == 's')
    {
      printf("\tDigite o valor do tipo de dado %c para a coluna %s: ", aux.tipo, aux.nome.vetor);
      linhaASerInserida[i] = texto_lerValorComTipo(aux.tipo);
    }
    else
    {
      Texto texto;
      texto.capacidade = 5;
      texto.tamanho = 4;
      texto.vetor = calloc(5, sizeof(char));
      sprintf(texto.vetor, "NULL");
      linhaASerInserida[i] = texto; //insere NULL caso o usuário não queira inserir um dado 
    }
  }
  return linhaASerInserida;
}

/**
 * Verifica se já existe uma chave com valor igual ao requerido, retornando 1 em caso de sucesso e 0, caso contrário.
 * 
 * @param tabela Estrutura com os dados da tabela.
 * @param linhaASerInserida Estrutura com o dado a ser verificado
 * @return 1 em caso de sucesso e 0, caso contrário
 */
int verificarExistenciaDaChave(Tabela tabela, Texto linhaASerInserida[])
{
  int erro = 0;
  int posicao = coluna_buscarValor(tabela.colunas[0], linhaASerInserida[0]);
  if (posicao != -1) // valor presente
  {
    erro = 1;
    printf("\t\tNao e possivel realizar essa acao: ja existe uma linha com a chave \"%s\".\n", linhaASerInserida[0].vetor);
  }
  return erro;
}

/**
 * Representa a opção do menu de adicionar linha em uma tabela.
 * 
 * Faz a leitura do nome da tabela e dos dados a serem adicionados e, em seguida, atualiza o arquivo da tabela, inserindo uma linha com os dados recentes.
 */
void adicionarDados()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    Texto *linhaASerInserida = leituraDeDados(tabela.quantidadeDeColunas, tabela.colunas);
    int erro = verificarExistenciaDaChave(tabela, linhaASerInserida);
    if (!erro)
    {
      tabela = tabela_adicionarLinha(tabela, linhaASerInserida);
      tabela_gravar(tabela);
      tabela_liberar(tabela); // libera nome também
      printf("\t>>Dados inseridos com sucesso.\n\n");
    }
    else
    {
      for (int i = 0; i < tabela.quantidadeDeColunas; i++)
      {
        free(linhaASerInserida[i].vetor);
      }
    }
    free(linhaASerInserida);
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
  }
  free(nome.vetor);
}

/**
 * Representa a opção do menu de apagar uma tabela.
 * 
 * Faz a leitura do nome da tabela e a apaga do disco rígido, atualizando o arquivo 'tabela geral.data', que contém a quantidade de tabelas e seus nomes.
 */
void apagarTabela()
{
  printf("Digite o nome da tabela a ser apagada: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_apagar(nome))
  {
    printf("\t>>Tabela \"%s\" apagada com sucesso.\n\n", nome.vetor);
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
  }
  free(nome.vetor);
}

/**
 * Representa a opção do menu de apagar uma linha de uma tabela.
 * 
 * Faz a leitura do nome da tabela e da chave desejada e apaga sua linha, atualizando o arquivo da tabela.
 */
void apagarTupla()
{
  printf("Digite o nome da tabela em que se encontra a tupla: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    printf("Digite a chave a ser removida: ");
    Texto chave = leituraDaChavePrimaria(tabela.colunas[0]);
    if (tabela_removeChave(tabela, chave))
    {
      printf("\t>>Tupla de chave \"%s\" apagada com sucesso.\n\n", chave.vetor);
    }
    else
    {
      printf("\t\tNao e possivel realizar essa acao: nao existe uma tupla com a chave \"%s\".\n", chave.vetor);
    }
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
  }
}

/**
 * Representa a opção do menu de pesquisar um valor em uma tabela.
 * 
 * Faz a leitura do nome da tabela e exibe as colunas disponíveis. Depois, faz a leitura do valor a ser pesquisado, exibindo as opções de pesquisa para, posteriormente, exibir os resultados da pesquisa.
 */
void pesquisarValores()
{
  printf("Digite o nome da tabela a ser pesquisada: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    tabela_exibirCabecalho(tabela);

    printf("Qual a coluna a ser pesquisada: ");
    Texto coluna = texto_lerTerminalEmLoop(256);
    int indice = -1;
    for (int i = 0; i < tabela.quantidadeDeColunas && indice == -1; i++)
    {
      if (strcmp(coluna.vetor, tabela.colunas[i].nome.vetor) == 0)
      {
        indice = i;
      }
    }

    if (indice != -1)
    {
      pesquisar(tabela, indice);
      tabela_liberar(tabela);
    }
    else
    {
      printf("\t\tNao e possivel realizar essa acao: nao existe uma coluna com o nome \"%s\".\n", coluna.vetor);
    }
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
  }
}

/**
 * Função principal.
 *
 * @return Resultado da execução do programa. 0 indica ausência de erros.
 */
int main(void)
{

  Opcoes opcao;
  do
  {
    menu(); // imprime as opções de escolha para o usuário.
    scanf("%d", &opcao);
    fflush(stdin);

    //! Instruções de acordo com a escolha do usuário.
    switch (opcao)
    {
    case CRIAR_TABELA:
      criarTabela();
      break;
    case LISTAR_TABELA:
      tabelaGeral_listar();
      break;
    case CRIAR_LINHA:
      adicionarDados();
      break;
    case LISTAR_DADOS:
      exibirDados();
      break;
    case PESQUISAR_VALOR:
      pesquisarValores();
      break;
    case APAGAR_TUPLA:
      apagarTupla();
      break;
    case APAGAR_TABELA:
      apagarTabela();
      break;
    case SAIR:
      break;
    case LIMPAR:
      tabelaGeral_limpar();
      break;
    default:
      printf("Opcao invalida\n\n");
    }

  } while (opcao != SAIR);

  return 0;
}
