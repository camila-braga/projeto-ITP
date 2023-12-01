
#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <string.h>

#include "Dados.h"

typedef struct {
    Texto nome;
    char tipo;
    int quantidadeDeLinhas;
    Texto * dados;
} ColunaDaTabela;

typedef struct {
    Texto nome;
    int quantidadeDeColunas;
    int quantidadeDeLinhas;
    ColunaDaTabela * colunas;
} Tabela;

Tabela tabela_criar(Texto nome, int quantidadeDeColunas, Texto nomeDasColunas[], char tipoDasColunas[]);
void tabela_gravar(Tabela tabela);
Tabela tabela_recuperar(Texto nome);
void tabela_liberar(Tabela tabela);
void tabela_exibirCabecalho(Tabela tabela);
void tabela_exibirDados(Tabela tabela);

void tabela_adicionarLinha(Tabela tabela, Texto dados []);

// retorna -1 se o valor não estiver na coluna, em caso contrário, retorna a posição em que ele se encontra
int coluna_buscarValor(ColunaDaTabela coluna, Texto valor);

#endif
