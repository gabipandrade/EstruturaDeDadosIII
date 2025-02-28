
#ifndef __ESCRITAARQUIVOS_H__
#define __ESCRITAARQUIVOS_H__

#include "cabeca.h"

FILE *AbreArquivoEscritaBIN(char *arq);
int EscreveDadosNoArquivo(RegistroArvore *RegDados,FILE*arq);
void EscrevePalavras(char *string,FILE *arq,int tamanho);
int EscreveDadosNoBIN(RegistroBIN *RegDados,FILE *arqConvertido);
int EscreveCabecalhoArvore(CabecalhoArvore*RegCab,FILE*arq);
void Insert_Into(FILE*arqRead,FILE*arqReadIndice,int n);

#endif