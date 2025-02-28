#include "FuncoesCabecalho.h"
#include "cabeca.h"
#include "AberturaArquivo.h"
#include "FuncoesDados.h"
#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"

// Gabriela Passos de Andrade-12625142
// Rafael Cunha Bejes Learth-13676367 

int main(){
    int escolha;
    int RRN;
    int n;
    char arqCSV[20];
    char arqBIN[20];
    scanf("%d",&escolha);
    switch(escolha){
        case 1:
        scanf("%s",arqCSV);
        scanf("%s",arqBIN);
        createTable(arqCSV,arqBIN);
        break;
        case 2:
        scanf("%s",arqBIN);
        SelectFrom(arqBIN);
        break;
        case 3:
        scanf("%s",arqBIN);
        scanf("%d",&n);
        SelecWhere(arqBIN,n);
        break;
        case 4:
        scanf("%s",arqBIN);
        scanf("%d",&RRN);
        RecuperaDados(arqBIN,RRN);
        break;
    }
}
