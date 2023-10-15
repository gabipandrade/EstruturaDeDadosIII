#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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



int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido){
    RegistroDeDados *RegDados;
    RegistroCabecalho *RegCab;
    char readerChar;
    RegCab=CriaStructCabecalho();

    if (RegCab == NULL) {
        printf("Erro ao alocar memória\n"); //REMOVER NO FUTURO
        free(RegCab);
        fclose(arqConvertido);
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

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}
void ContadorTecnologias(RegistroCabecalho *RegCab,char ***Origem,char ***Destino,char *tecOrigem,char *tecDestino,int *n){
    if((*n)==0){
        (*n)++;
        *Origem=(char** )malloc(sizeof(char*)*(*n));
	    *Destino=(char**)malloc(sizeof(char)*(*n));

        // Verifica alocacao
        if (*Origem == NULL || *Destino == NULL) {
        printf("Erro na alocação de matriz\n");
        return ;
        }
        for (int i = 0; i < *n; i++) {
            (*Origem)[i] = NULL;
            (*Destino)[i] = NULL;
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
        if(strcmp(tecOrigem,(*Origem)[i])==0){
            a=1;
            break;
        }
    }
    
    if(a==0){
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Destino)[i])==0){
                a=1;
                break;
            }
        }
    }
    
    if(tecDestino==NULL){
        b=1;
    }else{
        for(int i=0;i<(*n);i++){
            if(strcmp(tecDestino,(*Origem)[i])==0){
                b=1;
                break;
            }
        }
        if(b==0){
            for(int i=0;i<(*n);i++){
                if(strcmp(tecDestino,(*Destino)[i])==0){
                    b=1;
                    break;
                }
            }
        }    
    }
    
    if(a==0){
        if(b==0){
            //a=0 e b=0 nenhuma eh repetida
            RegCab->nroTecnologias+=2;

        }else{
            //a=0 e b=1 uma eh repetida
            RegCab->nroTecnologias++;
        }
    }else{
        if(b==0){
            //a=1 e b=0 uma eh repetida
            RegCab->nroTecnologias++;
        }else{
            //a=1 e b=1 as duas sao repetidas
        }
    }

    //Verificacao dos Pares de Tecnologias
    if(tecDestino!=NULL){
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
        (*Destino)[(*n)-1] = strdup(tecOrigem);
    }
    else{
        for(int i=0;i<(*n);i++){
            if(strcmp(tecOrigem,(*Origem)[i])==0 && (*Destino)[i]==NULL){
                //ja tem
                return;
            }
        }
        //eh novo, deve ser adicionado, mas nao eh par
        (*n)++;
        *Origem= (char **)realloc(*Origem, sizeof(char *) * (*n));
        *Destino= (char **)realloc(*Destino, sizeof(char *) * (*n));
        (*Origem)[(*n)-1] = strdup(tecOrigem);
        (*Destino)[(*n)-1] = NULL;
        
    }
    
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
    char **Origem,**Destino;
	int n=0;
    
	

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
            printf("Origem:  %s   Destino:   %s\n",str1,str2);
            
            strcpy(RegDados->nomeTecnologiaOrigem,str1);
            RegDados->tamanhoTecnologiaOrigem=strlen(str1);
            RegDados->grupo=num1;
            RegDados->popularidade=num2;
            strcpy(RegDados->nomeTecnologiaDestino,str2);
            RegDados->tamanhoTecnologiaDestino=strlen(str2);
            RegDados->peso=num3;
            ContadorTecnologias(RegCab,&Origem,&Destino,str1,str2,&n);
            
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
    
    for(int i=0;i<n;i++){
        printf("ORIGEM:    %s DESTINO: %s\n",Origem[i],Destino[i]);
    }

    printf("nro tecnologias:%d\n",RegCab->nroTecnologias);
    printf("nro pares tecnologias:%d\n",RegCab->nroParesTecnologias);
    
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