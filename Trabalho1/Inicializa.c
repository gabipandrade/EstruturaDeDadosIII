#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

CabecalhoArvore *InicializaCabecalho(){ //inicializa o cabeçalho da arvore
    CabecalhoArvore *RegCab=(CabecalhoArvore*)malloc(sizeof(CabecalhoArvore));
    if(RegCab==NULL){
        return NULL;
    }

    RegCab->status='0'; //status do arquivo inicializado com 0
    RegCab->noRaiz=-1; //no raiz inicializado com -1
    RegCab->RRNproxNo=0; //RRN do proximo no inicializado com 0
    
    return RegCab;
}
RegistroCabBIN *CriaStructCabecalho(){//inicializa o cabeçalho do arquivo binario
    RegistroCabBIN *RegCab=(RegistroCabBIN*)malloc(sizeof(RegistroCabBIN));
    if(RegCab==NULL){
        return NULL;
    }

    RegCab->status='0'; //status do arquivo inicializado com 0
    RegCab->proxRRN=0;  //RRN do proximo registro inicializado com 0
    RegCab->nroTecnologias=0;   //numero de tecnologias inicializado com 0
    RegCab->nroParesTecnologias=0; //numero de pares de tecnologias inicializado com 0

    return RegCab;
}

RegistroArvore *InicializaDados(){//inicializa os dados da arvore
    RegistroArvore *RegDados=(RegistroArvore*)malloc(sizeof(RegistroArvore));
    RegDados->nroChavesNo=1;
        
    for(int i=0;i<4;i++){
        RegDados->folha.P[i] = -1; //inicializa P com -1
    }

    for(int i=0;i<3;i++){
        RegDados->folha.PR[i]=-1;// inicializa PR com -1
        RegDados->folha.chave[i]=(char*)calloc(sizeof(char),56); //inicializa chave com \0
    }
    return RegDados;
}

Chave *InicializaChave(RegistroBIN *RegBIN,int RRN){//inicializa a chave da arvore
    Chave *chave=(Chave*)malloc(sizeof(Chave));
    chave->nometec=(char*)malloc(sizeof(char)*56);
    char *str=(char*)malloc(sizeof(char)*56);
    strcpy(str,RegBIN->nomeTecnologiaOrigem); //copia o nome da tecnologia de origem para str   
    strcat(str,RegBIN->nomeTecnologiaDestino); //concatena o nome da tecnologia de destino em str
    chave->PR=RRN;//PR recebe o RRN do registro de dados
    chave->Pdireita=-1;//Pdireita inicializado com -1
    strcpy(chave->nometec,str);//copia str para nometec
    free(str);
    return chave; //retorna a chave
}
    
RegistroBIN *CriaStructRegDados(){//inicializa os dados do arquivo binario
    RegistroBIN* RegBIN=(RegistroBIN*)malloc(sizeof(RegistroBIN));
    if(RegBIN==NULL){
        return NULL;
    }

    strcpy(RegBIN->removido,"0"); //removido inicializado com 0
    RegBIN->nomeTecnologiaDestino=(char*)calloc(50,sizeof(char)); //nomeTecnologiaDestino inicializado com \0
    RegBIN->nomeTecnologiaOrigem=(char*)calloc(50,sizeof(char)); //nomeTecnologiaOrigem inicializado com \0
    
    return RegBIN;//retorna o registro 
}
void LiberaRegistro(RegistroArvore *RegDados){ //free no registro da arvore
    for(int i=0;i<3;i++){
        free(RegDados->folha.chave[i]);    
    }
    free(RegDados);
}
    
void lerLinha(char linha[], RegistroBIN *registro) {
    char nomeorigem[50];
    char valorgrupo[50];
    char valorpopularidade[50];
    char nomedestino[50];
    char valorpeso[50];
    if (sscanf(linha, "%49[^,], %49[^,], %49[^,], %49[^,], %49[^,]", nomeorigem, valorgrupo, valorpopularidade, nomedestino, valorpeso) == 5) 
    // se o sscanf leu os 5 valores esperados, então a linha está correta   
    {
        strcpy(registro->nomeTecnologiaOrigem, nomeorigem); //copia o nome da tecnologia de origem para o registro
        if(strcmp(valorgrupo,"NULO")==0){ //se o valor do grupo for nulo, grupo recebe -1
            registro->grupo = -1;    
        }else{
            registro->grupo = atoi(valorgrupo);//se não for nulo converte para inteiro e copia para o registro
        }
        if(strcmp(valorpopularidade,"NULO")==0){//se o valor da popularidade for nulo, popularidade recebe -1
            registro->popularidade = -1;    
        }else{
            registro->popularidade = atoi(valorpopularidade);//se não for nulo converte para inteiro e copia para o registro
        }
        registro->tamanhoTecnologiaOrigem=strlen(nomeorigem); //atualiza tamanho do nomeTecnologiaOrigem 
        if(strcmp(nomedestino,"NULO")==0){
            strcpy(registro->nomeTecnologiaDestino,"");
            registro->tamanhoTecnologiaDestino=0; //Se for nulo o nome da tecnologia de destino o tamanho recebe 0
        }else{
            strcpy(registro->nomeTecnologiaDestino, nomedestino); //copia o nome da tecnologia de destino para o registro
            registro->tamanhoTecnologiaDestino=strlen(nomedestino);    
        }
        if(strcmp(valorpeso,"NULO")==0){ //se o valor do peso for nulo, peso recebe -1
            registro->peso=-1;
        }else{
            registro->peso = atoi(valorpeso);//se não for nulo converte para inteiro e copia para o registro
        }
    } else {
        printf("Falha no processamento do arquivo.\n");
    }
}
void LimpaRegistroDeDados(RegistroBIN *RegDados){ //Libera o registro de dados
    free(RegDados->nomeTecnologiaDestino);
    free(RegDados->nomeTecnologiaOrigem);
    free(RegDados);
}       

