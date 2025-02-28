#include "Funcoesfornecidas.h"
#include "Grafo.h"
#include "Funcionalidades.h"
#include "LeituraDados.h"
//Essa funcionalidade recebe o arquivo binário e trasforma ele em um grafo
void Funcionalidade8(char* nomeArquivo){
    FILE *arq;
    RegistroCabBIN *RegCab;
    vector<No> grafo;//grafo
    
    arq=AbreArquivoLeituraBIN(nomeArquivo);
    if(arq==NULL){
        return;
    }    
    RegCab=CriaStructCabecalho();
    //Leitura
    RegCab=LeituraCabecalho(RegCab,arq);
    //Cria Grafo
    CriaGrafo(grafo,arq,RegCab);
    imprimirGrafo(grafo);//imprime o grafo
    // Fechar arquivo
    fclose(arq);
}
//Essa funcionalidade recebe o arquivo binário e trasforma ele em um grafo transposto
void Funcionalidade9(char* nomeArquivo){
    FILE *arq;
    RegistroCabBIN *RegCab;
    vector<No> grafo;
    
    arq=AbreArquivoLeituraBIN(nomeArquivo);
    if(arq==NULL){
        return;
    }
    RegCab=CriaStructCabecalho();
    //Leitura
    RegCab=LeituraCabecalho(RegCab,arq);
    //Cria Grafo
    CriaGrafoTransposto(grafo,arq,RegCab);//cria o grafo transposto
    imprimirGrafo(grafo);//imprime o grafo
    // Fechar arquivo
    fclose(arq);
}
//Essa funcionalidade cria um grafo transposto e procura qual tecnologia aponta para a tecnologia buscada
void Funcionalidade10(char* nomeArquivo){
    FILE *arq;
    RegistroCabBIN *RegCab;
    vector<No> grafo;
    int n;
    bool possui;
    string nomestring;
    
    arq=AbreArquivoLeituraBIN(nomeArquivo);
    if(arq==NULL){
        return;
    }
    RegCab=CriaStructCabecalho();
    
    //Leitura
    RegCab=LeituraCabecalho(RegCab,arq);
    //Cria Grafo
    CriaGrafoTransposto(grafo,arq,RegCab);//cria o grafo transposto

    cin >> n;
    for(int i=0;i<n;i++){
        possui=false;
        char *nome=new char[50];
        scan_quote_string(nome);
        nomestring=string(nome);
        for (int i = 0; i < (int)grafo.size(); ++i) {//percorre o grafo
            if (grafo[i].origem == nomestring) {//se o vertice na posicao i for igual ao nome da tecnologia procurada
                cout << nomestring << ": ";
                possui=true;
                for(int j=0;j<(int)grafo[i].arestas.size()-1;j++){
                    cout << grafo[i].arestas[j].destino<< ", ";
                }
                cout << grafo[i].arestas[(int)grafo[i].arestas.size()-1].destino<< endl;//exibe qual vertice de origem aponta para o de destino buscado
            }
        }
        if(possui==false){
            cout << "Registro inexistente" << endl;//se nao possui o registro, exibe que nao existe
        }
        cout << endl;
            
    }
    // Fechar arquivo
    fclose(arq);

}
//Essa funcionalidade usa o algoritmo de Kosaraju para descobrir se o grafo é fortemente conexo
void Funcionalidade11(char* nomeArquivo){
    FILE *arq;
    RegistroCabBIN *RegCab;
    
    arq=AbreArquivoLeituraBIN(nomeArquivo);
    if(arq==NULL){
        return;
    }
    RegCab=CriaStructCabecalho();
    //Leitura
    RegCab=LeituraCabecalho(RegCab,arq);
    Kosaraju(arq,RegCab);//chama a funcao de kosaraju para descobrir se o grafo é fortemente conexo
    //Fechar arquivo
    fclose(arq);
}
//Essa funcionalidade usa o algoritmo de Dijkstra para descobrir o menor caminho entre duas tecnologias
void Funcionalidade12(char* nomeArquivo){
    FILE *arq;
    RegistroCabBIN *RegCab;
    vector<No> grafo;
    string origem,destino;
    int n;
    
    arq=AbreArquivoLeituraBIN(nomeArquivo);
    if(arq==NULL){
        return;
    }
    RegCab=CriaStructCabecalho();
    //Leitura
    RegCab=LeituraCabecalho(RegCab,arq);
    //Cria Grafo
    CriaGrafo(grafo,arq,RegCab);

    cin >> n;
    for(int i=0;i<n;i++){
        char *nome1=new char[50];
        char *nome2=new char[50];
        scan_quote_string(nome1);
        origem=string(nome1);
        scan_quote_string(nome2);
        destino=string(nome2);
        int indiceOrigem = encontrarIndiceTecnologia(grafo,origem);//encontra a posicao da tecnologia de origem
        int indiceDestino = encontrarIndiceTecnologia(grafo,destino);//encontra a posicao da tecnologia de destino
        int d= Dijkstra(grafo, indiceOrigem, indiceDestino); //d recebe a distancia entre origem e destino usando Dijkstra
        if (d == -1 || d == 0 ) {
            cout  << nome1 <<" "<< nome2 << ": "<< "CAMINHO INEXISTENTE." <<endl;//Se nao existe caminho ou se a tecnologia não existe no grafo, exibe que nao existe caminho
        } 
        else {
        cout << nome1 <<" "<< nome2 << ": " << d << endl;
        }  
    }
    // Fechar arquivo
    fclose(arq);

}
