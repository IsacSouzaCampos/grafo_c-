all: program

program: main.o grafo.o
	g++ -g3 main.o grafo.o -o program

main.o: main.cpp
	g++ -g3 -c main.cpp

grafo.o: grafo.cpp
	g++ -g3 -c grafo.cpp
