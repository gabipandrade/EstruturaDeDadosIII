#include "FuncoesCabecalho.h"
#include "cabeca.h"
#include "AberturaArquivo.h"
#include "FuncoesDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"

/* Cria e aloca o Registro de cabeçalho, além de inicializar as váriavéis com 0*/
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

/* Inicializa o cabeçalho escrevendo no arquivo os dados do cabeçalho recebidos pela função*/
void InicializaCabecalho(RegistroCabecalho *RegCab, FILE *arq){
    fwrite(&(RegCab->status),sizeof(char),1,arq);
    fwrite(&(RegCab->proxRRN),sizeof(int),1,arq);
    fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fwrite(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);   
}

/* faz a leitura do cabeçalho do arquivo recebido usando fread*/
RegistroCabecalho *LeituraCabecalho(RegistroCabecalho*RegCab, FILE *arq){
    fread(&(RegCab->status),sizeof(char),1,arq);
    fread(&(RegCab->proxRRN),sizeof(int),1,arq);
    fread(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fread(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);

    return RegCab;
}

/*Conta o número de tecnologias e de pares que o arquivo possui */
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
            (*Origem)[i] = NULL; //vetor de tecnologias da origem
            (*Destino)[i] = NULL; //vetor de tecnologias do destino
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
        if(strcmp(tecOrigem,(*Origem)[i])==0){ //confere se a tecnologia ja existe no vetor origem
            a=1; //se existir a=1
            break;
        }
    }
    
    if(a==0){ //se a tecnologia nao existir no vetor origem conferir no vetor destino
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Destino)[i])==0){ 
                a=1; //se existir a=1
                break;
            }
        }
    }
    
    if(tecDestino==NULL){ //confere se a tecnologia de destino eh nula
        b=1;
    }else{
        for(int i=0;i<(*n);i++){
            if(strcmp(tecDestino,(*Origem)[i])==0){ //confere se a tecnologia Destino ja existe no vetor origem
                b=1; //se existir b=1
                break;
            }
        }
        if(b==0){
            for(int i=0;i<(*n);i++){ //confere se a tecnologia Destino ja existe
                if(strcmp(tecDestino,(*Destino)[i])==0){
                    b=1; //se existir b=1
                    break;
                }
            }
        }    
    }
    
    if(a==0){ //se a tecnologia origem é nova
        if(b==0){ //se a tecnologia destino é nova
            //a=0 e b=0 nenhuma eh repetida
            RegCab->nroTecnologias+=2; //duas tecnologias novas

        }else{ //caso contrario apenas a tecnologia origem eh nova
            //a=0 e b=1 uma eh repetida
            RegCab->nroTecnologias++; //uma tecnologia nova
        }
    }else{
        if(b==0){ // apenas a tecnologia destino eh nova
            //a=1 e b=0 uma eh repetida
            RegCab->nroTecnologias++;
        }else{ //nenhuma eh nova
            //a=1 e b=1 as duas sao repetidas
        }
    }

    //Numero dos Pares de Tecnologias
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
        (*Destino)[(*n)-1] = strdup(tecDestino);
        
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
