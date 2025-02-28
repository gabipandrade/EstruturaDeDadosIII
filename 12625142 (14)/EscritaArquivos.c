#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

FILE *AbreArquivoEscritaBIN(char *arq){ //abre o arquivo para escrita com o modo wb+
    FILE *arquivo;    
    arquivo= fopen(arq,"wb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

int EscreveDadosNoArquivo(RegistroArvore *RegDados,FILE*arq){//escreve os dados no arquivo de indice
    //Escrita do cabecalho
    fwrite(&(RegDados->nroChavesNo),sizeof(int),1,arq);
    fwrite(&(RegDados->alturaNo),sizeof(int),1,arq);
    fwrite(&(RegDados->RRNdoNo),sizeof(int),1,arq);   
    fwrite(&(RegDados->folha.P[0]),sizeof(int),1,arq);
    //Escrita chave 1
    EscrevePalavras(RegDados->folha.chave[0],arq,55);
    fwrite(&(RegDados->folha.PR[0]),sizeof(int),1,arq);
    fwrite(&(RegDados->folha.P[1]),sizeof(int),1,arq);
    //Escrita chave 2
    EscrevePalavras(RegDados->folha.chave[1],arq,55);
    fwrite(&(RegDados->folha.PR[1]),sizeof(int),1,arq);
    fwrite(&(RegDados->folha.P[2]),sizeof(int),1,arq);
    //Escrita chave 3
    EscrevePalavras(RegDados->folha.chave[2],arq,55);
    fwrite(&(RegDados->folha.PR[2]),sizeof(int),1,arq);
    fwrite(&(RegDados->folha.P[3]),sizeof(int),1,arq);

    return 0;
}

void EscrevePalavras(char *string,FILE *arq,int tamanho){//escreve as palavras no arquivo 
    int TamanhoDoLixo;
    fwrite(string,sizeof(char)*strlen(string),1,arq);
    TamanhoDoLixo=tamanho-strlen(string);
    for(int i=0;i<TamanhoDoLixo;i++){
        fwrite("$",sizeof(char),1,arq); //escreve o lixo
    }
}

int EscreveDadosNoBIN(RegistroBIN *RegDados,FILE *arqConvertido){//escreve os dados no arquivo binario
    int TamanhoDoLixo;  
    fwrite(&(RegDados->removido),sizeof(char),1,arqConvertido);
    fwrite(&(RegDados->grupo),sizeof(int),1,arqConvertido);
    fwrite(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
    fwrite(&(RegDados->peso),sizeof(int),1,arqConvertido);
    fwrite(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
    EscrevePalavras(RegDados->nomeTecnologiaOrigem,arqConvertido,RegDados->tamanhoTecnologiaOrigem);
    fwrite(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
    EscrevePalavras(RegDados->nomeTecnologiaDestino,arqConvertido,RegDados->tamanhoTecnologiaDestino); 
    
    TamanhoDoLixo=76 - 21 -(RegDados->tamanhoTecnologiaOrigem+RegDados->tamanhoTecnologiaDestino);
    
    for(int i=0;i<TamanhoDoLixo;i++){
        fwrite("$",sizeof(char),1,arqConvertido);//escreve o lixoQ
    }
    return 0;
}

int EscreveCabecalhoArvore(CabecalhoArvore*RegCab,FILE*arq){ //escreve o cabecalho da arvore

    int TamanhoDoLixo=196; //tamanho do lixo
    fwrite(&(RegCab->status),sizeof(char),1,arq); //escreve o status do cabecalho
    fwrite(&(RegCab->noRaiz),sizeof(int),1,arq); //escreve o no raiz do cabecalho
    fwrite(&(RegCab->RRNproxNo),sizeof(int),1,arq);//escreve o RRN do proximo no do cabecalho   
    for(int i=0;i<TamanhoDoLixo;i++){
        fwrite("$",sizeof(char),1,arq); //escreve o lixo
    }
    return 0;
}
void Insert_Into(FILE*arqRead,FILE*arqReadIndice,int n){ //insere os dados no arquivo binario e no arquivo de indice
    RegistroCabBIN *RegCabBIN;
        RegistroCabBIN *RegCabBIN1;
        
        CabecalhoArvore *RegCab;
        RegistroBIN *registro;
        int RRN;
        char **Origem,**Destino;
        int n1=0;
        RegCabBIN=CriaStructCabecalho();
        RegCabBIN1=CriaStructCabecalho();
        RegCab=InicializaCabecalho();
        
        RegCabBIN = LeituraCabecalhoBIN(RegCabBIN,arqRead);
        RegCab = LeituraCabecalho(RegCab,arqReadIndice);
        
        RRN=RegCabBIN->proxRRN;
        getchar();
        for (int i = 0; i < n; i++) {
            registro= CriaStructRegDados();
            char linha[50];
            fgets(linha, 50, stdin); //le a linha
            linha[strcspn(linha, "\n")] = '\0';
            lerLinha(linha, registro); //le a linha e armazena no registro
            fseek(arqRead,13+RRN*76,SEEK_SET);
            EscreveDadosNoBIN(registro,arqRead); //escreve os dados no arquivo de dados
            
            if((registro->tamanhoTecnologiaOrigem==0)||(registro->tamanhoTecnologiaDestino==0)){
                RRN++; //se nao tiver tecnologia, nao escreve no arquivo de indice e pula para o proximo registro
                continue;
            }
            //Escreve no Arquivo de Indice
            AdicionaNaArvore(registro,RegCabBIN,arqReadIndice,RegCab,RRN); 
            RRN++;
        }
        
        //Modifica os dados e conta as tecnologias apos insercao
        fseek(arqReadIndice,0,SEEK_SET);
        EscreveCabecalhoArvore(RegCab,arqReadIndice);
    
        LerArquivoBinarioParaContagemTecnologias(&Origem,&Destino,RegCabBIN1,&n1,arqRead); //le o arquivo binario para contar as tecnologias
        RegCabBIN->nroParesTecnologias=RegCabBIN1->nroParesTecnologias;//atualiza o numero de pares de tecnologias
        RegCabBIN->nroTecnologias=RegCabBIN1->nroTecnologias; //atualiza o numero de tecnologias
        RegCabBIN->proxRRN=RegCabBIN->proxRRN+n; //atualiza o proximo RRN
        //Atualizaca cabecalho
        fseek(arqRead,0,SEEK_SET);
        InicializaCabecalhoBIN(RegCabBIN,arqRead);    
        
        for(int i=0;i<n;i++){
            free(Origem[i]);
            free(Destino[i]);
        }
        
        free(Origem);
        free(Destino);

}