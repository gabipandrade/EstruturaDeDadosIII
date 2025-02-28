#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

FILE *AbreArquivoLeituraBIN(char *arq){ //abre o arquivo para leitura com o modo rb
    FILE *arquivo;
    char readerChar;    
    arquivo= fopen(arq,"rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    fread(&readerChar,1,1,arquivo); //le o primeiro byte do arquivo

    if(readerChar=='0'){ //se o primeiro byte for 0 o arquivo esta inconsistente
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }

    ungetc(readerChar,arquivo); 
    return arquivo;
}

FILE *AbreArquivoLeituraEscritaBIN(char *arq){//abre o arquivo para leitura e escrita com o modo rb+
    FILE *arquivo;
    char readerChar;    
    arquivo= fopen(arq,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    fread(&readerChar,1,1,arquivo);

    if(readerChar=='0'){ //se o primeiro byte for 0 o arquivo esta inconsistente
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }

    ungetc(readerChar,arquivo);
    return arquivo;
}
void InicializaCabecalhoBIN(RegistroCabBIN *RegCab, FILE *arq){//escreve o cabecalho do arquivo binario
    fwrite(&(RegCab->status),sizeof(char),1,arq);
    fwrite(&(RegCab->proxRRN),sizeof(int),1,arq);
    fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fwrite(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);   
}

RegistroCabBIN *LeituraCabecalhoBIN(RegistroCabBIN*RegCab, FILE *arq){//le o cabecalho do arquivo binario
    fread(&(RegCab->status),sizeof(char),1,arq);
    fread(&(RegCab->proxRRN),sizeof(int),1,arq);
    fread(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fread(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);

    return RegCab;
}

CabecalhoArvore *LeituraCabecalho(CabecalhoArvore *RegCab, FILE *arq){ //le o cabecalho do arquivo de indice
    fread(&(RegCab->status),sizeof(char),1,arq);
    fread(&(RegCab->noRaiz),sizeof(int),1,arq);
    fread(&(RegCab->RRNproxNo),sizeof(int),1,arq);
    //pula o lixo
    fseek(arq,196,SEEK_CUR);
    
    return RegCab;
}
void LeituraDadosIndice(FILE *arqBIN){//le os dados do arquivo de indice
    CabecalhoArvore *RegCab;
    RegCab=InicializaCabecalho();

    RegCab = LeituraCabecalho(RegCab,arqBIN);
    
    if(RegCab->status==0){ //Arquivo Inconsistente
        printf("Falha no processamento do arquivo\n");
        return; 
    }
    
}

void LeituraDadosParaAdicao(FILE *arqBIN,FILE *arqWrite){ //le os dados do arquivo binario para adicionar na arvore
    char readerChar;
    RegistroBIN *RegBIN;
    RegistroCabBIN *RegCabBIN;
    CabecalhoArvore *RegCab;
    int RRN=0;
    //Inicializacao
    RegCabBIN=CriaStructCabecalho();
    RegCab=InicializaCabecalho();

    RegCabBIN = LeituraCabecalhoBIN(RegCabBIN,arqBIN);
    
    if(RegCabBIN->status==0){ //Arquivo Inconsistente
        printf("Falha no processamento do arquivo\n");
        return; 
    }
    
    while(fread(&readerChar,1,1,arqBIN)!=0){
        ungetc(readerChar,arqBIN);
        RegBIN=CriaStructRegDados();
        LerBIN(RegBIN,arqBIN);

        if((strcmp(RegBIN->removido,"1")==0)||(RegBIN->tamanhoTecnologiaDestino==0)||(RegBIN->tamanhoTecnologiaOrigem==0)){//se o registro estiver removido ou as tecnologias forem nulas
            LimpaRegistroDeDados(RegBIN);
            RRN++; //pula para o proximo registro
            continue;
        }
        AdicionaNaArvore(RegBIN,RegCabBIN,arqWrite,RegCab,RRN); //adiciona na arvore
        
        LimpaRegistroDeDados(RegBIN);
        RRN++;
    }
    
    RegCab->status='1'; //Arquivo consistente
    fseek(arqWrite,0,SEEK_SET);
    EscreveCabecalhoArvore(RegCab,arqWrite); //escreve cabecalho
        
}

RegistroBIN* LerBIN(RegistroBIN *RegDados, FILE *arq){//le os dados do arquivo binario
    int tamanhoRegistro;
    fread((RegDados->removido),sizeof(char),1,arq);
    fread(&(RegDados->grupo),sizeof(int),1,arq);
    fread(&(RegDados->popularidade),sizeof(int),1,arq);
    fread(&(RegDados->peso),sizeof(int),1,arq);
    fread(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arq);
    fread((RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arq);
    fread(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arq);
    fread((RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arq);

    tamanhoRegistro=76 - 21 -(RegDados->tamanhoTecnologiaOrigem+RegDados->tamanhoTecnologiaDestino);
    fseek(arq,tamanhoRegistro,SEEK_CUR);

    return RegDados;
}

int LeituraArqIndex(RegistroArvore *RegDados,FILE *arq){//le os dados do arquivo de indice
    fread(&(RegDados->nroChavesNo),sizeof(int),1,arq);
    fread(&(RegDados->alturaNo),sizeof(int),1,arq);
    fread(&(RegDados->RRNdoNo),sizeof(int),1,arq);
    
    fread(&(RegDados->folha.P[0]),sizeof(int),1,arq);
    //Leitura chave 1
    fread((RegDados->folha.chave[0]),55*sizeof(char),1,arq);
    fread(&(RegDados->folha.PR[0]),sizeof(int),1,arq);
    fread(&(RegDados->folha.P[1]),sizeof(int),1,arq);
    //Leitura de chave 2
    fread((RegDados->folha.chave[1]),55*sizeof(char),1,arq);
    fread(&(RegDados->folha.PR[1]),sizeof(int),1,arq);
    fread(&(RegDados->folha.P[2]),sizeof(int),1,arq);
    //Leitura de chave 3
    fread((RegDados->folha.chave[2]),55*sizeof(char),1,arq);
    fread(&(RegDados->folha.PR[2]),sizeof(int),1,arq);
    fread(&(RegDados->folha.P[3]),sizeof(int),1,arq);
    
    for(int j=0;j<3;j++){
        for(int i=54;i>=0;i--){
            if(RegDados->folha.chave[j][i]!='$'){
                RegDados->folha.chave[j][i+1]='\0';
                break;
            }
        }
    }
    
    return 0;
}
void LerArquivoBinarioParaContagemTecnologias(char***Origem,char***Destino,RegistroCabBIN *RegCab,int *n,FILE *arq){ //le o arquivo binario para contar tecnologias
    char readerChar;
    RegistroBIN *RegDados;
    int removido;
    fseek(arq,13,SEEK_SET);
    
    while(fread(&readerChar,1,1,arq)!=0){
        removido=0;
        ungetc(readerChar,arq);
        RegDados=CriaStructRegDados();
    
        // Inicializa strings como vazias a cada iteração
        RegDados=LerBIN(RegDados,arq);   
        if(strcmp(RegDados->removido,"1")==0){ //se o registro estiver removido
            continue;
        }
        
        ContadorTecnologias(RegCab,Origem,Destino,RegDados->nomeTecnologiaOrigem,RegDados->nomeTecnologiaDestino,n);//chama a função que conta tecnologias
        
        
        LimpaRegistroDeDados(RegDados);
    }
}
/*Conta o número de tecnologias e de pares que o arquivo possui */
void ContadorTecnologias(RegistroCabBIN *RegCab,char ***Origem,char ***Destino,char *tecOrigem,char *tecDestino,int *n){
    if((*n)==0){
        (*n)++;
        *Origem=(char** )malloc(sizeof(char*)*(*n));
        *Destino=(char**)malloc(sizeof(char*)*(*n));

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
            if(strcmp((*Destino)[i],"")==0){
                continue;
            }
            if(strcmp(tecOrigem,(*Destino)[i])==0){ 
                a=1; //se existir a=1
                break;
            }
        }
    }
    
    if(tecDestino==NULL||strlen(tecDestino)==0){ //confere se a tecnologia de destino eh nula
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
                if(strcmp((*Destino)[i],"")==0){
                    continue;
                }   
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
    if(strlen(tecDestino)!=0){
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
            if(strcmp(tecOrigem,(*Origem)[i])==0 && ((*Destino)[i]==NULL||strcmp((*Destino)[i],"")==0)){
                //ja tem
                return;
            }
        }
        //eh novo, deve ser adicionado, mas nao eh par
        (*n)++;
        *Origem= (char **)realloc(*Origem, sizeof(char *) * (*n));
        *Destino= (char **)realloc(*Destino, sizeof(char *) * (*n));
        (*Origem)[(*n)-1] = strdup(tecOrigem);
        (*Destino)[(*n)-1] = strdup(tecDestino);
        
    }
    
}
        
