#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabeca.h"

int main(){
    int escolha;
    int RRN;
    char arqCSV[20];
    char arqBIN[20];
    scanf("%d",&escolha);
    //printf("escolha feita foi:%d\n",escolha); //REMOVER NO FUTURO
    switch(escolha){
        case 1:
        printf("Caso1\n"); //REMOVER NO FUTURO
        scanf("%s",arqCSV);
        scanf("%s",arqBIN);
        createTable(arqCSV,arqBIN);
        break;
        case 2:
        printf("Caso2\n"); //REMOVER NO FUTURO
        scanf("%s",arqBIN);
        SelectFrom(arqBIN);
        break;
        case 3:
        printf("Caso3\n"); //REMOVER NO FUTURO
        break;
        case 4:
        printf("Caso4\n"); //REMOVER NO FUTURO
        scanf("%s",arqBIN);
        scanf("%d",&RRN);
        RecuperaDados(arqBIN,RRN);
        break;
    }
}
