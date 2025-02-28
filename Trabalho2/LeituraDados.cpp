#include "LeituraDados.h"
/* Cria e aloca o Registro de cabeçalho, além de inicializar as váriavéis com 0*/
RegistroCabBIN* CriaStructCabecalho() {
    RegistroCabBIN* RegCab = new RegistroCabBIN; 
    if (RegCab == nullptr) {
        return nullptr; // Falha na alocação
    }
    RegCab->status = '0';
    RegCab->proxRRN = 0;
    RegCab->nroTecnologias = 0;
    RegCab->nroParesTecnologias = 0;
    
    return RegCab;
}
//Cria o cabeçalho do arquivo binário
void InicializaCabecalho(RegistroCabBIN *RegCab, FILE *arq) {
    fwrite(&(RegCab->status),sizeof(char),1,arq);
    fwrite(&(RegCab->proxRRN),sizeof(int),1,arq);
    fwrite(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fwrite(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);   
}
/* faz a leitura do cabeçalho do arquivo recebido usando fread*/
RegistroCabBIN *LeituraCabecalho(RegistroCabBIN*RegCab, FILE *arq){
    fread(&(RegCab->status),sizeof(char),1,arq);
    fread(&(RegCab->proxRRN),sizeof(int),1,arq);
    fread(&(RegCab->nroTecnologias),sizeof(int),1,arq);
    fread(&(RegCab->nroParesTecnologias),sizeof(int),1,arq);
    return RegCab;
}

/*Cria a struct do registro de dados alocando as variaveis e iniciando elas*/
RegistroBIN* CriaStructRegDados() {
    RegistroBIN* RegDados = new RegistroBIN;
    
    if (RegDados == nullptr) {
        return nullptr; // Falha na alocação
    }

    strcpy(RegDados->removido, "0");
    RegDados->nomeTecnologiaOrigem = new char[50];
    RegDados->nomeTecnologiaDestino = new char[50];

    return RegDados;
}
/*abre o arquivo binário para leitura*/
FILE *AbreArquivoLeituraBIN(char* arq){
    FILE *arquivo;    
    arquivo= fopen(arq,"rb");
    if(arquivo == NULL){
        cout <<"Registro inexistente." << endl;
        return NULL;
    }
    return arquivo;
}
/*Função para Leitura de Dados no qual é lido cada um dos campos do registro de dados, 
e após isso dado um fseek para a posição do tamanho do registro*/
RegistroBIN *LeituraDados(RegistroBIN *RegDados, FILE *arqConvertido){
    int tamanhoRegistro;

    fread(&(RegDados->removido),sizeof(char),1,arqConvertido);
    fread(&(RegDados->grupo),sizeof(int),1,arqConvertido);
    fread(&(RegDados->popularidade),sizeof(int),1,arqConvertido);
    fread(&(RegDados->peso),sizeof(int),1,arqConvertido);
    fread(&(RegDados->tamanhoTecnologiaOrigem),sizeof(int),1,arqConvertido);
    fread((RegDados->nomeTecnologiaOrigem),(RegDados->tamanhoTecnologiaOrigem)*sizeof(char),1,arqConvertido);
    fread(&(RegDados->tamanhoTecnologiaDestino),sizeof(int),1,arqConvertido);
    fread((RegDados->nomeTecnologiaDestino),(RegDados->tamanhoTecnologiaDestino)*sizeof(char),1,arqConvertido);

    RegDados->nomeTecnologiaOrigem[RegDados->tamanhoTecnologiaOrigem]='\0';
    RegDados->nomeTecnologiaDestino[RegDados->tamanhoTecnologiaDestino]='\0';
    
    tamanhoRegistro=76 - 21 -(RegDados->tamanhoTecnologiaOrigem+RegDados->tamanhoTecnologiaDestino);
    fseek(arqConvertido,tamanhoRegistro,SEEK_CUR);

    return RegDados;
}