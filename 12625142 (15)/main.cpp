#include "Funcoesfornecidas.h"
#include "Grafo.h"
#include "Funcionalidades.h"
#include "LeituraDados.h"
//Gabriela Passos de Andrade-12625142
//Rafael Cunha Bejes Learth-13676367
int main() {
    int opcao;
    char *arquivo = new char[40];
    cin >> opcao;
    switch (opcao) {
        case 8:
            cin >>arquivo;
            Funcionalidade8(arquivo); //Funcionalidade 8
            break;
        case 9:
            cin >>arquivo;
            Funcionalidade9(arquivo);//Funcionalidade 9
            break;
        case 10:
            cin >>arquivo;
            Funcionalidade10(arquivo);//Funcionalidade 10
            break;
        case 11:
            cin >>arquivo;
            Funcionalidade11(arquivo);//Funcionalidade 11
            break;
        case 12:
            cin >>arquivo;
            Funcionalidade12(arquivo);//Funcionalidade 12
            break;
        default:
            break;
    }

    
    return 0;
}
