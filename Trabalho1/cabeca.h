#ifndef __CABECA_H__
#define __CABECA_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAVES 4
#define TAM_REGISTRO 205
#define LIXO '$'
#define NAO_REMOVIDO '0'


typedef struct RegistroCabBIN{
    char status; //inidica a consistencia do arquivo de dados
    int proxRRN; //armazena o valor do proximo RRN
    int nroTecnologias; // indica a quantidade de tecnologias armazenadas
    int nroParesTecnologias;// indica a quantidade de pares diferentes que estao armazenados no arquivo de dados
}RegistroCabBIN;

typedef struct RegistroBIN{
    int grupo; //grupo ao qual a tecnologia de origem pertence
    int popularidade; //total de milhoes de acessos que existe no stack overflow
    int peso; //frequencia com que as tags de tecnoologia no stack overflow aparecem juntas
    int tamanhoTecnologiaOrigem; //tamanho da string de tamanho variavel
    char *nomeTecnologiaOrigem; //string, nao pode ter \0
    int tamanhoTecnologiaDestino; //tamanho da string de tamanho variavel
    char *nomeTecnologiaDestino; //string, nao pode ter \0
    char removido[1]; //string de 1 byte para indicar se o registro esta logicamente removido
}RegistroBIN;

//ARVORE
typedef struct CabecalhoArvore{ //COLOCAR REFERENCIA PARA ARVORE
    char status; //inidica a consistencia do arquivo de dados
    int noRaiz;
    int RRNproxNo; //armazena o valor do proximo RRN    
}CabecalhoArvore;

typedef struct DadosNo{ //Trocar NOME PARA "DADOS DO NO"
    int P[4]; //Ponteiros
    char *chave[3]; //Chaves
    int PR[3];
}DadosNo;

typedef struct RegistroArvore{ //COLOCAR REFERENCIA PARA ARVORE
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;
    DadosNo folha;    
}RegistroArvore;

typedef struct Chave{
    char *nometec;
    int PR;
    int Pdireita;
}Chave;

#endif