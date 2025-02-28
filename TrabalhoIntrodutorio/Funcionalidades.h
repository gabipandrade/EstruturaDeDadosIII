#ifndef __FUNCIONALIDADE_H__
#define __FUNCIONALIDADE_H__

#include "cabeca.h"
//Funcionalidade [1]
void createTable(char *arqCSV,char *arqBIN);
//Funcionalidade [2]
void SelectFrom(char *arqBIN);
//Funcionalidade [3]
void SelecWhere(char *arqBIN,int n);
//Funcionalidade [4]
void RecuperaDados(char *arqBIN, int RRN);

#endif