#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cabeca.h"


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
    char **Origem,**Destino;
	int n=0,RRN=1;
    
	

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
            ContadorTecnologias(RegCab,&Origem,&Destino,str1,str2,&n);
            RRN++;
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
    
    fseek(arqConvertido,0,SEEK_SET);
    RegCab->status='1';
    RegCab->proxRRN=RRN;
    
    InicializaCabecalho(RegCab,arqConvertido);
    
    

    LimpaRegistroDeDados(RegDados);
    free(RegCab);
    free(p);

    for(int i=0;i<n;i++){
        free(Origem[i]);
        free(Destino[i]);
    }
    
    free(Origem);
    free(Destino);
    
    free(str1);
    free(str2);
    
    binarioNaTela(arqBIN);
    //Fecha Arquivos
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
void SelecWhere(char *arqBIN,int n){
    FILE *arqConvertido;
    char *tipo;
    char *nome;
    int valor;
    
    arqConvertido=AbreArquivoLeituraBIN(arqBIN);
    if(arqConvertido==NULL)return;
    

    for(int i=0;i<n;i++){
        tipo=(char*)malloc(sizeof(char)*10);
        scanf("%s",tipo);
        // grupo, popularidade, peso,tamanho origem, nome origem, tamanho destino, nome destino
        if(strcmp(tipo,"grupo")==0){
            scanf("%d",&valor);
            if(BuscaWhere(0,valor," ",arqConvertido)==1){
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"popularidade")==0){
            scanf("%d",&valor);
            if(BuscaWhere(1,valor,NULL,arqConvertido)==1){
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"peso")==0){
            scanf("%d",&valor);
            if(BuscaWhere(2,valor,NULL,arqConvertido)==1){
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"nomeTecnologiaOrigem")==0){
            nome=(char*)malloc(sizeof(char)*20);
            scan_quote_string(nome);
            if(BuscaWhere(3,-1,nome,arqConvertido)==1){
                fclose(arqConvertido);
                return;
            }
            free(nome);
    
        }
        else if(strcmp(tipo,"nomeTecnologiaDestino")==0){
            nome=(char*)malloc(sizeof(char)*20);
            scan_quote_string(nome);
            if(BuscaWhere(4,-1,nome,arqConvertido)==1){
                fclose(arqConvertido);                
                return;
            }
            free(nome);
        }
        fseek(arqConvertido,0,SEEK_SET);
        free(tipo);
    }

    fclose(arqConvertido);
}
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
        printf("Registro inexistente.\n");
        free(RegDados);
        return;
    }
    //CASO2: RRN foi removido
    fseek(arqConvertido,RRN*76,SEEK_CUR);
    fread(&readerChar,1,1,arqConvertido);

    if(readerChar=='1'){
        printf("Registro inexistente.\n");
        return;
    }
    
    ungetc(readerChar,arqConvertido);

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