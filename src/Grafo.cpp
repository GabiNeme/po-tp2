#include "Grafo.h"

Grafo::Grafo(){
    this->num_vertices = 0;
    this->matriz_custos = nullptr;
    this->matriz_fluxos = nullptr;
}


Grafo::Grafo(int num_vertices){
    this->iniciaGrafo(num_vertices);
}


Grafo::~Grafo(){
    int v = this->num_vertices;

    for (int i = 0; i < v; ++i)
        delete [] matriz_custos[i];
    delete [] matriz_custos;

    for (int i = 0; i < v; ++i)
        delete [] matriz_fluxos[i];
    delete [] matriz_fluxos;
}

int Grafo::get_num_vertices(){
    return this->num_vertices;
}

void Grafo::iniciaGrafo(int num_vertices){
    this->num_vertices = num_vertices;

    this->matriz_custos = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
        matriz_custos[i] = new int[num_vertices]; 

    this->matriz_fluxos = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
        matriz_fluxos[i] = new int[num_vertices];
    
    for(int i = 0; i < this->num_vertices; i++){
        for(int j = 0; j < this->num_vertices; j++){
            matriz_custos[i][j] = 0;
        }
    }

    this->zeraMatrizFluxos();
}

void Grafo::zeraMatrizFluxos(){
    for(int i = 0; i < this->num_vertices; i++){
        for(int j = 0; j < this->num_vertices; j++){
            matriz_fluxos[i][j] = 0;
        }
    }
}


void Grafo::adicionaAresta(int origem, int dest, int custo){
    matriz_custos[origem][dest] = custo;
    matriz_custos[dest][origem] = custo;
}

void Grafo::imprimeMatrizAdjacencia(){
    int v = this->num_vertices;

    for (int i = 0; i < v; i++) {
         std::cout << i << ' ';
        for (int j = 0; j < this->num_vertices; j++) {
            std::cout << "(" << matriz_fluxos[i][j] << "/" << matriz_custos[i][j] << ")\t";
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
        for (int x = 0; x < this->num_vertices; x++){
            if (!visitado[x]){ //se não foi visitado
                if(matriz_fluxos[o][x] < matriz_custos[o][x]){ //da pra passar por esse vértice
                    result =  verificaViabilidadeCaminho(x, d, lim, visitado, caminho, i_caminho);
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
        int ant = caminho[i-1];
        int atual = caminho[i];

        if (matriz_custos[ant][atual] - matriz_fluxos[ant][atual] < lim){
            lim = matriz_custos[ant][atual] - matriz_fluxos[ant][atual]; //limite é a diferença entre custo e fluxo
        }

        i++;
    }
    return lim;
}


// Percorre o caminho encontrado e aumenta o valor dos fluxos
void Grafo::aumentaFluxo(int aumento, int caminho[]){
    int v = num_vertices;
    int i = 1;
    int valor = 0;

    //para cada vértice do caminho
    while(i < v && caminho[i] != -1){

        int ant = caminho[i-1];
        int atual = caminho[i];

        matriz_fluxos[ant][atual] += aumento;
        valor = matriz_fluxos[ant][atual];
        matriz_fluxos[atual][ant] = -valor;        

        i++;
    }
}


int Grafo::obtemValorCorte(bool alcancaveis[]){
    int corte = 0;

    for(int i = 0; i < num_vertices; i++){
        if(alcancaveis[i]){ //para os vértices alcançáveis
            for (int x = 0; x < this->num_vertices; x++){ //para todos os vértices que pode estar conectado
                if (!alcancaveis[x])
                    corte += abs(matriz_custos[i][x]); //soma o custo ao total
            }
        }
    }
    return corte;
}

int Grafo::FordFulkerson(int s, int t, bool corteMinimo[]){
    int v = num_vertices;
    bool visitado[v];
    int caminho[v];

    this->zeraMatrizFluxos();

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