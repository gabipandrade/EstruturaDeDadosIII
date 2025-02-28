#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

//Funcionalidade 5 le o arquivo binário da árvore e cria o arquivo de indice
void Funcionalidade5(char *arqBIN1,char *arqBIN2){
    FILE *arqRead;
    FILE *arqWrite;
    arqRead=AbreArquivoLeituraBIN(arqBIN1); //arquivo leitura
    arqWrite=AbreArquivoEscritaBIN(arqBIN2);//arquivo escrita 

    if(arqRead==NULL ||arqWrite==NULL){ //verifica se os arquivos foram abertos corretamente
        return;
    }else{
        LeituraDadosParaAdicao(arqRead,arqWrite); //le os dados do arquivo binario e escreve no arquivo de indice usando a Funçaõ LeituraDadosParaAdicao
    }
    fclose(arqRead);//fecha arquivos
    fclose(arqWrite);
    binarioNaTela(arqBIN2); //binario na tela para conferir arquivo de indice


}
/*Funcionalidade 6 le o arquivo binário e de indice e realiza n buscas utilizando um campo do arquivo binario (grupo,popularidade,nomeTecnologiaOrigem,peso ou nomeTecnologiaDestino) 
ou se será busca a chave de busca no arquivo de indice(concatenação de NomeTecnologiaOrigem com NomeTecnologiaDestino) */
void Funcionalidade6(char *arqBIN1,char *arqBIN2,int n){
    FILE *arqRead;
    FILE *arqReadIndice;
    
    arqRead=AbreArquivoLeituraBIN(arqBIN1);
    arqReadIndice=AbreArquivoLeituraBIN(arqBIN2);

    if(arqRead==NULL ||arqReadIndice==NULL){
        return;
    }else{
        SelecWhere(arqRead,arqReadIndice,n);    
    }
    
    fclose(arqRead);
    fclose(arqReadIndice);
}
void Funcionalidade7(char *arqBIN1,char *arqBIN2,int n){ //Funcionalidade 7 le o arquivo binário e de indice e realiza n inserções
    FILE *arqRead;
    FILE *arqReadIndice;
    arqRead=AbreArquivoLeituraEscritaBIN(arqBIN1);
    arqReadIndice=AbreArquivoLeituraEscritaBIN(arqBIN2);
    if(arqRead==NULL ||arqReadIndice==NULL){
        return;
    }else{
        Insert_Into(arqRead,arqReadIndice,n); //função que realiza as inserções
    }
    fclose(arqRead);
    fclose(arqReadIndice);
    
    binarioNaTela(arqBIN1); //binario na tela para conferir arquivo 
    binarioNaTela(arqBIN2); //binario na tela para conferir arquivo de indice
}
