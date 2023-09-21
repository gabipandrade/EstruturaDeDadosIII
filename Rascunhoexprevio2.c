#include <stdio.h>
#include <stdlib.h>

#define LIXO "$"
#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define NAO_REMOVIDO '0'

typedef char bool;
typedef struct RegistroCabecalho{
    bool status; //inidica a consistencia do arquivo de dados
    int proxRRN; //armazena o valor do proximo RRN
    int nroTecnologias; // indica a quantidad de tecnologias armazenadas
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
//valores nulos devem ser representados pelo valor -1 e o tamanho armazenado como 0
//lixo deve ser identificado com $, ou seja, cada byte deve armazenar um valor valido ou $
}RegistroDeDados;

//Funcionalidade[1]SQL
void createTable(){
    FILE *arquivoinicial; //arquivo csv
    FILE *arquivofinal; //arquivo.bin
    arquivofinal = fopen("arquivo.bin", "wb");
    arquivoinicial = fopen("tecnologia.csv", "rb");
    if(arquivoinicial == NULL || arquivofinal == NULL){
        printf("Falha no processamento do arquivo.\n"); //confere se foi aberto o arquivo
        return;
    }
    long contador = 0;
    unsigned char buffer[1]; 

    while (fread(buffer, 1, 1, arquivoinicial) == 1) {
        fwrite(buffer, 1, 1, arquivofinal); 
        contador++;
    }
    fclose(arquivoinicial);
    fclose(arquivofinal);
    }
    
       
//void binarioNaTela();
//Funcionalidade[2]SQL
//void select();
//void from();
//Funcionalidade[3] SQL
//void where();
//Funcionalidade[4]
//void RecuperaDados(int RRN);

int main(){
    printf("Hello\n");
    createTable();
    return 0;
}