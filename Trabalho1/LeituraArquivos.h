
#ifndef __LEITURAARQUIVOS_H__
#define __LEITURAARQUIVOS_H__
#include "cabeca.h"

FILE *AbreArquivoLeituraBIN(char *arq);
FILE *AbreArquivoLeituraEscritaBIN(char *arq);
void InicializaCabecalhoBIN(RegistroCabBIN *RegCab, FILE *arq);
RegistroCabBIN *LeituraCabecalhoBIN(RegistroCabBIN*RegCab, FILE *arq);
CabecalhoArvore *LeituraCabecalho(CabecalhoArvore *RegCab, FILE *arq);
void LeituraDadosIndice(FILE *arqBIN);
void LeituraDadosParaAdicao(FILE *arqBIN,FILE *arqWrite);
RegistroBIN* LerBIN(RegistroBIN *RegDados, FILE *arq);
int LeituraArqIndex(RegistroArvore *RegDados,FILE *arq);
void LerArquivoBinarioParaContagemTecnologias(char***Origem,char***Destino,RegistroCabBIN *RegCab,int *n,FILE *arq);
void ContadorTecnologias(RegistroCabBIN *RegCab,char ***Origem,char ***Destino,char *tecOrigem,char *tecDestino,int *n);
        
#endif