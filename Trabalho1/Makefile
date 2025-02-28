FLAG := #-g -Wall -fsanitize=address

all: ex4

run: ex4
	./ex4

ex4.o: main.c
	gcc $(FLAG) -c main.c -o ex4.o

Arvore.o: Arvore.c
	gcc $(FLAG) -c Arvore.c -o Arvore.o

LeituraArquivos.o: LeituraArquivos.c
	gcc $(FLAG) -c LeituraArquivos.c -o LeituraArquivos.o

Funcionalidades.o: Funcionalidades.c
	gcc $(FLAG) -c Funcionalidades.c -o Funcionalidades.o

Funcoesfornecidas.o: Funcoesfornecidas.c
	gcc $(FLAG) -c Funcoesfornecidas.c -o Funcoesfornecidas.o

Inicializa.o: Inicializa.c
	gcc $(FLAG) -c Inicializa.c -o Inicializa.o

Busca.o: Busca.c
	gcc $(FLAG) -c Busca.c -o Busca.o

EscritaArquivos.o: EscritaArquivos.c
	gcc $(FLAG) -c EscritaArquivos.c -o EscritaArquivos.o

ExibeDados.o: ExibeDados.c
	gcc $(FLAG) -c ExibeDados.c -o ExibeDados.o

ex4: ex4.o Arvore.o LeituraArquivos.o Funcionalidades.o Inicializa.o Funcoesfornecidas.o Busca.o EscritaArquivos.o ExibeDados.o
	gcc $(FLAG) -o ex4 ex4.o Arvore.o LeituraArquivos.o Funcionalidades.o Inicializa.o Funcoesfornecidas.o Busca.o EscritaArquivos.o ExibeDados.o

clean:
	rm ex4 ex4.o Arvore.o LeituraArquivos.o Funcionalidades.o Inicializa.o Funcoesfornecidas.o Busca.o EscritaArquivos.o ExibeDados.o
