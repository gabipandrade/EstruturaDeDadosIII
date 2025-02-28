#include "cabeca.h"
#include "AberturaArquivo.h"

/*abre o arquivo csv recebido*/
FILE *AbreArquivoLeituraCSV(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"r");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

/*abre o arquivo binário para escrita*/
FILE *AbreArquivoEscritaBIN(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"wb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

/*abre o arquivo binário para leitura*/
FILE *AbreArquivoLeituraBIN(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}
