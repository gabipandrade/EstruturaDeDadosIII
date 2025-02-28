#ifndef __FUNCOESCABACALHO_H__
#define __FUNCOESCABECALHO_H__
#include "cabeca.h"

RegistroCabecalho *CriaStructCabecalho();
void InicializaCabecalho(RegistroCabecalho *RegCab, FILE *arq);
RegistroCabecalho *LeituraCabecalho(RegistroCabecalho*RegCab, FILE *arq);
void ContadorTecnologias(RegistroCabecalho *RegCab,char ***Origem,char ***Destino,char *tecOrigem,char *tecDestino,int *n);
#endif