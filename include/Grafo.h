#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include "VerticeAdjacente.h"

class Grafo{
private:
    int num_vertices;
    std::vector<std::list<V_Adj>> adj_list;

public:
    Grafo();
    Grafo(int num_vertices);

    int get_num_vertices();

    void iniciaGrafo(int num_vertices);
    void adicionaAresta(int origem, int dest, int custo);
    void imprimeListaAdjacencia();
    void imprimeMatrizAdjacencia();

    int procuraCaminho(int s, int t, bool visitado[], int caminho[]);
    int verificaViabilidadeCaminho(int o, int d, int &lim, bool visitado[], int caminho[], int &i_caminho);

    int obtemLimiteFluxo(int caminho[]);
    void aumentaFluxo(int aumento, int caminho[]);

    int obtemValorCorte(bool alcancaveis[]);

    void zeraOcupacoes();

    int FordFulkerson(int s, int t, bool corteMinimo[]);

    void obtemCorteMinimo();
    void obtemCorteMinimoVertices(int listaVertices[], int tamList,int &corteMinimo, bool verticesCorteMinimo[]);
    void imprimeDadosCorteMinimo(int corte, bool verticesCorteMinimo[]);

};


#endif
