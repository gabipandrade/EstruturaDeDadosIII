all: ex4

run: ex4
	./ex4

ex4.o: main.c
	gcc -c main.c -o ex4.o

FuncoesDados.o: FuncoesDados.c
	gcc -c FuncoesDados.c -o FuncoesDados.o

Funcionalidades.o: Funcionalidades.c
	gcc -c Funcionalidades.c -o Funcionalidades.o

Funcoesfornecidas.o:  Funcoesfornecidas.c
	gcc -c Funcoesfornecidas.c -o Funcoesfornecidas.o

FuncoesCabecalho.o: FuncoesCabecalho.c
	gcc -c FuncoesCabecalho.c -o FuncoesCabecalho.o

AberturaArquivo.o: AberturaArquivo.c
	gcc -c AberturaArquivo.c -o AberturaArquivo.o

ex4: ex4.o FuncoesDados.o Funcoesfornecidas.o Funcionalidades.o FuncoesCabecalho.o AberturaArquivo.o
	gcc -o ex4 ex4.o FuncoesDados.o Funcoesfornecidas.o Funcionalidades.o FuncoesCabecalho.o AberturaArquivo.o

clean:
	rm ex4 ex4.o FuncoesDados.o Funcoesfornecidas.o Funcionalidades.o FuncoesCabecalho.o AberturaArquivo.o