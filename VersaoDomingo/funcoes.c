#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cabeca.h"

RegistroCabecalho *CriaStructCabecalho(){
    RegistroCabecalho *RegCab;
    RegCab=(RegistroCabecalho*)malloc(sizeof(RegistroCabecalho));
    if(RegCab==NULL){
        return NULL;
    }

    RegCab->status='0';
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

FILE *AbreArquivoLeituraBIN(char *arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

void PrintarDadosRegistro(RegistroDeDados *RegDados){
    char cifrao[2]="$";
    printf("%s",RegDados->nomeTecnologiaOrigem);
    if(RegDados->grupo==-1){
        printf(", NULO");
    }else{
        printf(", %d",RegDados->grupo);    
    }
    if(RegDados->popularidade==-1){
        printf(", NULO");
    }else{
    printf(", %d",RegDados->popularidade);    
    }
    if(RegDados->tamanhoTecnologiaDestino==0){
        printf(", NULO");
    }
    else{
        printf(", %s",RegDados->nomeTecnologiaDestino);    
    }
    if(RegDados->peso==-1){
        printf(", NULO\n");
    }else{
        printf(", %d\n",RegDados->peso);    
    }
}


RegistroCabecalho *LeituraCabecalho(RegistroCabecalho*RegCab, FILE *arq){
    //status/proxRRN/NroTecnologias/NroParesTecnologias
    fread(&(RegCab->status),sizeof(char),1,arq);
    fread(&(RegCab->proxRRN),sizeof(int),1,arq);
    fread(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fread(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);

    return RegCab;
}

RegistroDeDados *LeituraDados(RegistroDeDados *RegDados, FILE *arqConvertido){
    int tamanhoRegistro;

    fread(&(RegDados->removido),sizeof(char),1,arqConvertido);
    fread(&(RegDados->grupo),sizeof(int),1,arqConvertido);
    fread(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
    fread(&(RegDados->peso),sizeof(int),1,arqConvertido);
    fread(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
    fread((RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arqConvertido);
    fread(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
    fread((RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arqConvertido);

    tamanhoRegistro=76 - 21 -(RegDados->tamanhoTecnologiaOrigem+RegDados->tamanhoTecnologiaDestino);
    fseek(arqConvertido,tamanhoRegistro,SEEK_CUR);

    return RegDados;
}
void LimpaRegistroDeDados(RegistroDeDados *RegDados){
    free(RegDados->nomeTecnologiaDestino);
    free(RegDados->nomeTecnologiaOrigem);
    free(RegDados);
}       



int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido){
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    char readerChar;
    RegCab=CriaStructCabecalho();

    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegCab);
        fclose(arqConvertido);
        return 1;
    }

    RegCab=LeituraCabecalho(RegCab,arqConvertido);
    
    if(RegCab->status=='0'){
        printf("Falha no processamento do arquivo.\n");
        free(RegCab);
        return 1;
    }
    while(fread(&readerChar,1,1,arqConvertido)!=0){
        ungetc(readerChar,arqConvertido);
        RegDados=CriaStructRegDados();
    
        if (RegDados ==NULL ) {
            printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
            LimpaRegistroDeDados(RegDados);
            return 1;
        }
    
        RegDados=LeituraDados(RegDados,arqConvertido);
        
        if(escolha ==0 && RegDados->grupo==valor){
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==1 && RegDados->popularidade==valor){
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==2 && RegDados->peso==valor){
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==3 && strcmp(RegDados->nomeTecnologiaOrigem,nome)==0){
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==4 && strcmp(RegDados->nomeTecnologiaDestino,nome)==0){
            PrintarDadosRegistro(RegDados);
        }
        LimpaRegistroDeDados(RegDados);    
    }
    free(RegCab);
    return 0;
}

void ContadorTecnologias(RegistroCabecalho *RegCab,char ***Origem,char ***Destino,char *tecOrigem,char *tecDestino,int *n){
    if((*n)==0){
        (*n)++;
        *Origem=(char** )malloc(sizeof(char*)*(*n));
	    *Destino=(char**)malloc(sizeof(char)*(*n));

        // Verifica alocacao
        if (*Origem == NULL || *Destino == NULL) {
        printf("Erro na alocação de matriz\n");
        return ;
        }
        for (int i = 0; i < *n; i++) {
            (*Origem)[i] = NULL;
            (*Destino)[i] = NULL;
        }
        
        (*Origem)[0]=strdup(tecOrigem);
        (*Destino)[0]=strdup(tecDestino);
        RegCab->nroTecnologias+=2;
        RegCab->nroParesTecnologias++;

        return;
    }
    //Numero Tecnologias
    int a=0,b=0;
    for(int i=0;i<(*n);i++){
        if(strcmp(tecOrigem,(*Origem)[i])==0){
            a=1;
            break;
        }
    }
    
    if(a==0){
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Destino)[i])==0){
                a=1;
                break;
            }
        }
    }
    
    if(tecDestino==NULL){
        b=1;
    }else{
        for(int i=0;i<(*n);i++){
            if(strcmp(tecDestino,(*Origem)[i])==0){
                b=1;
                break;
            }
        }
        if(b==0){
            for(int i=0;i<(*n);i++){
                if(strcmp(tecDestino,(*Destino)[i])==0){
                    b=1;
                    break;
                }
            }
        }    
    }
    
    if(a==0){
        if(b==0){
            //a=0 e b=0 nenhuma eh repetida
            RegCab->nroTecnologias+=2;

        }else{
            //a=0 e b=1 uma eh repetida
            RegCab->nroTecnologias++;
        }
    }else{
        if(b==0){
            //a=1 e b=0 uma eh repetida
            RegCab->nroTecnologias++;
        }else{
            //a=1 e b=1 as duas sao repetidas
        }
    }

    //Verificacao dos Pares de Tecnologias
    if(tecDestino!=NULL){
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Origem)[i])==0 && strcmp(tecDestino,(*Destino)[i])==0){//Verifica se ja tem alguma Origem igual a Origem no vetor
                //o par eh repetido
                return;
            }
        }
        //o par eh novo, deve ser adicionado
        RegCab->nroParesTecnologias++;
        (*n)++;
        *Origem= (char **)realloc(*Origem, sizeof(char *) * (*n));
        *Destino= (char **)realloc(*Destino , sizeof(char *) * (*n));
        (*Origem)[(*n)-1] = strdup(tecOrigem);
        (*Destino)[(*n)-1] = strdup(tecOrigem);
    }
    else{
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Origem)[i])==0 && (*Destino)[i]==NULL){
                //ja tem
                return;
            }
        }
        //eh novo, deve ser adicionado, mas nao eh par
        (*n)++;
        *Origem= (char **)realloc(*Origem, sizeof(char *) * (*n));
        *Destino= (char **)realloc(*Destino, sizeof(char *) * (*n));
        (*Origem)[(*n)-1] = strdup(tecOrigem);
        (*Destino)[(*n)-1] = NULL;
        
    }
    
}
