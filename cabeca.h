#ifndef __CABECA_H__
#define __CABECA_H__


#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define LIXO '$'
#define NAO_REMOVIDO '0'

typedef struct RegistroCabecalho{
    char status; //inidica a consistencia do arquivo de dados
    int proxRRN; //armazena o valor do proximo RRN
    int nroTecnologias; // indica a quantidade de tecnologias armazenadas
    int nroParesTecnologias;// indica a quantidade de pares diferentes que estao armazenados no arquivo de dados
}RegistroCabecalho;


typedef struct RegistroDeDados{
    int grupo; //grupo ao qual a tecnologia de origem pertence
    int popularidade; //total de milhoes de acessos que existe no stack overflow
    int peso; //frequencia com que as tags de tecnoologia no stack overflow aparecem juntas
    int tamanhoTecnologiaOrigem; //tamanho da string de tamanho variavel
    char *nomeTecnologiaOrigem; //string, nao pode ter \0
    int tamanhoTecnologiaDestino; //tamanho da string de tamanho variavel
    char *nomeTecnologiaDestino; //string, nao pode ter \0
    char removido[1]; //string de 1 byte para indicar se o registro esta logicamente removido
}RegistroDeDados;

FILE *AbreArquivoLeituraCSV(char *arq);
FILE *AbreArquivoLeituraBIN(char *arq);
FILE *AbreArquivoEscritaBIN(char *arq);
void binarioNaTela(char *nomeArquivoBinario);
RegistroCabecalho *CriaStructCabecalho();
RegistroDeDados *CriaStructRegDados();
void InicializaCabecalho(RegistroCabecalho *RegCab, FILE *arq);
void PrintarDadosRegistro(RegistroDeDados *RegDados);
RegistroCabecalho *LeituraCabecalho(RegistroCabecalho*RegCab, FILE *arq);
RegistroDeDados *LeituraDados(RegistroDeDados *RegDados, FILE *arqConvertido);
void LimpaRegistroDeDados(RegistroDeDados *RegDados);
//Funcionalidade [1]
void createTable(char *arqCSV,char *arqBIN);
//Funcionalidade[2]
void SelectFrom(char *arqBIN);
//Funcionalidade[3]

//Funcionalidade[4]
void RecuperaDados(char *arqBIN, int RRN);

#endif