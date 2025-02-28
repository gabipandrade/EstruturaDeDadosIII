#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

// Função para busca binária pelo nome no No
int BuscaBinNo(RegistroArvore *RegDados,char*nome) { 
    int inicio = 0;
    int tamanho=RegDados->nroChavesNo;
    int fim = tamanho - 1; 
    char *chave;
    chave=nome;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        // Comparação do elemento no meio com a chave
        // Se a chave for igual ao elemento no meio, retornamos a posição
        if (strcmp(RegDados->folha.chave[meio],chave)== 0) {
            return RegDados->folha.PR[meio];
        }

        // Se a chave for menor, busca na metade à esquerda
        if (strcmp(RegDados->folha.chave[meio],chave)> 0) {
            fim = meio - 1;
        }
        // Se a chave for maior, busca na metade à direita
        else {
            inicio = meio + 1;
        }
    }

    // Chave não encontrada
    return -1;
}

int BuscaIndex(char *nome,FILE * arqReadIndex,FILE *arqRead){ //Busca no arquivo de indice
    int posicao=0;
    CabecalhoArvore *RegCab;
    RegistroArvore *RegDados;

    RegCab=InicializaCabecalho();
    RegDados=InicializaDados();
    
    if (RegCab == NULL|| RegDados == NULL) {
        printf("Falha no processamento do arquivo.\n"); 
        free(RegCab);
        free(RegDados);
        return 1;
    }

    
    RegCab=LeituraCabecalho(RegCab,arqReadIndex);
    
    if(RegCab->status=='0'){ //Se o arquivo de indice estiver inconsistente falha no processamento
        printf("Falha no processamento do arquivo.\n");
        free(RegCab);
        free(RegDados);
        return 1;
    }     
    fseek(arqReadIndex,(RegCab->noRaiz)*(TAM_REGISTRO),SEEK_CUR);
    
    LeituraArqIndex(RegDados,arqReadIndex); //leitura arquivo indice
    
    while(posicao!=-1){   
        if(BuscaBinNo(RegDados,nome)!=-1){
            break;
        }
        posicao=PosicaoNaArvore(RegDados,nome);
    
        if(posicao!=-1){
            fseek(arqReadIndex,(posicao+1)*(TAM_REGISTRO),SEEK_SET);
            LeituraArqIndex(RegDados,arqReadIndex);
        }
    }

    if(posicao==-1){    //Se nao encontrei->-1, registro inexistente
        printf("Registro inexistente.\n");
        return 0;
    }
    posicao=0;
    RecuperaDados(arqRead, BuscaBinNo(RegDados,nome)); //se encontrei, recupero os dados
    
    return 0;
}
int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido){ //Busca no arquivo binario o campo a ser buscado e exibido
    RegistroBIN *RegDados;
    RegistroCabBIN *RegCab;
    char readerChar;
    char done=0;
    RegCab=CriaStructCabecalho();

    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); 
        free(RegCab);
        return 1;
    }

    RegCab=LeituraCabecalhoBIN(RegCab,arqConvertido);
    
    if(RegCab->status=='0'){ //Se o arquivo de indice estiver inconsistente falha no processamento
        printf("Falha no processamento do arquivo.\n");
        free(RegCab);
        
        return 1;
    }
    while(fread(&readerChar,1,1,arqConvertido)!=0){ //leio o arquivo binario
        ungetc(readerChar,arqConvertido);
        RegDados=CriaStructRegDados();
    
        if (RegDados ==NULL ) {
            printf("Erro ao alocar memória\n"); 
            LimpaRegistroDeDados(RegDados);
            free(RegCab);
            return 1;
        }
    
        RegDados=LerBIN(RegDados,arqConvertido);
        
        if(escolha ==0 && RegDados->grupo==valor){ //comparo o campo a ser buscado com o valor
            done=1;
            PrintarDadosRegistro(RegDados);//se for igual, printo
        } 
        else if(escolha ==1 && RegDados->popularidade==valor){ 
            done=1;
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==2 && RegDados->peso==valor){ 
            done=1;
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==3 && strcmp(RegDados->nomeTecnologiaOrigem,nome)==0){
            done=1;
            PrintarDadosRegistro(RegDados);
        }
        else if(escolha ==4 && strcmp(RegDados->nomeTecnologiaDestino,nome)==0){
            done=1;
            PrintarDadosRegistro(RegDados);
        }
        LimpaRegistroDeDados(RegDados);    
    }
    if(done==0){ //se não for encontrado nenhum registro com o campo a ser buscado, registro inexistente
        printf("Registro inexistente.\n");
    }
    free(RegCab);
    return 0;
}