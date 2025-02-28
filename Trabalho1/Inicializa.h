#ifndef __INICIALIZA_H__
#define __INICIALIZA_H__

#include "cabeca.h"
CabecalhoArvore *InicializaCabecalho();
RegistroCabBIN *CriaStructCabecalho();

RegistroArvore *InicializaDados();
Chave *InicializaChave(RegistroBIN *RegBIN,int RRN);
RegistroBIN *CriaStructRegDados();
void LiberaRegistro(RegistroArvore *RegDados);
    
void lerLinha(char linha[], RegistroBIN *registro);
void LimpaRegistroDeDados(RegistroBIN *RegDados);




#endif