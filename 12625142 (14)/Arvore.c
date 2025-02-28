#include "Arvore.h"
#include "Busca.h"
#include "cabeca.h"
#include "EscritaArquivos.h"
#include "ExibeDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"
//BUSCA BINARIA DA POSICAO QUE DEVE SER ADICIONADA NA ARVORE
//Pois para optimizacao, ela inicia a busca primeiro verificando se tem ao menos duas chaves, posteriormente, verifica em relacao a folha.chave do meio se
//o nome que esta sendo buscado eh maior ou menor que ele, para entao dividir em procurar antes ou depois desse nome
int PosicaoNaArvore(RegistroArvore *RegDados,char *nome) {//Compara as chaves e descobre a posição onde deve ser adicionado o novo registro
    char *chave;
    chave=nome;
    //Comapara com chave do meio:
    if(RegDados->nroChavesNo>=2){
        if(strcmp(chave,RegDados->folha.chave[1])< 0){ //A chave eh menor que a segunda chave
            if(strcmp(chave,RegDados->folha.chave[0])< 0){
                return (RegDados->folha.P[0]);
            }else{//
                return (RegDados->folha.P[1]);
            }
        }else{//strcmp(chave,RegDados->folha.chave[1]) > 0 //A chave eh maior que a segunda chave
            if(RegDados->nroChavesNo==3){
                if(strcmp(chave,RegDados->folha.chave[2]) < 0){
                    return (RegDados->folha.P[2]);
                }else{
                    return (RegDados->folha.P[3]);
                }
            }else{
                return (RegDados->folha.P[2]);
            }   
        }
    }else{
        if(strcmp(chave,RegDados->folha.chave[0])< 0) { //Se a chave for menor que a primeira chave, retorna 0
            return (RegDados->folha.P[0]);    
        }else{
            return (RegDados->folha.P[1]);
        }

    }
}

int AdicionaNaArvore(RegistroBIN *RegBIN,RegistroCabBIN *RegCabBIN,FILE *arqIndex,CabecalhoArvore *RegCab,int RRN){//adiciona na arvore um registro
    RegistroArvore *RegDados; 
    Chave *promove; //Chave que sera promovida
    RegDados=InicializaDados();
    promove=InicializaChave(RegBIN,RRN);//Inicializa a chave que sera promovida
    int posicao;
    
    if(RegCab->noRaiz==-1){ //se a raiz for -1, ou seja, se a arvore estiver vazia cria o nó raiz
        RegCab->noRaiz++;
        RegCab->RRNproxNo++;
        
        RegDados->alturaNo=1;
        RegDados->RRNdoNo=RegCab->noRaiz;
        RegDados->folha.PR[0]=RRN;
        
        strcpy(RegDados->folha.chave[0],promove->nometec); //a chave a ser promovida é a primeira chave do nó raiz
        
        fseek(arqIndex,0,SEEK_SET);
        //Escreve o Cabecalho e a Raiz no arquivo binario
        EscreveCabecalhoArvore(RegCab,arqIndex);
        EscreveDadosNoArquivo(RegDados,arqIndex);
        //Libera espacos de Memoria da chave
        free(promove->nometec);
        free(promove);
        LiberaRegistro(RegDados);
        return 0;
    }
    else{ //se a arvore nao estiver vazia
        //Leitura da Raiz: 
        fseek(arqIndex,(RegCab->noRaiz+1)*(TAM_REGISTRO),SEEK_SET);
        LeituraArqIndex(RegDados,arqIndex);
        //Adiciona Recursivamente
        posicao=PosicaoNaArvore(RegDados,promove->nometec); //posicao recebe a posicao onde deve ser adicionado o novo registro
        promove=AdicionaRec(promove,posicao,RegDados,RegCab,arqIndex); //adiciona recursivamente o novo registro na arvore
        
        if(promove!=NULL){ 
            fseek(arqIndex,(RegCab->noRaiz+1)*(TAM_REGISTRO),SEEK_SET);
            LeituraArqIndex(RegDados,arqIndex);
            //Adicao na Raiz
            if(RegDados->nroChavesNo<3){//se o numero de chaves no nó raiz for menor que 3, adiciona o novo registro na raiz
                AdicionaNo(promove,RegDados,arqIndex);  //adiciona o novo registro na raiz  
            }else{
                //split raiz
                promove=Split(promove,RegDados,RegCab,arqIndex);
                //Inicializa um novo registro
                RegistroArvore *novo;
                novo=InicializaDados();
                strcpy(novo->folha.chave[0],promove->nometec);
                //Cria o Novo no Raiz
                novo->folha.P[0]=RegCab->noRaiz;//Aponta o P[0] para o no raiz antigo
                novo->folha.PR[0]=promove->PR; //Aponta o PR[0] para o PR da chave promovida
                novo->folha.P[1]=promove->Pdireita;// Aponta o P[1] para o novo no
                novo->RRNdoNo=RegCab->RRNproxNo; //RRNdoNo recebe o RRNproxNo
                novo->alturaNo=RegDados->alturaNo+1;//altura do novo no recebe a altura do no antigo +1
                //Atualiza o Registro de Cabecalho
                RegCab->noRaiz=novo->RRNdoNo; //no raiz recebe o RRNdoNo
                RegCab->RRNproxNo++;//RRNproxNo é atualizado
                //Da fseek para o RRNdoNo para escrever o novo Indice
                fseek(arqIndex,(novo->RRNdoNo+1)*TAM_REGISTRO,SEEK_SET);
                EscreveDadosNoArquivo(novo,arqIndex); //Escreve o novo no no arquivo de indice
                //FREES
                free(novo);
                free(promove->nometec);
                free(promove);
            }
        }
    }
    LiberaRegistro(RegDados);
    return 0;
}

Chave *AdicionaRec(Chave *chave,int posicao,RegistroArvore *RegDados,CabecalhoArvore *RegCab,FILE *arqIndex){ //Adiciona recursivamente um novo registro na arvore
    Chave *promove=(Chave*)malloc(sizeof(Chave)); //Inicializa a chave a ser promovida
    promove->nometec=(char*)malloc(sizeof(char)*56); //Inicializa o nome da chave a ser promovida
    
    RegistroArvore *RegDadosFilho; 
    RegDadosFilho=InicializaDados();

    if(posicao==-1){ //Se a posicao for -1, ou seja, se o nó for uma folha
        chave->Pdireita=-1; //Pdireita recebe -1
        return chave; //retorna a chave
    }

    
    fseek(arqIndex,(posicao+1)*(TAM_REGISTRO),SEEK_SET);
    LeituraArqIndex(RegDadosFilho,arqIndex); //leitura do registro de dados filho no arquivo de indice
    // Criar uma cópia de RegDados antes de chamar Split
    
    posicao=PosicaoNaArvore(RegDadosFilho,chave->nometec); //posicao recebe a posicao onde deve ser adicionado o novo registro

    promove=AdicionaRec(chave,posicao,RegDadosFilho,RegCab,arqIndex); //adiciona recursivamente o novo registro na arvore
    
    if(promove!=NULL){ //se a chave a ser promovida nao for nula
        if(RegDadosFilho->nroChavesNo<3){ //se o numero de chaves no nó for menor que 3
            AdicionaNo(promove,RegDadosFilho,arqIndex); //adiciona o novo registro no nó
            //LiberaRegistro(RegDados);
            return NULL;
        }else{
            promove=Split(promove,RegDadosFilho,RegCab,arqIndex); //split no nó se for maior que 3 chaves
            //LiberaRegistro(RegDados);
            return promove;
        }
    }else{
        return NULL;
    }        
}

Chave *Split(Chave *chave,RegistroArvore *registro,CabecalhoArvore *RegCab,FILE *arqIndex){ //split no nó se for maior que 3 chaves
    // Criar um novo RegistroArvore para o novo nó
    RegistroArvore *novo;
    novo=InicializaDados();
    if (novo==NULL) {
        printf("Erro ao alocar Memoria\n");
        return NULL;
    }
    //Inicializa a chave a ser promovida
    Chave *promove=(Chave*)malloc(sizeof(Chave));
    promove->nometec=(char*)malloc(sizeof(char)*56);
    
    //Inicializa o Vetor Chaves
    Chave *C=(Chave*)malloc(sizeof(Chave)*4);
    for(int i=0;i<4;i++){
        C[i].nometec=(char*)malloc(sizeof(char)*56);
    }
    //Coloca as 4 chaves num vetor para ser Ordenado
    for(int i=0;i<3;i++){
        strcpy(C[i].nometec,registro->folha.chave[i]); //C recebe as chaves do registro
        C[i].Pdireita=registro->folha.P[i+1]; //C recebe os P's do registro
        C[i].PR=registro->folha.PR[i]; //C recebe os PR's do registro
    }
    strcpy(C[3].nometec,chave->nometec); //C recebe a chave a ser promovida
    C[3].Pdireita=chave->Pdireita; //C recebe o Pdireita da chave a ser promovida
    C[3].PR=chave->PR; //C recebe o PR da chave a ser promovida
    
    //Ordena:
    quickSortNome(C,0,3);
    //promove=terceira
    strcpy(promove->nometec,C[2].nometec); //promove recebe a terceira chave do vetor ordenado
    promove->Pdireita=RegCab->RRNproxNo; //promove recebe o RRNproxNo
    promove->PR=C[2].PR; //promove recebe o PR da terceira chave do vetor ordenado

    //as duas primeiras ficam no registro
    strcpy(registro->folha.chave[0],C[0].nometec); //o registro recebe a primeira chave do vetor ordenado
    registro->folha.PR[0]=C[0].PR; //o registro recebe o PR da primeira chave do vetor ordenado
    registro->folha.P[1]=C[0].Pdireita; //o registro recebe o Pdireita da primeira chave do vetor ordenado
    strcpy(registro->folha.chave[1],C[1].nometec); //o registro recebe a segunda chave do vetor ordenado
    registro->folha.PR[1]=C[1].PR; //o registro recebe o PR da segunda chave do vetor ordenado
    registro->folha.P[2]=C[1].Pdireita; //o registro recebe o Pdireita da segunda chave do vetor ordenado
    registro->nroChavesNo=2; //o registro recebe o numero de chaves igual a 2
    strcpy(registro->folha.chave[2],""); //o registro recebe uma string vazia na terceira chave
    registro->folha.PR[2]=-1; //o registro recebe -1 no PR da chave pois nao tem mais terceira chave
    registro->folha.P[3]=-1; // o registro recebe -1 no P da terceira chave pois não existe mais terceira chave
    
    //a quarta fica no novo registro(RegCab->RRNproxNo) e adicionamos isso no arquivo
    strcpy(novo->folha.chave[0],C[3].nometec); //o novo registro recebe a quarta chave do vetor ordenado
    novo->folha.P[0]=C[2].Pdireita; //o novo registro P[0] recebe o Pdireita da terceira chave do vetor ordenado
    novo->alturaNo=registro->alturaNo; //o novo registro recebe a altura do registro
    novo->RRNdoNo=RegCab->RRNproxNo; //o novo registro recebe o RRNproxNo
    novo->folha.PR[0]=C[3].PR; //o novo registro recebe o PR da quarta chave do vetor ordenado
    novo->folha.P[1]=C[3].Pdireita; //o novo registro P[1]recebe o Pdireita da quarta chave do vetor ordenado
    
    if(novo->alturaNo==1){ //se a altura do novo registro for 1, ou seja, se o novo registro for uma folha
        for(int i=0;i<4;i++){
            if(novo->folha.P[i]!=-1){
                novo->folha.P[i]=-1; //o novo registro recebe -1 no P pois nao tem mais P
            }
        }
    }
    if(registro->alturaNo==1){ //se a altura do registro for 1, ou seja, se o registro for uma folha
        for(int i=0;i<4;i++){
            if(registro->folha.P[i]!=-1){
                registro->folha.P[i]=-1; //o registro recebe -1 no P pois nao tem mais P
            }
            
        }
    }       
    //Escreve os indices alterados no arquivo de dados:
    fseek(arqIndex,(novo->RRNdoNo+1)*TAM_REGISTRO,SEEK_SET);
    EscreveDadosNoArquivo(novo,arqIndex);
    
    fseek(arqIndex,(registro->RRNdoNo+1)*TAM_REGISTRO,SEEK_SET);
    EscreveDadosNoArquivo(registro,arqIndex);

    //Reescreve o cabecalho
    RegCab->RRNproxNo++;
    
    for(int i=0;i<4;i++){
        free(C[i].nometec);
    }

    free(chave->nometec);
    free(chave);
    free(C);
    //Envia a chave promovida para o no de cima
    return promove;

}
void AdicionaNo(Chave *promove,RegistroArvore *RegDados,FILE *arqIndex){
    Chave *C=(Chave*)malloc(sizeof(Chave)*3);
    
    for(int i=0;i<3;i++){
        C[i].nometec=(char*)malloc(sizeof(char)*56);
    }

    //Adiciona valores do registro de dados atual no vetor auxiliar
    for(int i=0;i<RegDados->nroChavesNo;i++){
        strcpy(C[i].nometec,RegDados->folha.chave[i]);
        C[i].Pdireita=RegDados->folha.P[i+1];
        C[i].PR=RegDados->folha.PR[i];
    }
    //Adiciona valor extra que sera adicionado
    strcpy(C[RegDados->nroChavesNo].nometec,promove->nometec);
    C[RegDados->nroChavesNo].Pdireita=promove->Pdireita;
    C[RegDados->nroChavesNo].PR=promove->PR;
    
    //Ordena vetor auxiliar
    RegDados->nroChavesNo++;
    quickSortNome(C,0,RegDados->nroChavesNo-1);
    //Organiza os dados novamente no No
    for(int i=0;i<RegDados->nroChavesNo;i++){
        //printf("ADicionaRec:%s\n",C[i].nometec);
        strcpy(RegDados->folha.chave[i],C[i].nometec);
        RegDados->folha.PR[i]=C[i].PR;
        RegDados->folha.P[i+1]=C[i].Pdireita;
    }
    //Atualiza o numero de chaves no No
    if(RegDados->alturaNo==1){
        for(int i=0;i<4;i++){
            if(RegDados->folha.P[i]!=-1){
                RegDados->folha.P[i]=-1;
            }
            
        }
    }

    //Escreve no Arquivo
    fseek(arqIndex,(RegDados->RRNdoNo+1)*TAM_REGISTRO,SEEK_SET);    
    EscreveDadosNoArquivo(RegDados,arqIndex);
    //FREES
    for(int i=0;i<3;i++){
        free(C[i].nometec);
    }
    free(C);
    free(promove->nometec);
    free(promove);
}


void quickSortNome(Chave *V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(V, inicio, fim);
        quickSortNome(V, inicio, pivo - 1); // Ordena a parte esquerda
        quickSortNome(V, pivo + 1, fim); // Ordena a parte direita
    }
}

int particiona(Chave *V, int inicio, int fim) {
    Chave pivo = V[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (strcmp(V[j].nometec, pivo.nometec) < 0) {
            i++;
            troca(&V[i], &V[j]);
        }
    }
    troca(&V[i + 1], &V[fim]);
    return (i + 1);
}

void troca(Chave *a, Chave *b) {
    Chave t = *a;
    *a = *b;
    *b = t;
}