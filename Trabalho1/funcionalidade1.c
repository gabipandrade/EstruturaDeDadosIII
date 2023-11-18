#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_REGISTRO 205
#define LIXO '$'
#define NAO_REMOVIDO '0'



typedef struct RegistroCabecalho{
    char status; //inidica a consistencia do arquivo de dados
    int noRaiz;
    int RRNproxNo; //armazena o valor do proximo RRN    
}RegCab;

typedef struct Folha{
    int P1;
    char C1[55];
    int PR1;
    int P2;
    char C2[55];
    int PR2;
    int P3;
    char C3[55];
    int PR3;
    int P4;
}Folha;

typedef struct RegistroDeDados{
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;
    Folha folha;    
}RegDados;
FILE *AbreArquivoLeituraBIN(char *arq);
FILE *AbreArquivoEscritaBIN(char *arq);

int InicializaCabecalho(RegCab *RegCab);
int InicializaDados(RegDados *RagDados);
int EscreveCabecalhoNoArquivo(RegCab *RegCab,FILE *arq);
int LeituraArquivo(RegDados *RegDados,char *p,FILE *arq);

int AdicionaNaArvore();
int BuscaBinaria();
int Split();
int EscreveNoArquivo();

int main(){

    RegDados x;
    RegCab y;
    InicializaCabecalho(&y);
    InicializaDados(&x);
    scanf("%s",x.folha.C1);
    scanf("%s",x.folha.C2);
    scanf("%s",x.folha.C3);
    printf("%s %s %s\n",x.folha.C1,x.folha.C2,x.folha.C3);
    printf("%d %d %d\n",x.folha.P1,x.folha.P2,x.folha.P3);
}

int InicializaCabecalho(RegCab *RegCab){
    RegCab->status='0';
    RegCab->noRaiz=-1;
    RegCab->RRNproxNo=0;
    return 0;
}

int InicializaDados(RegDados *RegDados){
    RegDados->folha.P1=-1;
    RegDados->folha.P2=-1;
    RegDados->folha.P3=-1;
    return 0;
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

FILE *AbreArquivoLeituraBIN(char *arq){
    FILE *arquivo;
    char readerChar;    
    arquivo= fopen(arq,"rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    fread(&readerChar,1,1,arquivo);

    if(readerChar=='0'){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

void createTable(char *arqCSV,char *arqBIN){
    //ponteiros para arquivo
    FILE *arqOriginal;
    FILE *arqConvertido;
    
    //ponteiros para registros
    //RegCab *RegCab;
    //RegDados *RegDados;
    //variaveis de leitura
    char *p;
    int MaxLinha=256;

    arqOriginal=AbreArquivoLeituraBIN(arqCSV);    
    arqConvertido=AbreArquivoEscritaBIN(arqBIN);
    
    //InicializaCabecalho(RegCab);
    //InicializaDados(RegDados);

    if(arqConvertido==NULL || arqConvertido==NULL){
        //free(RegDados);
        //free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        return;
    }
    
    
    p=(char*)calloc(256,sizeof(char)); 
    if (p == NULL ) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        //free(RegDados);
        //free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        free(p);
        return ;
    }

    fgets(p, MaxLinha, arqOriginal); //Ignora primeira linha
    /*
    if(LeituraArquivo(RegDados,p,arqOriginal)==1){
        return;
    }
    
    */
    
    
    
    //RegCab->status='1';
    
    //EscreveCabecalhoNoArquivo(RegCab,arqConvertido);
    
    

    //LimpaRegistroDeDados(RegDados);
    //free(RegCab);
    free(p);

    
    //Fecha Arquivos
    fclose(arqConvertido);
    fclose(arqOriginal);
    //binarioNaTela(arqBIN);
    
}
/*
int EscreveNoArquivo(RegistroDeDados *RegDados,RegistroCabecalho*RegCab,char *p,FILE *arqOriginal,FILE *arqConvertido,int *RRN){
    int MaxLinha=256;
    char **Origem,**Destino;
	int n=0;
    int TamanhoDoLixo;
    char *token;

    while(fgets(p, 76, arqOriginal)){
        ler_dados(RegDados,&Origem,&Destino,RegCab,&n);
        fwrite(&(RegDados->removido),sizeof(char),1,arqConvertido);
        fwrite(&(RegDados->grupo),sizeof(int),1,arqConvertido);
        fwrite(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
        fwrite(&(RegDados->peso),sizeof(int),1,arqConvertido);
        fwrite(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
        EscrevePalavras(RegDados->nomeTecnologiaOrigem,arqConvertido,RegDados->tamanhoTecnologiaOrigem);
        fwrite(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
        if(RegDados->tamanhoTecnologiaDestino!=0){
            EscrevePalavras(RegDados->nomeTecnologiaDestino,arqConvertido,RegDados->tamanhoTecnologiaDestino);
        }
                
        TamanhoDoLixo=76 - 21 -(RegDados->tamanhoTecnologiaOrigem+RegDados->tamanhoTecnologiaDestino);
        for(int i=0;i<TamanhoDoLixo;i++){
            fwrite("$",sizeof(char),1,arqConvertido);
        }
        (*RRN)++;
    }
    
    
    for (int i = 0; i < n; i++) {
        free(Origem[i]);
        free(Destino[i]);
    }

    free(Origem);
    free(Destino);
    
}

*/
