#include "FuncoesCabecalho.h"
#include "cabeca.h"
#include "AberturaArquivo.h"
#include "FuncoesDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"


/*Funcionalidade 1 tem a função de criar um arquivo binário a partir de um arquivo csv, assim a função começa abrindo os arquivos csv e binário e alocando as variáveis necessárias para a leitura dos dados.
Depois de criado os registros de cabeçalho e de dados, é chamado a função EscreveNoArquivo que faz a escrita dos dados de acordo com os valores do cabeçalho.
*/
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
    int n=0,RRN=0;
    int TamanhoDoLixo;
    int MaxLinha=256;

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

    p=(char*)calloc(256,sizeof(char)); 
    if (p == NULL ) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegDados);
        free(RegCab);
        fclose(arqConvertido);
        fclose(arqOriginal);
        free(p);
        return ;
    }

    fgets(p, MaxLinha, arqOriginal); //Ignora primeira linha
    
    if(EscreveNoArquivo(RegDados,RegCab,p,arqOriginal,arqConvertido,&RRN)==1){
        return;
    }
    
    fseek(arqConvertido,0,SEEK_SET);
    RegCab->status='1';
    RegCab->proxRRN=RRN;
    
    InicializaCabecalho(RegCab,arqConvertido);
    

    LimpaRegistroDeDados(RegDados);
    free(RegCab);
    free(p);

    
    //Fecha Arquivos
    fclose(arqConvertido);
    fclose(arqOriginal);
    binarioNaTela(arqBIN);
    
}

//Funcionalidade [2]
/* SelectFrom função da funcionalidade 2 para recuperar dados do arquivo binário e permitir a exibição correta deles com a indicação de campos nulos.
A função começa recebendo o nome do arquivo binário e o abre para leitura, em seguida aloca memória para o registro de dados e o registro de cabeçalho,
e verifica se a alocação foi bem sucedida, caso não seja, a função é encerrada.Após isso, chama a função LeituraDados que faz a leitura e dá fseek para a posição do tamanho do registro.
Em seguida, a função PrintarDadosRegistro é chamada para printar os dados do registro de dados e exibindo NULO quando necessário, e a função LimpaRegistroDeDados é chamada para liberar a memória alocada para o registro de dados.
*/
void SelectFrom(char *arqBIN){
    FILE *arqConvertido;
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    arqConvertido=AbreArquivoLeituraBIN(arqBIN);
    if(arqConvertido==NULL)return;
    //variaveis de leitura
    RegCab=CriaStructCabecalho();

    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); 
        free(RegCab);
        fclose(arqConvertido);
        return ;
    }
    
    //Leitura do arquivo
    
    RegCab=LeituraCabecalho(RegCab,arqConvertido);
    
    if(RegCab->status=='0'){
        printf("Falha no processamento do arquivo.\n");
        free(RegCab);
        fclose(arqConvertido);
        return;
    }
    //Modificar para for(int i=0;i<reader->ProxRRN)
    for(int i=0;i<RegCab->proxRRN;i++){
        RegDados=CriaStructRegDados();
        if (RegDados ==NULL ) {
            printf("Erro ao alocar memória\n"); 
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
/* A função SelecWhere tem o objetivo de receber um arquivo e realizar n buscas e exibindo o resultado delas. Assim a função começa
abrindo o arquivo e alocando as váriavéis necessárias para a leitura dos dados. Após isso, a função entra em um loop que realiza o número n de buscas desejadas,
é realizado um scanf para saber qual campo será buscado (grupo,popularidade,nomeTecnologiaOrigem,peso ou nomeTecnologiaDestino) com o tipo de busca escolhido a função BuscaWhere é chamada para realizar a busca,
e após isso todos os dados que possuem o campo com o valor buscado são exibidos*/
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
                free(tipo);
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"popularidade")==0){
            scanf("%d",&valor);
            if(BuscaWhere(1,valor,NULL,arqConvertido)==1){
                free(tipo);
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"peso")==0){
            scanf("%d",&valor);
            if(BuscaWhere(2,valor,NULL,arqConvertido)==1){
                free(tipo);
                fclose(arqConvertido);
                return;
            }
        }
        else if(strcmp(tipo,"nomeTecnologiaOrigem")==0){
            nome=(char*)malloc(sizeof(char)*20);
            scan_quote_string(nome);
            if(BuscaWhere(3,-1,nome,arqConvertido)==1){
                free(nome);
                free(tipo);
                fclose(arqConvertido);
                return;
            }
            free(nome);
    
        }
        else if(strcmp(tipo,"nomeTecnologiaDestino")==0){
            nome=(char*)malloc(sizeof(char)*20);
            scan_quote_string(nome);
            if(BuscaWhere(4,-1,nome,arqConvertido)==1){
                free(nome);
                free(tipo);
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
/* A função RecuperaDados tem o objetivo de receber um arquivo e um RRN e exibir os dados do registro de dados que está na posição RRN desejada do arquivo.
Assim, a função começa abrindo o arquivo e alocando as váriavéis necessárias para a leitura dos dados e cabeçalho. Após isso, a função verifica se o RRN desejado existe, quando não existe a mensagem Registro Inexistente é exibida. Caso o RRN exista, a função verifica se o registro foi removido, quando foi removido a mensagem Registro Inexistente é exibida. 
Caso o registro não tenha sido removido, a função LeituraDados é chamada para ler os dados do registro e a função PrintarDadosRegistro é chamada para exibir os dados do registro.
*/
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
        printf("Erro ao alocar memória\n"); 
        free(RegCab);
        fclose(arqConvertido);
        return ;
    }
    
    //Leitura do arquivo
    RegCab=LeituraCabecalho(RegCab,arqConvertido);

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
    RegDados=LeituraDados(RegDados,arqConvertido);
    
    PrintarDadosRegistro(RegDados);
    LimpaRegistroDeDados(RegDados);
    free(RegCab);
    fclose(arqConvertido);
}