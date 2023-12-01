
#ifndef TABELA_GERAL_H
#define TABELA_GERAL_H

#include <string.h>

#include "Dados.h"
#include "Tabela.h"

int tabelaGeral_contemTabela(Texto nome);
void tabelaGeral_adicionarTabela(Texto nome);
void tabelaGeral_limpar();
int tabelaGeral_apagar(Texto nomeDaTabela);
void tabelaGeral_listar();

#endif
