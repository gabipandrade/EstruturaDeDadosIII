#ifndef __BUSCA_H__
#define __BUSCA_H__
#include "cabeca.h"

// Função para busca binária no No
int BuscaBinNo(RegistroArvore *RegDados,char*nome);
int BuscaIndex(char *nome,FILE * arqReadIndex,FILE *arqRead);
int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido);
#endif