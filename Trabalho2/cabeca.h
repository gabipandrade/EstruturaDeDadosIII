#ifndef __CABECA_H__
#define __CABECA_H__
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_REGISTRO 205
#define LIXO '$'
#define NAO_REMOVIDO '0'

using namespace std;

struct RegistroCabBIN {
    char status; // indica a consistência do arquivo de dados
    int proxRRN; // armazena o valor do próximo RRN
    int nroTecnologias; // indica a quantidade de tecnologias armazenadas
    int nroParesTecnologias; // indica a quantidade de pares diferentes que estão armazenados no arquivo de dados
};

struct RegistroBIN {
    int grupo; // grupo ao qual a tecnologia de origem pertence
    int popularidade; // total de milhões de acessos que existem no stack overflow
    int peso; // frequência com que as tags de tecnologia no stack overflow aparecem juntas
    int tamanhoTecnologiaOrigem; // tamanho da string de tamanho variável
    char *nomeTecnologiaOrigem; // string, não pode ter \0
    int tamanhoTecnologiaDestino; // tamanho da string de tamanho variável
    char *nomeTecnologiaDestino; // string, não pode ter \0
    char removido[1]; // string de 1 byte para indicar se o registro está logicamente removido
};

// Estrutura para representar uma aresta
struct Aresta {
    string destino;//nome da tecnologia de destino
    int peso;//peso da aresta
};

// Estrutura para representar um nó do grafo
struct No {
    string origem;//nome da tecnologia de origem
    int grauEntrada = 0;//grau de entrada do nó
    int grauSaida = 0;//grau de saída do nó
    int grupo;//grupo ao qual a tecnologia de origem pertence
    vector<Aresta> arestas;//vetor de arestas
};


#endif