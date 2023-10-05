all: ex4

run: ex4
	./ex4

ex4.o: main.c
	gcc -c main.c -o ex4.o

funcoes.o: funcoes.c
	gcc -c funcoes.c -o funcoes.o

ex4: ex4.o funcoes.o
	gcc -o ex4 ex4.o funcoes.o

clean:
	rm ex4 ex4.o funcoes.o