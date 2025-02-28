#ifndef __GRAFO_H__
#define __GRAFO_H__
#include "cabeca.h"
//Grafo
void adicionarAresta(vector<No>& grafo, const string& origem, const string& destino, int grupo, int peso);
void imprimirGrafo(const std::vector<No>& grafo) ;
int encontrarNo(vector<No>& grafo, const std::string& origem);
void adicionarArestaTransposto(vector<No>& grafo, const string& origem, const string& destino, int grupo, int peso);
void CriaGrafo(vector<No>& grafo,FILE *arq,RegistroCabBIN *RegCab);
void CriaGrafoTransposto(vector<No>& grafo,FILE *arq,RegistroCabBIN *RegCab);
int encontrarIndiceTecnologia(const vector<No>& grafo, const string& tecnologia) ;
int Dijkstra(vector<No>& grafo, int indiceOrigem, int indiceDestino);
void Kosaraju(FILE *arq,RegistroCabBIN *RegCab);
void dfsParaMontarLista(vector<No>& grafo,string &u,map<string,bool>& ListaVisitados,stack<string>&Lista);
void dfsParaVisitar(vector<No>& grafo,string &u,map<string,bool>& ListaVisitados);
#endif