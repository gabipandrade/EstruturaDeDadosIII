#ifndef __ARVORE_H__
#define __ARVORE_H__
#include "cabeca.h"

int PosicaoNaArvore(RegistroArvore *RegDados,char *nome);
int AdicionaNaArvore(RegistroBIN *RegBIN,RegistroCabBIN *RegCabBIN,FILE *arqIndex,CabecalhoArvore *RegCab,int RRN);
Chave *AdicionaRec(Chave *chave,int posicao,RegistroArvore *RegDados,CabecalhoArvore *RegCab,FILE *arqIndex);
Chave *Split(Chave *chave,RegistroArvore *registro,CabecalhoArvore *RegCab,FILE *arqIndex);
void AdicionaNo(Chave *promove,RegistroArvore *RegDados,FILE *arqIndex);
void quickSortNome(Chave *V, int inicio, int fim) ;
int particiona(Chave *V, int inicio, int fim);
void troca(Chave *a, Chave *b);

#endif