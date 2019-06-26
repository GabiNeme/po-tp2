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


    int procuraCaminho(int s, int t, bool visitado[], int caminho[]);
    int verificaViabilidadeCaminho(int o, int d, int &lim, bool visitado[], int caminho[], int &i_caminho);

    int obtemLimiteFluxo(int caminho[]);
    void aumentaFluxo(int aumento, int caminho[]);

    int obtemValorCorte(bool alcancaveis[]);

    void zeraOcupacoes();

    void imprimeDadosCorteMinimo(int corte, bool verticesCorteMinimo[]);

public:
    Grafo();
    Grafo(int num_vertices);

    int get_num_vertices();
    void iniciaGrafo(int num_vertices);
    void adicionaAresta(int origem, int dest, int custo);
    void imprimeListaAdjacencia();

    int FordFulkerson(int s, int t, bool corteMinimo[]);
    void obtemCorteMinimo();

};


#endif
