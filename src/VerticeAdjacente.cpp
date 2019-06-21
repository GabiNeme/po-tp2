#include "VerticeAdjacente.h"

V_Adj::V_Adj(){
    this->vertice = -1;
    this->custo = -1;
}

V_Adj::V_Adj(int vertice, int custo){
    this->vertice = vertice;
    this->custo = custo;
    this->ocupacao = 0;

}