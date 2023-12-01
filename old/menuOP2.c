#include <stdio.h>
#include "TabelaGeral.h"

//!Função que exibe todas as tabelas existentes.

void ListaTabelas(){
  FILE * ArqTabelas;
  ArqTabelas = fopen("Arquivo com nomes das tabelas.txt","r");
  //Verifica se o arquivo existe:
  if (ArqTabelas == NULL){
    printf("Não existem tabelas a serem listadas.\n");
    fclose(ArqTabelas);
    
  }else{
    //Exibe as tabelas existentes:
    printf("As tabelas existentes são:\n");
    int qtdTabelas = fscanf(ArqTabelas,"%d",&qtdTabelas);
    for (int i = 0; i < qtdTabelas; i++){
      //printf("");
    }
  }

/*Gostaria que fosse assim:
Lia a quantidade de tabelas existentes
Exibia os nomes dessas tabelas*/

  
}