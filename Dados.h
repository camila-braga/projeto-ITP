
#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Representa uma string de caracteres.
 * Tem como objetivo armazenar informações de uma string , como seu tamanho, para facilitar as manipulações com arquivos.
 */
typedef struct
{                    /** quantidade de posições alocadas para o vetor */
    int capacidade; /** tamanho do texto sem o \0 */
    int tamanho;    /** vetor de caracteres do texto */
    char *vetor;    
} Texto;

void texto_gravar(Texto texto, FILE *arquivo);
Texto texto_recuperar(FILE *arquivo);
Texto texto_lerTerminalEmLoop(int capacidade);
char texto_lerTipoEmLoop();
int texto_lerValorPositivoEmLoop();

// NULL para dado faltando
Texto texto_lerValorComTipo(char tipo);

#endif
