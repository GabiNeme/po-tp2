#include <iostream>
#include "leituraEntrada.h"
#include "Grafo.h"
/*
    O objetivo do presente programa é retornar o corte mínimo em um grafo dirigido conexo ponderado.
    Gabriela Peres Neme - 2018054745 - PO - DCC - ICEX - UFMG - 2019/1
*/

int main(int argc, char *argv[]){

    //declara variáveis de entrada e lê os valores definidos pelo usuário
    Grafo grafo;
    leEntrada(grafo);

    grafo.obtemCorteMinimo();
}