# SGBD ITP

---

O projeto consiste em implementar um Sistema de Gerenciamento de Banco de Dados (SGBD) simplificado baseado no modelo relacional.
Não é o objetivo desse projeto criar um SGBD para ser utilizado em produção por
sistemas de informação, mas “apenas” explorar os conceitos abordados na disciplina ITP.
O SGBD ITP deverá ser capaz de realizar as seguintes operações:

1. Criar uma tabela;
2. Listar todas as tabelas;
3. Criar uma nova linha na tabela;
4. Listar todos os dados da tabela;
5. Pesquisar valor em uma tabela;
6. Apagar uma tupla ou linha de uma tabela;
7. Apagar uma tabela;
8. Apagar todas as tabelas (funcionalidade adicional).

O SGBD ITP implementado cria um arquivo para cada tabela, além de criar um arquivo extra contendo a quantidade de tabelas e seus nomes para auxiliar, quando necessário, na implementação das funções.

O arquivo que contém a quantidade de tabelas e seus nomes se chama Tabela Geral.data e está organizado da seguinte forma: quantidade de tabelas, nomes das tabelas.

Cada arquivo das tabelas está organizado da seguinte forma: nome da tabela, quantidade de colunas, quantidade de linhas, tipo de dado e nome da coluna intercalados, dados das colunas.

O código fonte foi dividido em 4 módulos além do principal, chamados: Dados.h, Pesquisa.h, Tabela.h, TabelaGeral.h e principal.c. 
No módulo Dados, estão organizadas as funções responsáveis pelas leituras de dados e gravações das informações obtidas nos arquivos.
No módulo Pesquisa, estão organizadas as funções responsáveis pela pesquisa de um valor em uma tabela.
No módulo Tabela, estão organizadas as funções responsáveis pelas operações relacionadas às tabelas, como a criação de uma tabela, a adição ou remoção de uma linha, a exibição de seus dados...
No módulo TabelaGeral, estão organizadas as funções responsáveis pelas operações relacionadas ao arquivo 'tabela geral.data', como sua criação, a atualização de suas informações, a exibição dos nomes de todas as tabelas, a remoção de um arquivo...
No módulo principal, está implementada a função principal, além de outras auxiliares.

O código fonte está documentado no arquivo Doc.pdf.

## Instalação

O código fonte está escrito na linguagem C, sendo necessário apenas de um compilador para a referida linguagem voltado a sua plataforma. Por exemplo, para o compilador GCC, pode executar a seguinte linha de comando no diretório que se encontra o código fonte:

```
gcc -o main -Wno-unused-result principal.c Dados.c Pesquisa.c Tabela.c TabelaGeral.c
```
Versão do compilador GCC: gcc version 6.3.0 (MinGW.org GCC-6.3.0-1)
Link para download: https://www.mingw-w64.org/
Importante ressaltar que não é necessária a instalação de nenhuma biblioteca externa.

## Detalhes da implementação

Todas as funções solicitadas foram implementadas, além de uma função extra (Apagar todas as tabelas do código fonte) e a opção de sair do menu.

## O que poderia ser feito de forma diferente?

Poderia ter sido criado um único arquivo para todas as tabelas. Porém, a implementação se tornou muito complexa para a autora, que decidiu reiniciar o projeto utilizando a ideia atual. Outra coisa que poderia ter sido diferente era ter salvo os dados nos arquivos de modo binário e não em caractere, reduzindo assim o tamanho do arquivo. Também poderia ter sido implementada uma função extra de remover uma coluna na tabela.

## Autora

A autora do projeto se chama Camila Braga de Oliveira.