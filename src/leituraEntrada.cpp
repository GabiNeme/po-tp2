#include "leituraEntrada.h"

/* Lê o grafo inserido pelo usuário na linha de comandos e
    preenche o objeto grafo.
*/
void leEntrada(Grafo &grafo){

    // lê número de vértices e arestas
    int vertices, arestas;
    std::cin >> vertices;
    std::cin >> arestas;

    grafo.iniciaGrafo(vertices);

    //lê as arestas e seus custos
    int orig, dest, custo;
    for (int i = 0; i < arestas; i++){

        std::cin >> orig;
        std::cin >> dest;
        std::cin >> custo;

        grafo.adicionaAresta(orig, dest, custo);
    }

}

