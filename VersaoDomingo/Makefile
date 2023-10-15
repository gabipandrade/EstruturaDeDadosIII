all: ex4

run: ex4
	./ex4

ex4.o: main.c
	gcc -c main.c -o ex4.o

funcoes.o: funcoes.c
	gcc -c funcoes.c -o funcoes.o

Funcionalidades.o: Funcionalidades.c
	gcc -c Funcionalidades.c -o Funcionalidades.o

Funcoesfornecidas.o:  Funcoesfornecidas.c
	gcc -c Funcoesfornecidas.c -o Funcoesfornecidas.o

ex4: ex4.o funcoes.o Funcoesfornecidas.o Funcionalidades.o
	gcc -o ex4 ex4.o funcoes.o Funcoesfornecidas.o Funcionalidades.o

clean:
	rm ex4 ex4.o funcoes.o Funcoesfornecidas.o Funcionalidades.o