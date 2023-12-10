
#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <string.h>

#include "Dados.h"

/**
 *  Representa uma coluna de uma tabela.
 * 
 * Representa uma coluna de uma tabela. Uma coluna tem um nome, que é representado pela estrutura de Texto, um tipo associado, que pode ser 'i', 'f', 'd', 'c' ou 's', a quantidade de linhas presentes na coluna e um vetor para armazenar os dados da coluna.
 */
typedef struct { /** Nome da coluna */
    Texto nome;  /** o tipo de dado associado à coluna. */
    char tipo;   /** quantidade de linhas. */
    int quantidadeDeLinhas;  /** Os dados da coluna */
    Texto * dados;  
} ColunaDaTabela;

/**
 * Representa uma tabela.
 * 
 * Representa uma tabela de dados do sistema. Uma tabela possui um nome, que é representado pela estrutura de Texto, um vetor para armazenar os dados de cada uma das colunas e uma variável para indicar a quantidade de colunas presentes na tabela. Os detalhes de cada coluna serão armazenados pela estrutura ColunaDaTabela. Além disso, possui um campo para indicar a quantidade linhas das tabelas, ou seja, a quantdade de dados em cada coluna.
 */
typedef struct { /** Nome da tabela*/
    Texto nome; /**Quantidade de colunas da tabela*/
    int quantidadeDeColunas; /**Quantidade de linhas da tabela*/
    int quantidadeDeLinhas; /**dados das colunas da tabela*/
    ColunaDaTabela * colunas; 
} Tabela;

Tabela tabela_criar(Texto nome, int quantidadeDeColunas, Texto nomeDasColunas[], char tipoDasColunas[]);
void tabela_gravar(Tabela tabela);
Tabela tabela_recuperar(Texto nome);
void tabela_liberar(Tabela tabela);
void tabela_exibirCabecalho(Tabela tabela);
void tabela_exibirDados(Tabela tabela);
int tabela_removeChave(Tabela tabela, Texto chave);

Tabela tabela_adicionarLinha(Tabela tabela, Texto dados []);

// retorna -1 se o valor não estiver na coluna, em caso contrário, retorna a posição em que ele se encontra
int coluna_buscarValor(ColunaDaTabela coluna, Texto valor);

#endif
