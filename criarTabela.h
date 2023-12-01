
/**
 * @file
 * @brief Responsável por criar as tabelas do programa.
 * 
 * As tabelas são indexadas por um aquivo principal denominado "Tabela Geral.data"
 * e cada tabela estará associada a um arquivo especificado pelo o nome dela atribuído pelo usuário.
 * 
 * A Tabela Geral terá o seguinte formato:
 * Quantidade de tabelas existentes
 * Nome da primeira tabela
 * Nome da segunda tabela
 * ...
 * Nome da última tabela
 * 
 * 
 * As tabelas específicas serão organizadas da seguinte forma:
 * Nome da tabela
 * Quantidade de colunas
 * Quantidade de linhas
 * Nome da primeira coluna
 * Tipo de dado da primeira coluna
 * Nome da segunda coluna
 * Tipo de dado da segunda coluna
 * ...
 * Nome da última coluna
 * Tipo de dado da última coluna
 * Dados da primeira coluna
 * Dados da segunda coluna
 * ...
 * Dados da última coluna
 * 
 * Observação: a primeira coluna será a chave primária da tabela e seu tipo será inteiro sem sinal
*/

#ifndef CRIAR_TABELA_H
#define CRIAR_TABELA_H


/**
 * @file
 * @brief Reponsável por criar tabelas
*/

void criaTabela();


#endif
