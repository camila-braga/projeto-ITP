
#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Representa uma string de caracteres.
 */
typedef struct
{
    int capacidade; /// quantidade de posições alocadas para o vetor
    int tamanho;    /// tamanho do texto sem o \0
    char *vetor;    /// vetor de caracteres do texto
} Texto;

void texto_gravar(Texto texto, FILE *arquivo);
Texto texto_recuperar(FILE *arquivo);

Texto texto_lerTerminalEmLoop(int capacidade);
char texto_lerTipoEmLoop();
int texto_lerValorPositivoEmLoop();

// NULL para dado faltando
Texto texto_lerValorComTipo(char tipo);

#endif
