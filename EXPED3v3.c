#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define LIXO '$'
#define NAO_REMOVIDO '0'

typedef struct RegistroCabecalho{
    char status[2]; //inidica a consistencia do arquivo de dados
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
FILE *AbreArquivoEscritaBIN(char *arq);

RegistroCabecalho *CriaStructCabecalho();
RegistroDeDados *CriaStructRegDados();
void InicializaCabecalho(RegistroCabecalho *RegCab, FILE *arq);
void createTable(char *arqCSV,char *arqBIN){
    //ponteiros para arquivo
    FILE *arqOriginal;
    FILE *arqConvertido;
    
    //ponteiros para registros
    RegistroCabecalho *RegCab;
    RegistroDeDados *RegDados;
    //variaveis de leitura
    char *p;
    int MaxLinha=256;


    arqOriginal=AbreArquivoLeituraCSV(arqCSV);    
    arqConvertido=AbreArquivoEscritaBIN(arqBIN);
    RegCab=CriaStructCabecalho();
    RegDados=CriaStructRegDados();

    if(arqConvertido==NULL || arqConvertido==NULL){
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        return;
    }
    //da fwrite no cabecalho no arquivo Binario
    InicializaCabecalho(RegCab,arqConvertido);

    //Leitura do arquivo
    p=(char*)calloc(256,sizeof(char)); 
    if (p == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        free(p);
        return ;
    }

    fgets(p, MaxLinha, arqOriginal);
    printf("%s",p);
    char *str1; // Variável para armazenar a primeira string
    int num1, num2, num3; // Variáveis para armazenar os números
    char *str2; // Variável para armazenar a segunda string

    str1=(char*)calloc(50,sizeof(char)); 
    str2=(char*)calloc(50,sizeof(char)); 
    
    while (fgets(p, MaxLinha, arqOriginal) != NULL) {    
        if (sscanf(p, "%49[^,],%d,%d,%49[^,],%d", str1, &num1, &num2, str2, &num3) == 5) {
            // Agora, as variáveis contêm os valores lidos
            printf("String 1: %s\n", str1);
            printf("Número 1: %d\n", num1);
            printf("Número 2: %d\n", num2);
            printf("String 2: %s\n", str2);
            printf("Número 3: %d\n", num3);

            realloc(str1,strlen(str1));
            realloc(str2,strlen(str2));
            
            strcpy(RegDados->nomeTecnologiaOrigem,str1);
            RegDados->tamanhoTecnologiaOrigem=strlen(str1);
            RegDados->grupo=num1;
            RegDados->popularidade=num2;
            strcpy(RegDados->nomeTecnologiaDestino,str2);
            RegDados->tamanhoTecnologiaDestino=strlen(str2);
            RegDados->peso=num3;
            

            fwrite(&(RegDados->removido),sizeof(char),1,arqConvertido);
            fwrite(&(RegDados->grupo),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->peso),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arqConvertido);
            fwrite(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arqConvertido);
        }

    }
    printf("\nTudo OK\n");
    
    
    
    free(RegDados);
    free(RegCab);
    free(p);
    fclose(arqConvertido);
    fclose(arqOriginal);
        
}
int main(){
    int escolha;
    char arqCSV[20];
    char arqBIN[20];
    scanf("%d",&escolha);
    printf("escolha feita foi:%d\n",escolha); //REMOVER NO FUTURO
    switch(escolha){
        case 1:
        printf("Caso1\n"); //REMOVER NO FUTURO
        scanf("%s",arqCSV);
        scanf("%s",arqBIN);
        createTable(arqCSV,arqBIN);
        break;
        case 2:
        printf("Caso2\n"); //REMOVER NO FUTURO
        break;
        case 3:
        printf("Caso3\n"); //REMOVER NO FUTURO
        break;
        case 4:
        printf("Caso4\n"); //REMOVER NO FUTURO
        break;
    }
}
RegistroCabecalho *CriaStructCabecalho(){
    RegistroCabecalho *RegCab;
    RegCab=(RegistroCabecalho*)malloc(sizeof(RegistroCabecalho));
    if(RegCab==NULL){
        return NULL;
    }

    strcpy(RegCab->status,"0");
    RegCab->proxRRN=0;
    RegCab->nroTecnologias=0;
    RegCab->nroParesTecnologias=0;
    
    return RegCab;
}

RegistroDeDados *CriaStructRegDados(){
    RegistroDeDados *RegDados;
    RegDados=(RegistroDeDados*)malloc(sizeof(RegistroDeDados));
    if(RegDados==NULL){
        return NULL;
    }
    strcpy(RegDados->removido,"0");
    RegDados->nomeTecnologiaDestino=(char*)calloc(50,sizeof(char));
    RegDados->nomeTecnologiaOrigem=(char*)calloc(50,sizeof(char));
    return RegDados;
}
FILE *AbreArquivoLeituraCSV(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"r");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}
FILE *AbreArquivoEscritaBIN(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"wb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

void InicializaCabecalho(RegistroCabecalho *RegCab, FILE *arq){
    fwrite(&(RegCab->status),sizeof(char),1,arq);
    fwrite(&(RegCab->proxRRN),sizeof(int),1,arq);
    fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fwrite(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);   
}