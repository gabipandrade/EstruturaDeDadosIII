#include "cabeca.h"
#include "Funcionalidades.h"

//Rafael Cunha Bejes Learth 13676367
//Gabriela Passos de Andrade 12625142
int main(){
    int escolha;
    int n;
    char arqBIN1[20];
    char arqBIN2[20];
    scanf("%d",&escolha);
    switch(escolha){
        case 5:
        scanf("%s",arqBIN1);
        scanf("%s",arqBIN2);
        Funcionalidade5(arqBIN1,arqBIN2);
        break;
        case 6:
        scanf("%s",arqBIN1);
        scanf("%s",arqBIN2);
        scanf("%d",&n);
        Funcionalidade6(arqBIN1,arqBIN2,n);
        break;
        case 7:
        scanf("%s",arqBIN1);
        scanf("%s",arqBIN2);
        scanf("%d",&n);
        Funcionalidade7(arqBIN1,arqBIN2,n);
        break;
    }

}


