#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */
	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
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
    if(strcmp(RegDados->nomeTecnologiaDestino,cifrao)==1){
        printf(", NULO");
    }
    else{
        printf(", %s",RegDados->nomeTecnologiaDestino);    
    }
    if(RegDados->peso=='$'){
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
//Funcionalidade [1]
void createTable(char *arqCSV,char *arqBIN){
    //ponteiros para arquivo
    FILE *arqOriginal;
    FILE *arqConvertido;
    
    //ponteiros para registros
    RegistroCabecalho *RegCab;
    RegistroDeDados *RegDados;
    //variaveis de leitura
    char *p;
    int MaxLinha=256;
    char *str1; // Variável para armazenar a primeira string
    int num1, num2, num3; // Variáveis para armazenar os números
    char *str2; // Variável para armazenar a segunda string


    arqOriginal=AbreArquivoLeituraCSV(arqCSV);    
    arqConvertido=AbreArquivoEscritaBIN(arqBIN);
    RegCab=CriaStructCabecalho();
    RegDados=CriaStructRegDados();

    if(arqConvertido==NULL || arqConvertido==NULL){
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        return;
    }
    //da fwrite no cabecalho no arquivo Binario
    InicializaCabecalho(RegCab,arqConvertido);

    //Leitura do arquivo
    str1=(char*)calloc(50,sizeof(char)); 
    str2=(char*)calloc(50,sizeof(char)); 
    p=(char*)calloc(256,sizeof(char)); 
    if (p == NULL || str1 ==NULL || str2==NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        free(p);
        free(str1);
        free(str2);
        return ;
    }

    fgets(p, MaxLinha, arqOriginal); //Ignora primeira linha
    
    
    
    while (fgets(p, MaxLinha, arqOriginal) != NULL) {    
        if (sscanf(p, "%49[^,],%d,%d,%49[^,],%d", str1, &num1, &num2, str2, &num3) == 5) {
            // Agora, as variáveis contêm os valores lidos
            //nomeTecnologiaOrigem,grupo,popularidade,nomeTecnologiaDestino,peso
            //str1=nomeTecnologiaOrigem
            //num1=grupo
            //num2=popularidade
            //str2=nomeTecnologiaDestino
            //num3=peso
            str1=realloc(str1,strlen(str1));
            str2=realloc(str2,strlen(str2));
            
            strcpy(RegDados->nomeTecnologiaOrigem,str1);
            RegDados->tamanhoTecnologiaOrigem=strlen(str1);
            RegDados->grupo=num1;
            RegDados->popularidade=num2;
            strcpy(RegDados->nomeTecnologiaDestino,str2);
            RegDados->tamanhoTecnologiaDestino=strlen(str2);
            RegDados->peso=num3;
            
            fwrite(&(RegDados->removido),sizeof(char),1,arqConvertido);
            fwrite(&(RegDados->grupo),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->peso),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arqConvertido);
            fwrite(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
            fwrite(&(RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arqConvertido);
        }

    }
    
    
    free(RegDados);
    free(RegCab);
    free(p);
    free(str1);
    free(str2);
    binarioNaTela(arqBIN);
    fclose(arqConvertido);
    fclose(arqOriginal);
    
}
//Funcionalidade [2]
void SelectFrom(char *arqBIN){
    FILE *arqConvertido;
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    arqConvertido=AbreArquivoLeituraBIN(arqBIN);
    if(arqConvertido==NULL)return;
    //variaveis de leitura
     RegCab=CriaStructCabecalho();
    
    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegCab);
        fclose(arqConvertido);
        return ;
    }

    //Leitura do arquivo
    
    RegCab=LeituraCabecalho(RegCab,arqConvertido);
    
    //Modificar para for(int i=0;i<reader->ProxRRN)
    for(int i=0;i<RegCab->proxRRN;i++){
        RegDados=CriaStructRegDados();
        if (RegDados ==NULL ) {
            printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
            LimpaRegistroDeDados(RegDados);
            fclose(arqConvertido);
            return ;
        }

        RegDados=LeituraDados(RegDados,arqConvertido);
        
        PrintarDadosRegistro(RegDados);

        LimpaRegistroDeDados(RegDados);
    }
    
    free(RegCab);
    fclose(arqConvertido);
}
//Funcionalidade [3]
//Funcionalidade [4]
void RecuperaDados(char *arqBIN, int RRN){
    FILE *arqConvertido;
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    char readerChar;
    arqConvertido=AbreArquivoLeituraBIN(arqBIN);
    if(arqConvertido==NULL)return;

    //variaveis de leitura
    RegCab=CriaStructCabecalho();
    
    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegCab);
        fclose(arqConvertido);
        return ;
    }

    //Leitura do arquivo
    
    RegCab=LeituraCabecalho(RegCab,arqConvertido);
    //CASO1: RRN nao existe
    if(RRN>RegCab->proxRRN){
        printf("Registro Inexistente\n");
        free(RegDados);
        return;
    }
    //CASO2: RRN foi removido
    fseek(arqConvertido,RRN*76,SEEK_CUR);
    fread(&readerChar,1,1,arqConvertido);
    if(readerChar=='1'){
        printf("Registro Inexistente\n");
        return;
    }
    //CASO3: RRN valido

    RegDados=CriaStructRegDados();
    if (RegDados ==NULL ) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        LimpaRegistroDeDados(RegDados);
        fclose(arqConvertido);
        return ;
    }

    RegDados=LeituraDados(RegDados,arqConvertido);
    
    PrintarDadosRegistro(RegDados);

    LimpaRegistroDeDados(RegDados);

}