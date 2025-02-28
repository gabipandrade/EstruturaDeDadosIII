#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

/* A função SelecWhere tem o objetivo de receber um arquivo e realizar n buscas e exibindo o resultado delas. Assim a função começa
abrindo o arquivo e alocando as váriavéis necessárias para a leitura dos dados. Após isso, a função entra em um loop que realiza o número n de buscas desejadas,
é realizado um scanf para saber qual campo será buscado (grupo,popularidade,nomeTecnologiaOrigem,peso ou nomeTecnologiaDestino) ou se será busca a chave de busca(concatenação de NomeTecnologiaOrigem com NomeTecnologiaDestino) com o tipo de busca escolhido a função BuscaWhere é chamada para realizar a busca se for utilizado um campo
ou a função BuscaIndex(busca no arquivo de indice) na qual busca é chamada se for utilizado a chave de busca 
e após isso todos os dados que possuem o campo com o valor buscado são exibidos*/
void SelecWhere(FILE *arqRead,FILE *arqReadIndex,int n){
    char *tipo;
    char *nome;
    int valor;

    for(int i=0;i<n;i++){
        tipo=(char*)malloc(sizeof(char)*30);
        scanf("%s",tipo);
        // grupo, popularidade, peso,tamanho origem, nome origem, tamanho destino, nome destino
        if(strcmp(tipo,"grupo")==0){
            scanf("%d",&valor);
            if(BuscaWhere(0,valor," ",arqRead)==1){
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);
                return;
            }
        }
        else if(strcmp(tipo,"popularidade")==0){
            scanf("%d",&valor);
            if(BuscaWhere(1,valor,NULL,arqRead)==1){
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);
                return;
            }
        }
        else if(strcmp(tipo,"peso")==0){
            scanf("%d",&valor);
            if(BuscaWhere(2,valor,NULL,arqRead)==1){
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);
                return;
            }
        }
        else if(strcmp(tipo,"nomeTecnologiaOrigem")==0){
            nome=(char*)malloc(sizeof(char)*25);
            scan_quote_string(nome);
            if(BuscaWhere(3,-1,nome,arqRead)==1){
                free(nome);
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);
                return;
            }
            free(nome);
    
        }
        else if(strcmp(tipo,"nomeTecnologiaDestino")==0){
            nome=(char*)malloc(sizeof(char)*25);
            scan_quote_string(nome);
            if(BuscaWhere(4,-1,nome,arqRead)==1){
                free(nome);
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);                                
                return;
            }
            free(nome);
        }else if(strcmp(tipo,"nomeTecnologiaOrigemDestino")==0){
            nome=(char*)malloc(sizeof(char)*25);
            scan_quote_string(nome);
            if(BuscaIndex(nome,arqReadIndex,arqRead)==1){
                free(nome);
                free(tipo);
                fclose(arqRead);
                fclose(arqReadIndex);                
                return;
            }
            
            
            free(nome);
        }
        fseek(arqRead,0,SEEK_SET);
        fseek(arqReadIndex,0,SEEK_SET);
        free(tipo);
    }
}
void PrintarDadosRegistro(RegistroBIN *RegDados){//exibe dados do registro
    if(strcmp(RegDados->removido,"1")!=0){  //se o registro nao foi removido   
        printf("%s",RegDados->nomeTecnologiaOrigem);
        if(RegDados->grupo==-1){ //se o campo for nulo
            printf(", NULO");
        }else{
            printf(", %d",RegDados->grupo);    
        }
        if(RegDados->popularidade==-1){ //se o campo for nulo
            printf(", NULO");
        }else{
        printf(", %d",RegDados->popularidade);    
        }
        if(RegDados->tamanhoTecnologiaDestino==0){ //se o campo for nulo
            printf(", NULO");
        }
        else{
            printf(", %s",RegDados->nomeTecnologiaDestino);    
        }
        if(RegDados->peso==-1){//se o campo for nulo
            printf(", NULO\n");
        }else{
            printf(", %d\n",RegDados->peso);    
        }
    }
    
}

void RecuperaDados(FILE *arqConvertido, int RRN){ //Recupera Dados para Exibir utilizando o RRN do dado a ser buscado
    RegistroBIN *RegDados;
    RegistroCabBIN *RegCab;
    char readerChar;
    
    
    //variaveis de leitura
    RegCab=CriaStructCabecalho();
    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); 
        free(RegCab);
        fclose(arqConvertido);
        return ;
    }
    
    //Leitura do arquivo
    RegCab=LeituraCabecalhoBIN(RegCab,arqConvertido);

    if(RegCab->status=='0'){
        printf("Falha no processamento do arquivo.\n");
        free(RegCab);
        fclose(arqConvertido);
        return;
    } 
    //CASO1: RRN nao existe
    if(RRN>RegCab->proxRRN){
        printf("Registro inexistente.\n");
        free(RegCab);
        fclose(arqConvertido);
        return;
    }

    //CASO2: RRN foi removido
    fseek(arqConvertido,RRN*76,SEEK_CUR);
    fread(&readerChar,1,1,arqConvertido);

    if(readerChar=='1'){
        printf("Registro inexistente.\n");
        free(RegCab);
        fclose(arqConvertido);
        return;
    }
    
    ungetc(readerChar,arqConvertido);

    //CASO3: RRN valido
    RegDados=CriaStructRegDados();
    if (RegDados ==NULL ) {
        printf("Erro ao alocar memória\n"); 
        LimpaRegistroDeDados(RegDados);
        fclose(arqConvertido);
        return ;
    }
    RegDados=LerBIN(RegDados,arqConvertido);
    
    PrintarDadosRegistro(RegDados); //exibe os dados do registro recuperado
    LimpaRegistroDeDados(RegDados);
    free(RegCab);
    
}
