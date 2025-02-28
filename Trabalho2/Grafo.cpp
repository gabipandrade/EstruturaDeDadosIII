#include "Grafo.h"
#include "LeituraDados.h"
int encontrarIndiceTecnologia(const vector<No>& grafo, const string& tecnologia) { //encontra o indice da tecnologia no grafo
    for (int i = 0; i < (int)grafo.size(); ++i) {//percorre o grafo
        if (grafo[i].origem == tecnologia) { //se encontrar a tecnologia no grafo
            return i;//retorna a posição da tecnologia no grafo
        }
    }
    return -1;  // Retornar um valor inválido se a tecnologia não for encontrada
}

int Dijkstra(vector<No>& grafo, int indiceOrigem, int indiceDestino){//retorna a distancia entre dois nós do grafo
    int MAX = 10000;//valor maximo para a distancia 
    int n = grafo.size();//n recebe o tamanho do grafo
    vector<int> dist(n, MAX);//cria um vetor de distancia com tamanho n e inicializa todas as posições com o valor maximo
    vector<int> pai(n, -1);//cria um vetor de pai com tamanho n e inicializa todas as posições com -1
    vector<bool> visitado(n, false);//cria um vetor de visitado com tamanho n e inicializa todas as posições com false
    dist[indiceOrigem] = 0;//a distancia da origem para ela mesma é 0
    for (int i = 0; i < n; ++i) {
        int u = -1;//u recebe -1
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {//se o nó nao foi visitado e u é igual a -1 ou a distancia do nó j é menor que a distancia do nó u
                u = j;//u recebe j
            }
        }
        if (dist[u] == MAX) {
            break;
        }
        visitado[u] = true;//marca o nó u como visitado
        for (const auto& aresta : grafo[u].arestas) {
            int v = encontrarNo(grafo, aresta.destino);//v recebe a posição do nó de destino da aresta
            if (dist[u] + aresta.peso < dist[v]) {//se a distancia do nó u + o peso da aresta for menor que a distancia do nó v
                dist[v] = dist[u] + aresta.peso;//a distancia do nó v recebe a distancia do nó u + o peso da aresta
                pai[v] = u;//o pai do nó v recebe o nó u
            }
        }
    }
    if (dist[indiceDestino] < MAX) {//se a distancia do nó destino for menor que o valor maximo
        return dist[indiceDestino];//retorna a distancia do nó destino
    } else {
        return -1;
    }
}


// Função para adicionar uma aresta ao grafo
void adicionarAresta(vector<No>& grafo, const string& origem, const string& destino, int grupo, int peso) {
    int indiceOrigem = encontrarNo(grafo, origem);//encontra a posição da tecnologia de origem
    if (indiceOrigem == -1) {//se nao encontrar a tecnologia de origem
        No novoNo;//cria um novo nó
        novoNo.origem = origem;//o nome da tecnologia de origem do novo nó recebe a tecnologia de origem
        novoNo.grupo = grupo; //o grupo do novo nó recebe o grupo da tecnologia de origem
        grafo.push_back(novoNo);//adiciona o novo nó no grafo
        indiceOrigem = grafo.size() - 1;//indice da tecnologia de origem recebe o tamanho do grafo - 1
    }

    int indiceDestino = encontrarNo(grafo, destino);//encontra a posição da tecnologia de destino
    if (indiceDestino == -1) {//se nao encontrar a tecnologia de destino
        No novoNo;//cria um novo nó
        novoNo.origem = destino;//o nome da tecnologia de origem do novo nó recebe a tecnologia de destino
        novoNo.grupo = -1;//o grupo do novo nó recebe -1
        grafo.push_back(novoNo);//adiciona o novo nó no grafo
        indiceDestino = grafo.size() - 1;//indice da tecnologia de destino recebe o tamanho do grafo - 1
    }

    grafo[indiceOrigem].grauSaida++;//incrementa o grau de saida do nó de origem
    grafo[indiceDestino].grauEntrada++;//incrementa o grau de entrada do nó de destino

    if (grafo[indiceOrigem].grupo == -1)//se o grupo do nó de origem for -1
        grafo[indiceOrigem].grupo = grupo;//o grupo do nó de origem recebe o grupo da tecnologia de origem
    
    Aresta novaAresta;//cria uma nova aresta
    novaAresta.destino = destino;//a aresta recebe o destino 
    novaAresta.peso = peso;//a aresta recebe o peso
    grafo[indiceOrigem].arestas.push_back(novaAresta);//adiciona a aresta no nó de origem
}
//adiciona uma aresta no grafo transposto
void adicionarArestaTransposto(vector<No>& grafo, string& origem, string& destino, int grupo, int peso){
    swap(origem, destino);//troca a origem pelo destino
    int indiceOrigem = encontrarNo(grafo, origem);
    if (indiceOrigem == -1) {//
        No novoNo;
        novoNo.origem = origem;
        novoNo.grupo = -1; 
        grafo.push_back(novoNo);
        indiceOrigem = grafo.size() - 1;
    }

    int indiceDestino = encontrarNo(grafo, destino);
    if (indiceDestino == -1) {
        No novoNo;
        novoNo.origem = destino;
        novoNo.grupo = grupo;
        grafo.push_back(novoNo);
        indiceDestino = grafo.size() - 1;
    }

    grafo[indiceOrigem].grauSaida++;//incrementa o grau de saida do nó de origem
    grafo[indiceDestino].grauEntrada++;//incrementa o grau de entrada do nó de destino

    if (grafo[indiceDestino].grupo == -1)
        grafo[indiceDestino].grupo = grupo;
    
    Aresta novaAresta;
    novaAresta.destino = destino;
    novaAresta.peso = peso;
    grafo[indiceOrigem].arestas.push_back(novaAresta);

}


// Função para imprimir o grafo
void imprimirGrafo(const std::vector<No>& grafo) {
    for (const auto& no : grafo) {
        for (const auto& aresta : no.arestas) {//imprime as informações da aresta
        cout << no.origem << " "
                    << no.grupo << " "
                    << no.grauEntrada << " "
                    << no.grauSaida << " "
                    << no.grauSaida + no.grauEntrada << " "
                    << aresta.destino << " "
                    << aresta.peso << endl;
        }
    }
    
}

// Função para encontrar um nó no grafo
int encontrarNo(vector<No>& grafo, const std::string& origem) {
    for (int i = 0; i < (int)grafo.size(); ++i) {
        if (grafo[i].origem == origem) {//se encontrar a tecnologia de origem no grafo
            return i;//retorna a posição da tecnologia de origem no grafo
        }
    }
    return -1;
}
void CriaGrafo(vector<No>& grafo,FILE *arq,RegistroCabBIN *RegCab){//cria o grafo
    string origem,destino;
    RegistroBIN *RegDados;
    
    for(int i=0;i<RegCab->proxRRN;i++){
        RegDados=CriaStructRegDados();
        if (RegDados ==NULL ) {
            cout << "Erro ao alocar memória"<<endl; 
            fclose(arq);
            return ;
        }
        RegDados=LeituraDados(RegDados,arq);
        if (RegDados->removido[0] == '1' || RegDados->tamanhoTecnologiaDestino==0 || RegDados->grupo==-1) {/*se o registro estiver removido ou o tamanho da tecnologia de destino for 0 ou 
        o grupo for -1 não adiciona  */    
            continue;
        }
        origem=string(RegDados->nomeTecnologiaOrigem);
        destino=string(RegDados->nomeTecnologiaDestino);
        adicionarAresta(grafo, origem, destino, RegDados->grupo, RegDados->peso);//adiciona a aresta no grafo

    }
    // Ordenando o grafo
    sort(grafo.begin(), grafo.end(), [](const No& a, const No& b) {
        return a.origem < b.origem;
    });
    sort(grafo.begin(), grafo.end(), [](const No& a, const No& b) {
        return a.origem < b.origem;
    });

    for(int i=0;i<int(grafo.size());i++){
        sort(grafo[i].arestas.begin(),grafo[i].arestas.end(),[](const Aresta& a, const Aresta& b) {
        return a.destino < b.destino;
    });

    }
}
void CriaGrafoTransposto(vector<No>& grafo,FILE *arq,RegistroCabBIN *RegCab){//cria o grafo transposto
    string origem,destino;
    RegistroBIN *RegDados;
    
    for(int i=0;i<RegCab->proxRRN;i++){
        RegDados=CriaStructRegDados();
        if (RegDados ==NULL ) {
            cout << "Erro ao alocar memória"<<endl; 
            fclose(arq);
            return ;
        }

        RegDados=LeituraDados(RegDados,arq);
        if (RegDados->removido[0] == '1' || RegDados->tamanhoTecnologiaDestino==0 || RegDados->grupo==-1) {
            continue;
        }
        origem=string(RegDados->nomeTecnologiaOrigem);
        destino=string(RegDados->nomeTecnologiaDestino);
        adicionarArestaTransposto(grafo, origem, destino, RegDados->grupo, RegDados->peso);//adiciona a aresta no grafo transposto

    }
    // Ordenando o grafo
    sort(grafo.begin(), grafo.end(), [](const No& a, const No& b) {
        return a.origem < b.origem;
    });
    sort(grafo.begin(), grafo.end(), [](const No& a, const No& b) {
        return a.origem < b.origem;
    });

    for(int i=0;i<int(grafo.size());i++){
        sort(grafo[i].arestas.begin(),grafo[i].arestas.end(),[](const Aresta& a, const Aresta& b) {
        return a.destino < b.destino;
    });

    }
}

void dfsParaMontarLista(vector<No>& grafo,string &u,map<string,bool> &ListaVisitados,stack<string>&Lista){ //para montar lista para kosaraju
    if(ListaVisitados[u]){//se o nó ja foi visitado
        return;//retorna
    }
    int indice_u=encontrarNo(grafo, u);//indice do nó u
    ListaVisitados[grafo[indice_u].origem]=true;//marca o nó u como visitado
    for(int i=0;i<(int)grafo[indice_u].arestas.size();i++){//percorre as arestas do nó u
        dfsParaMontarLista(grafo,grafo[indice_u].arestas[i].destino,ListaVisitados,Lista);//chama a novamente a função para montar a lista para o nó de destino da aresta
    }
    Lista.push(grafo[indice_u].origem);//adiciona o nó u na lista
    return;
}

void dfsParaVisitar(vector<No>& grafo,string &u,map<string,bool> &ListaVisitados){ //para visitar pelo kosaraju
    
    if(ListaVisitados[u]){//se o nó ja foi visitado
        return;
    }
    int indice_u=encontrarNo(grafo, u);//indice do nó u
    ListaVisitados[grafo[indice_u].origem]=true;//marca o nó u como visitado
    for(int i=0;i<(int)grafo[indice_u].arestas.size();i++){//percorre as arestas do nó u
        dfsParaVisitar(grafo,grafo[indice_u].arestas[i].destino,ListaVisitados);//chama a novamente a função para visitar o nó de destino da aresta
    }
    return;
}

void Kosaraju(FILE *arq,RegistroCabBIN *RegCab){
    
    // Criando um vetor de pares string-booleano
    map<string,bool> ListaVisitados;
    //Cria Grafo
    vector<No> grafo,grafoT;
    stack<string>Lista;
    CriaGrafo(grafo,arq,RegCab);
    for (const auto& no : grafo) {
        ListaVisitados[no.origem] = false;//inicializa o vetor de visitados com false
    }
    for(int i=0;i<(int)grafo.size();i++){
        if(ListaVisitados[grafo[i].origem]==false){//se o nó nao foi visitado
            dfsParaMontarLista(grafo,grafo[i].origem,ListaVisitados,Lista);//chama a função para montar a lista para o nó
        }
    
    }
    
    //Cria Grafo Transposto
    fseek(arq,13,SEEK_SET);
    CriaGrafoTransposto(grafoT,arq,RegCab);//cria o grafo transposto
    int numero_de_componentes=0;//numero de componentes conexos do grafo

    for (const auto& no : grafo) {
        ListaVisitados[no.origem] = false;
    }
    
    while (!Lista.empty()) {
        if(ListaVisitados[Lista.top()]==false){
            dfsParaVisitar(grafoT,Lista.top(),ListaVisitados);//chama a função para visitar o nó
            numero_de_componentes++;//incrementa o numero de componentes
        }
        Lista.pop();//remove o nó da lista
    }
    if(numero_de_componentes==1){//se o numero de componentes for 1
        cout << "Sim, o grafo é fortemente conexo e possui 1 componente."<< endl;//exibe que o grafo é fortemente conexo e possui 1 componente

    }else{//se o numero de componentes for maior que 1
        cout <<"Não, o grafo não é fortemente conexo e possui " << numero_de_componentes<<" componentes."<<endl;//exibe que o grafo não é fortemente conexo e possui x componentes

    }    

}
