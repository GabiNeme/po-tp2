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

    /*
    std::string variacaoQS, tipoVetor, exibirVetores;
    int tamVet = 0;
    leEntrada(argc, argv, variacaoQS, tipoVetor, tamVet, exibirVetores);

    //declara variáveis de comparação
    int NUM_ITER = 50;
    long media_comp, media_mov;
    int media_tempo;
    std::string vetoresUsados;

    //alimenta função aleatória
    srand(time(nullptr));

    //Cria NUM_ITER vetores, popula de acorodo com tipoVetor, ordena segundo estipulado por variacaoQS e apura a média
    //de comparações, movimentações e mediana do tempo
    ordenaVetores(variacaoQS, tipoVetor, tamVet, media_comp, media_mov, media_tempo, NUM_ITER, vetoresUsados);

    //imprime saida
    imprimeSaida(variacaoQS, tipoVetor, tamVet, media_comp, media_mov, media_tempo, vetoresUsados, exibirVetores);
*/

}