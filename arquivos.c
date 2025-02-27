#include <stdio.h>
#include <stdlib.h>
int main(){
    //fseek ajusta o ponteiro para a posição offset a partir da origem
    //fseek(arquivoinicial, 0, SEEK_SET); ir para inicio arquivo
    //fseek(arquivoinicial, 0, SEEK_END); ir para fim arquivo
    //ftell(arquivoinicial); retorna a posição atual do ponteiro
    //fwrite(&pessoa, sizeof(Pessoa), 1, arquivoinicial);faz a escrita de sizeof*número bytes que estão salvos em buffer.
    //int vetor[10];
    //fwrite(vetor, sizeof(int), 10, arquivoinicial); exemplo monitor
    //fread(&pessoa, sizeof(Pessoa), 1, arquivoinicial);
    //não usar feof
    //fclose(arquivoinicial), fecha o arquivo
    //outras funções fgetc, fputc, fgets, fputs, fprintf, fscanf, rewind, remove, rename,ferror,tmpfile,fflush.
    //não usar fread e fwrite na struct no disco, solução escrever campo a campo
    //hexdump -Cv arquivo.bin, mostra o conteúdo do arquivo em hexadecimal
    //valgrind conferir memoria, compile com a flag -g gcc -g arquivos.c -o executavel
    //valgrind ./executavel
    //valgrind --leak-check=full --show-leak-kinds=all ./executavel
    return 0;
}
