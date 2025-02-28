#ifndef __LEITURA_H__
#define __LEITURA_H__
#include "cabeca.h"
//Cabecalho de dados
RegistroCabBIN *CriaStructCabecalho();
void InicializaCabecalho(RegistroCabBIN *RegCab, FILE *arq);
RegistroCabBIN *LeituraCabecalho(RegistroCabBIN*RegCab, FILE *arq);
//Registro de dados
RegistroBIN *CriaStructRegDados();
RegistroBIN *LeituraDados(RegistroBIN *RegDados, FILE *arqConvertido);
//Escrita
int EscreveNoArquivo(RegistroBIN *RegDados,RegistroCabBIN*RegCab,char *p,FILE *arqOriginal,FILE *arqConvertido,int *RRN);
RegistroBIN *LeituraDados(RegistroBIN *RegDados, FILE *arqConvertido);
//Abertura de arquivo
FILE *AbreArquivoLeituraBIN(char *arq);
bool compararStrings(const char* a, const char* b);

#endif