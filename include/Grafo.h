#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>

class Grafo{
private:
    int num_vertices;
    int num_arestas;
    int ** matriz_custos;
    int ** fluxos;

public:
    Grafo();
    Grafo(int num_vertices, int num_arestas);

    ~Grafo();

    void iniciaGrafo(int num_vertices, int num_arestas);
    void adicionaAresta(int origem, int dest, int custo);
    void imprimeMatrizCusto();
};


#endif
