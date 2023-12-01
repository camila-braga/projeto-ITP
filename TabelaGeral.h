
#ifndef TABELA_GERAL_H
#define TABELA_GERAL_H

#include <string.h>

#include "Dados.h"

int tabelaGeral_existe();
int tabelaGeral_contemTabela(Texto nome);
void tabelaGeral_adicionarTabela(Texto nome); // ok
void tabelaGeral_limpar();

#endif
