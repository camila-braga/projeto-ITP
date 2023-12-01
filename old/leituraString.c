#include <stdio.h>
#include <stdlib.h>

#include "leituraString.h"

 /**
  * Efetua a leitura de uma string de tamanho qualquer.
  * 
  * @param n Retorno por referência do tamnho da string mais 1 para incluir o \0.
  * @return Um ponteiro para o vetor de caracteres.
 */

char *lerString(int *n) {
  char *texto = NULL;
  int tam = 0;

  //tratamento do primeiro caractere:
  char c = getchar();
  if (c == ' ') {
    *n = 0;
    return texto;
  } else {
    //Faz a leitura do primeiro caractere diferente de ' ' na memória dinânica.
    texto = realloc(texto, tam + 1);
    texto[tam] = c;
    tam += 1;
  }
  //Continua a leitura dos outros caracteres.
  do {
    scanf("%c", &c);
    texto = realloc(texto, tam + 1);
    texto[tam] = c;
    tam += 1;
  } while (texto[tam - 1] != '\0' && texto[tam - 1] != '\n');
  texto[tam - 1] = '\0';
  *n = tam;
  return texto;
}

