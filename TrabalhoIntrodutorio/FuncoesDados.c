#include "FuncoesCabecalho.h"
#include "cabeca.h"
#include "AberturaArquivo.h"
#include "FuncoesDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"

/*Cria a struct do registro de dados alocando as variaveis e iniciando elas*/
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

/*Desaloca os dados do registro de dados*/
void LimpaRegistroDeDados(RegistroDeDados *RegDados){
    free(RegDados->nomeTecnologiaDestino);
    free(RegDados->nomeTecnologiaOrigem);
    free(RegDados);
}       

/*Recebe o registro de dados e printa cada um dos campos sendo eles: 
nomeTecnologiaOrigem,grupo,popularidade,nomeTecnologiaDestino e peso sendo que quando o grupo, popularidade e peso são iguais a -1 é exibido nulo e 
quando o tamanho da tecnologia destino é 0 o nomeTecnologiaDestino é nulo*/
void PrintarDadosRegistro(RegistroDeDados *RegDados){
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

/*Função para Leitura de Dados no qual é lido cada um dos campos do registro de dados, 
e após isso dado um fseek para a posição do tamanho do registro*/
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


/*Função auxiliar da funcionalidade 3 na qual cria e aloca as structs e após isso confere se o status é 1, ou seja o arquivo foi aberto corretamente
com isso é realizado a busca e exibido os dados que possuem o valor desejado*/
int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido){
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    char readerChar;
    RegCab=CriaStructCabecalho();

    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegCab);
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
            free(RegCab);
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

/*Função para escrever  palavras*/
void EscrevePalavras(char *string,FILE *arq,int tamanho){
    fwrite(string,sizeof(char),tamanho,arq);
}

/*Função da funcionalidade 1 para escrever no arquivo, faz a leitura pulando a primeira linha e vai escrevendo para binario atualizando o valor do RRN e contando o número de pares e de tecnologias*/

int EscreveNoArquivo(RegistroDeDados *RegDados,RegistroCabecalho*RegCab,char *p,FILE *arqOriginal,FILE *arqConvertido,int *RRN){
    int MaxLinha=256;
    char *str1; // Variável para armazenar a primeira string
    int num1, num2, num3; // Variáveis para armazenar os números
    char *str2; // Variável para armazenar a segunda string
    char **Origem,**Destino;
	int n=0;
    int TamanhoDoLixo;
    char *token;

    //Leitura do arquivo
    str1=(char*)calloc(50,sizeof(char)); 
    str2=(char*)calloc(50,sizeof(char)); 
    if(str1==NULL || str2==NULL){
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        free(p);
        return 1;    
    }
    
    while (fgets(p, MaxLinha, arqOriginal) != NULL) {
        
        // Usando strtok para dividir a linha em campos
        token = strtok(p, ",");
        if (token) {
            str1 = strdup(token);
            token = strtok(NULL, ",");
            if (token) {
                num1 = atoi(token);
                token = strtok(NULL, ",");
                if (token) {
                    num2 = atoi(token);
                    token = strtok(NULL, ",");
                    if (token) {
                        // Verifique se o campo correspondente a str2 está vazio
                        if (strlen(token) == 0) {
                            str2 = NULL;
                        } else {
                            str2 = strdup(token);
                        }
                        token = strtok(NULL, ",");
                        if (token) {
                            num3 = atoi(token);
                        }
                    }
                }
            }
        }
        if(str2==NULL){
            RegDados->nomeTecnologiaDestino=NULL;
            RegDados->tamanhoTecnologiaDestino=0;
        }else{
            str2=realloc(str2,strlen(str2));
            strcpy(RegDados->nomeTecnologiaDestino,str2);
            RegDados->tamanhoTecnologiaDestino=strlen(str2);
        }
        str1=realloc(str1,strlen(str1));
                
        strcpy(RegDados->nomeTecnologiaOrigem,str1);
        RegDados->tamanhoTecnologiaOrigem=strlen(str1);
        RegDados->grupo=num1;
        RegDados->popularidade=num2;
        RegDados->peso=num3;
        
        ContadorTecnologias(RegCab,&Origem,&Destino,str1,str2,&n);
        
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
            fwrite("$",sizeof(char),1,arqConvertido);
        }
        (*RRN)++;
    }
    
    for(int i=0;i<n;i++){
        free(Origem[i]);
        free(Destino[i]);
    }
    
    free(Origem);
    free(Destino);
    
    free(str1);
    free(str2);
    
}