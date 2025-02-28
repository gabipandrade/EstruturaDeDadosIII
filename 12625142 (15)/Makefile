FLAG := #-g -Wall -fsanitize=address

all: ex4

run: ex4
	./ex4

ex4: main.o LeituraDados.o Funcionalidades.o Funcoesfornecidas.o Grafo.o
	g++ $(FLAG) main.o LeituraDados.o Funcionalidades.o Funcoesfornecidas.o Grafo.o -o ex4

main.o: main.cpp 
	g++ $(FLAG) -c main.cpp -o main.o

LeituraDados.o: LeituraDados.cpp 
	g++ $(FLAG) -c LeituraDados.cpp -o LeituraDados.o

Funcionalidades.o: Funcionalidades.cpp 
	g++ $(FLAG) -c Funcionalidades.cpp -o Funcionalidades.o

Funcoesfornecidas.o: Funcoesfornecidas.cpp
	g++ $(FLAG) -c Funcoesfornecidas.cpp -o Funcoesfornecidas.o

Grafo.o:	Grafo.cpp
	g++ $(FLAG) -c Grafo.cpp -o Grafo.o

clean:
	rm -f ex4 *.o
zip:
	rm -f ZED3.zip
	zip ZED3.zip *.cpp *.h Makefile
