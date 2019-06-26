#include "Grafo.h"

Grafo::Grafo(){
    this->num_vertices = 0;
}


Grafo::Grafo(int num_vertices){
    this->iniciaGrafo(num_vertices);
}

int Grafo::get_num_vertices(){
    return this->num_vertices;
}

void Grafo::iniciaGrafo(int num_vertices){
    this->num_vertices = num_vertices;
    adj_list.resize(num_vertices);
}


void Grafo::adicionaAresta(int origem, int dest, int custo){
    V_Adj ori_dest(dest, custo);
    V_Adj dest_ori(origem, custo);
    adj_list[origem].push_back(ori_dest);
    adj_list[dest].push_back(dest_ori);
}

void Grafo::imprimeListaAdjacencia(){
    int v = this->num_vertices;

    for (int i = 0; i < v; i++) {
         std::cout << i << ' ';
        for (auto x : adj_list[i]) {
            std::cout << x.vertice << "(" << x.ocupacao << "/" << x.custo << ") ";
        }
        std::cout <<  std::endl;
    }
}


// Procura um caminho viável entre 's' e 't'
int Grafo::procuraCaminho(int s, int t, bool visitado[], int caminho[]){

    int i_caminho = 0;
    int lim = __INT_MAX__;

    // Chamada recursiva para procurar os caminhos
    return verificaViabilidadeCaminho(s, t, lim, visitado, caminho, i_caminho);
}

// Função recursiva que procura, no grafo, qualquer caminho com capacidade
// disponível entre o e d
int Grafo::verificaViabilidadeCaminho(int o, int d, int &lim, bool visitado[], int caminho[], int &i_caminho){
    // Se chegou no vértice, ele pode pertencer ao caminho
    visitado[o] = true;
    caminho[i_caminho] = o;
    i_caminho++;

    int result = 0;

    // Se encontrou o destino, retorna 1
    if (o == d){
        return 1;

    }else{ //se não é o vértice de destino

        // Verifica a viabilidade de todos os vértices adjacentes ao atual
        for (auto x: adj_list[o]){

            if (!visitado[x.vertice]){ //se não foi visitado
                if(x.ocupacao < x.custo){ //da pra passar por esse vértice
                    result =  verificaViabilidadeCaminho(x.vertice, d, lim, visitado, caminho, i_caminho);
                    if (result == 1) break;
                }

            }
        }

        //verificou todos os possíveis nós a partir do atual
        //Se for 0, não encontrou nenhum, tira esse nó do caminho
        //Se for 1, encontrou algum
        if (result == 0){
            caminho[i_caminho] = -1;
            i_caminho --;
        }

        return result;
    }

}


//percorre o caminho encontrado à procura do limite de aumento do caminho
int Grafo::obtemLimiteFluxo(int caminho[]){
    int v = num_vertices;
    int i = 1;
    int lim = __INT_MAX__;

    //para cada vértice do caminho
    while(i < v && caminho[i] != -1){

        for (auto x: adj_list[caminho[i-1]]){
            if(x.vertice == caminho[i]){ //encontrou o vertice atual na lista de adjacência do vértice anterior
                if (x.custo - x.ocupacao < lim){
                    lim = x.custo - x.ocupacao; //limite é a diferença entre custo e ocupação
                }
            }
        }
        i++;
    }
    return lim;
}


// Percorre o caminho encontrado e aumenta o valor das ocupações
void Grafo::aumentaFluxo(int aumento, int caminho[]){
    int v = num_vertices;
    int i = 1;
    int valor = 0;

    //para cada vértice do caminho
    while(i < v && caminho[i] != -1){

        //procura o vertice atual na lista de adjacência do vértice anterior
        for (auto it = adj_list[caminho[i-1]].rbegin(); it != adj_list[caminho[i-1]].rend(); it++){
            if(it->vertice == caminho[i]){
                it->ocupacao += aumento;
                valor = it->ocupacao;
                break;
            }
        }
        //procura o vertice anterior na lista de adjacência do vértice atual
        for (auto it = adj_list[caminho[i]].rbegin(); it != adj_list[caminho[i]].rend(); it++){
            if(it->vertice == caminho[i-1]){
                it->ocupacao = -valor;
                break;
            }
        }

        i++;
    }
}


int Grafo::obtemValorCorte(bool alcancaveis[]){
    int corte = 0;

    for(int i = 0; i < num_vertices; i++){
        if(alcancaveis[i]){ //para os vértices alcançáveis
            for (auto x: adj_list[i]){ //percorre a lista de adjacência desse vértice
                if (!alcancaveis[x.vertice])
                    corte += abs(x.custo); //soma o custo ao total
            }
        }
    }
    return corte;
}

int Grafo::FordFulkerson(int s, int t, bool corteMinimo[]){
    int v = num_vertices;
    bool visitado[v];
    int caminho[v];

    this->zeraOcupacoes();

    //enquanto existe trajeto disponível no grafo de s a t
    while(true){
        for (int i = 0; i < v; i++){ //zera métricas
            visitado[i] = false;
            caminho[i] = -1;
        }

        int existeCaminho = this->procuraCaminho(s,t,visitado, caminho);
        if(!existeCaminho){
            break;
        }

        int aumento = this->obtemLimiteFluxo(caminho);
        this->aumentaFluxo(aumento, caminho);
    }

    for(int i = 0; i< v;i++){//copia vetor
        corteMinimo[i] = visitado[i];
    }

    return this->obtemValorCorte(visitado);
}


void Grafo::zeraOcupacoes(){
    for(int i = 0; i < num_vertices; i++){
        for (auto it = adj_list[i].rbegin(); it != adj_list[i].rend(); it++){
            it->ocupacao = 0;
        }
    }
}


void Grafo::obtemCorteMinimo(){

    int v = num_vertices;
    bool verticesCorteMinimo[v], verticesCorteAtual[v];
    int corteMinimo = __INT_MAX__;
    int corteAtual = __INT_MAX__;

    int s = 0;

    //para cada vértice que pode ser um destino
    for(int t = 1; t < v ; t++){

        corteAtual = this->FordFulkerson(s, t, verticesCorteAtual);

        if (corteAtual < corteMinimo){ //encontrou corte menor
            corteMinimo = corteAtual;
            for(int i = 0; i < v; i++){
                verticesCorteMinimo[i] = verticesCorteAtual[i];
            }
        }
    }

    imprimeDadosCorteMinimo(corteMinimo, verticesCorteMinimo);
}


void Grafo::imprimeDadosCorteMinimo(int corte, bool verticesCorteMinimo[]){
    int totalVertices = 0;
    //conta número de vértices do corte mínimo
    for(int i = 0; i < num_vertices; i++){
        if(verticesCorteMinimo[i])
            totalVertices ++;
    }
    std::cout << totalVertices << std::endl;

    //imprime vértices do corte mínimo
    for(int i = 0; i < num_vertices; i++){
        if(verticesCorteMinimo[i]){
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    //imprime valor do corte mínimo
    std::cout << corte << std::endl;

}