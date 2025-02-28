#ifndef __EXIBEDADOS_H__
#define __EXIBEDADOS_H__

#include "Funcionalidades.h"
#include "Funcoesfornecidas.h"
#include "Busca.h"
#include "EscritaArquivos.h"
#include "Inicializa.h"
#include "LeituraArquivos.h"

void SelecWhere(FILE *arqRead,FILE *arqReadIndex,int n);
void PrintarDadosRegistro(RegistroBIN *RegDados);
void RecuperaDados(FILE *arqConvertido, int RRN);

#endif