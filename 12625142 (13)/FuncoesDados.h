#ifndef __FUNCOESDADOS_H__
#define __FUNCOESDADOS_H__
#include "cabeca.h"

RegistroDeDados *CriaStructRegDados();
void LimpaRegistroDeDados(RegistroDeDados *RegDados);
void PrintarDadosRegistro(RegistroDeDados *RegDados);
RegistroDeDados *LeituraDados(RegistroDeDados *RegDados, FILE *arqConvertido);
int BuscaWhere(int escolha,int valor,char *nome,FILE *arqConvertido);
void EscrevePalavras(char *string,FILE *arq,int tamanho);
int EscreveNoArquivo(RegistroDeDados *RegDados,RegistroCabecalho*RegCab,char *p,FILE *arqOriginal,FILE *arqConvertido,int *RRN);
#endif