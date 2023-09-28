#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.c"

#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define LIXO '$'
#define NAO_REMOVIDO '0'
//Gabriela Passos de Andrade-12625142
//Rafael Cunha Bejes Learth-13676367

//tamanho fixo 13
typedef struct RegistroCabecalho{
    char status[2]; //inidica a consistencia do arquivo de dados
    int proxRRN; //armazena o valor do proximo RRN
    int nroTecnologias; // indica a quantidade de tecnologias armazenadas
    int nroParesTecnologias;// indica a quantidade de pares diferentes que estao armazenados no arquivo de dados
}RegistroCabecalho;

//---------------------Metodo Rafael
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



//1 abrir csv, abrir bin e passar dados para bin, passar para a funcao binarioNaTela
//2 abrir bin, imprime todos os dados
//3 nome do arquivo bin e quantidade de filtros, grupo e numero 

//cmp bin1.bin bin2.bin
//-hex editor extensao vscode

//Funcoes dadas
void binarioNaTela(char *nomeArquivoBinario);
void readline(char* string);

//Funcionalidade[1]SQL
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
    
    return RegDados;
}
void escrevefwrite(FILE *arquivoconvertido, RegistroDeDados *RegDados){
    if(&arquivoconvertido==NULL || &RegDados==NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }   
    fwrite(&(RegDados->removido),sizeof(char),1,arquivoconvertido);
    fwrite(&(RegDados->grupo),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegDados->popularidade),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegDados->peso),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arquivoconvertido);
    fwrite(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arquivoconvertido);
}
void contatecnologia(){
    //funcao que conta a quantidade de tecnologias
    //TODO LER ARQUIVO E CONTAR A TECNOLOGIA SEM REPETIR 
    //TODO VETOR ARMAZENAR AS TECNOLOGIAS
}
void contapares(){
    //funcao que conta a quantidade de pares
}
void createTable(char *ArqOrginal,char*ArqCriado){
    char *buffer;
    char *readerChar;
    int *readerInt;
    char *p;
    FILE *arquivoinicial;
    FILE *arquivoconvertido;
    RegistroCabecalho *RegCab;
    RegistroDeDados *RegDados;
    
    arquivoinicial = fopen(ArqOrginal, "r");
    arquivoconvertido= fopen(ArqCriado,"wb");
    RegCab=CriaStructCabecalho();
    RegDados=CriaStructRegDados();

    if(arquivoinicial == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    fwrite(&(RegCab->status),sizeof(char),1,arquivoconvertido);
    fwrite(&(RegCab->proxRRN),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arquivoconvertido);
    fwrite(&(RegCab->nroParesTecnologias),sizeof(int),1,arquivoconvertido);
    
        //nomeTecnologiaOrigem,grupo,popularidade,nomeTecnologiaDestino,peso
        //funcao que pula cabecalho
        p=(char*)malloc(100*sizeof(char)); 
        fgets(p, sizeof(p), arquivoinicial);
        printf("Ate Aqui OK\n");
        while(fgets(p,sizeof(p),arquivoinicial)!=0){
        //while(fread(readerChar,sizeof(char),1,arquivoinicial)!=0){    
            //ungetc(*readerChar,arquivoinicial);
            printf("Ate Aqui OK\n");

            //NomeTecnologiaOrigem e tamanho
            while(fread(readerChar,sizeof(char),1,arquivoinicial)!=0){
                buffer=(char*)calloc(50,sizeof(char));
                if(*readerChar!=','){
                    strcat(buffer,readerChar);
                }
                else{
                    //CRIAR CASO DE STRING VAZIA
                    strcpy(RegDados->nomeTecnologiaOrigem,buffer);
                    RegDados->tamanhoTecnologiaOrigem=strlen(buffer);
                    free(buffer);
                    break;
                }
            }

            printf("Ate Aqui OK\n");

            fread(&readerChar,sizeof(char),1,arquivoinicial);//le a virgula
            //Grupo
            fread(&readerInt,sizeof(int),1,arquivoinicial);
            RegDados->grupo=*readerInt;
            
            fread(&readerChar,sizeof(char),1,arquivoinicial);//le a virgula
            //Popularidade
            fread(&readerInt,sizeof(int),1,arquivoinicial);
            RegDados->popularidade=*readerInt;
            
            fread(&readerChar,sizeof(char),1,arquivoinicial);//le a virgula
            //nomeTecnologiaDestino e tamanho
            while(fread(readerChar,sizeof(char),1,arquivoinicial)!=0){
            buffer=(char*)calloc(50,sizeof(char));
                if(*readerChar!=','){
                    strcat(buffer,readerChar);
                }
                else{
                    //CRIAR CASO DE STRING VAZIA
                    strcpy(RegDados->nomeTecnologiaDestino,buffer);
                    RegDados->tamanhoTecnologiaDestino=strlen(buffer);
                    free(buffer);
                    break;
                }
            }
            fread(&readerChar,sizeof(char),1,arquivoinicial);//le a virgula
            //Peso
            fread(&readerInt,sizeof(int),1,arquivoinicial);
            RegDados->peso=*readerInt;
            
            //ler o enter
            fread(&readerChar,sizeof(char),2,arquivoinicial);
            
            //? CRIAR FUNCAO PARA ESCREVER AS COISAS EM ORDEM NO FWRITE  feito ?
            escrevefwrite(arquivoconvertido,RegDados);
        }
    printf("Saiu do Loop\n");
    void corrigecabecalho();{
    //ESCREVER FUNCAO QUE CORRIGE O CABECALHO COM AS INFORMACOES CORRETAS DE PROXRRN, NRO TECNOLOGIAS E NRO DE PARES DIFERENTES ANTES DE DAR FREE NOS REGISTROS, UTILIZAR CONTADORES
        fseek(arquivoinicial,0,SEEK_SET);
    //funcoes de alterar cabecalho
    //** Status começa 0 e vai para 1 no final  do uso arquivo
    //**antes do fclose e binario na tela
    //** ProxRRN começa 0 e muda quando necessario(descobrir quando)
    //** NroTecnologias começa 0 e vai contando
    //** NroParesTecnologias começa 0 e vai contando os pares sendo que a ordem importa
    fwrite(&(RegCab->status),sizeof(char),1,arquivoconvertido);
    //fwrite(&(RegCab->proxRRN),sizeof(int),1,arquivoconvertido);
    //fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arquivoconvertido);
    //fwrite(&(RegCab->nroParesTecnologias),sizeof(int),,arquivoconvertido);
    }
//corrigecabecalho();
    free(p);
    free(RegCab);
    free(RegDados);
    // se for fechado corretamente escrever o status igual a 1

    fclose(arquivoinicial);
    fclose(arquivoconvertido);
    strcpy(RegCab->status,"1");
    binarioNaTela(ArqCriado);
    
}   

//Funcionalidade[2]SQL
//void select(char *arqCriado);
        
//void select();
//void from();

//Funcionalidade[3] SQL
//void where();

//Funcionalidade[4]
void RecuperaDados(char *ArqCriado, int RRN){
    FILE *arquivoconvertido;
    RegistroDeDados *RegDados;
    char readerChar;
    int RRNfinal;
    int RRN0;
    RegDados=CriaStructRegDados();
    
    arquivoconvertido= fopen(ArqCriado,"rb");
    if(arquivoconvertido == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //CASO1: RRN nao existe
    fseek(arquivoconvertido,0,SEEK_SET);
    RRN0=(int)ftell(arquivoconvertido);
    printf("%d\n",RRN0);
    fseek(arquivoconvertido,0,SEEK_END);
    RRNfinal=((int)ftell(arquivoconvertido)-RRN0-sizeof(RegistroCabecalho))/sizeof(RegistroDeDados);
    
    
    printf("RRNfinal=%d\n",RRNfinal);
    printf("pont aq:%d\n",(int)ftell(arquivoconvertido));
    
    if(RRN>RRNfinal){
        printf("Registro Inexistente\n");
        return;
    }
    printf("Ate Aqui OK\n");
    //CASO2: RRN foi removido
    fseek(arquivoconvertido,RRN*sizeof(RegistroDeDados)+sizeof(RegistroCabecalho),SEEK_CUR);
    printf("pont aq:%ld\n",ftell(arquivoconvertido));
    fread(&readerChar,1,1,arquivoconvertido);
    if(readerChar=='1'){
        printf("Registro Inexistente\n");
        return;
    }
    printf("Ate Aqui OK\n");
    //CASO3: RRN valido
    fread(&(RegDados->removido),sizeof(char),1,arquivoconvertido);
    fread(&(RegDados->grupo),sizeof(int),1,arquivoconvertido);
    fread(&(RegDados->popularidade),sizeof(int),1,arquivoconvertido);
    fread(&(RegDados->peso),sizeof(int),1,arquivoconvertido);
    fread(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arquivoconvertido);
    fread(&(RegDados->nomeTecnologiaOrigem),RegDados->tamanhoTecnologiaOrigem*sizeof(char),1,arquivoconvertido);
    fread(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arquivoconvertido);
    fread(&(RegDados->nomeTecnologiaDestino),RegDados->tamanhoTecnologiaDestino*sizeof(char),1,arquivoconvertido);
    
    printf("%s",RegDados->nomeTecnologiaOrigem);
    
    if(RegDados->grupo=='$'){
        printf(", NULO");
    }else{
    printf(", %d",RegDados->grupo);    
    }
    if(RegDados->popularidade=='$'){
        printf(", NULO");
    }else{
    printf(", %d",RegDados->popularidade);    
    }
    if(*RegDados->nomeTecnologiaDestino=='$'){
        printf(", NULO");
    }else{
    printf(", %s",RegDados->nomeTecnologiaDestino);    
    }
    if(RegDados->peso=='$'){
        printf(", NULO");
    }else{
    printf(", %d",RegDados->peso);    
    }
    //SE TIVER CAMPO NULO, PRINTAR NULO
    
}

int main(){
    int escolha;
    long int RRN;
    char arqOriginal[10],arqCriado[10];
    
    scanf("%d",&escolha);
    switch(escolha){
        case 1:
        //readline(arqOriginal);
        //readline(arqCriado);
        scanf("%s %s",arqOriginal,arqCriado);
        //printf("%s\n",arqOriginal);
        //printf("%s\n",arqCriado);
        //createTable("dados1.csv",arqCriado); 
        break;
        case 2:
        scanf("%s",arqCriado);
        //select(arqCriado);
        break;
        case 3:
        //funcao 3
        break;
        case 4:
        scanf("%s",arqCriado);
        scanf("%ld", &RRN);

        RecuperaDados(arqCriado,RRN);
        break;
        default:
        //error
        break;
    }
    return 0;
}

