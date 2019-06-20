#include "Grafo.h"

Grafo::Grafo(){
    this->num_vertices = 0;
    this->num_arestas = 0;
    this->matriz_custos = nullptr;
}


Grafo::Grafo(int num_vertices, int num_arestas){
    this->iniciaGrafo(num_vertices, num_arestas);
}


Grafo::~Grafo(){
    int v = this->num_vertices;

    for (int i = 0; i < v; ++i)
        delete [] matriz_custos[i];
    delete [] matriz_custos;

    for (int i = 0; i < v; ++i)
        delete [] fluxos[i];
    delete [] fluxos;
}


void Grafo::iniciaGrafo(int num_vertices, int num_arestas){
    this->num_vertices = num_vertices;
    this->num_arestas = num_arestas;

    this->matriz_custos = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
        matriz_custos[i] = new int[num_vertices]; 

    this->fluxos = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
        fluxos[i] = new int[num_vertices];
}


void Grafo::adicionaAresta(int origem, int dest, int custo){
    this->matriz_custos[origem][dest] = custo;
}

void Grafo::imprimeMatrizCusto(){

    int v = this->num_vertices;

    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            std::cout << matriz_custos[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
