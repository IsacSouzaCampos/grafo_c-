#include <iostream>
#include <limits.h>
// #include "Grafo.h"
#include "linked_list.cpp"

using namespace std;


class Grafo {
 private:
    class Vertice {
        structures::LinkedList<const Vertice*> listaArestas;

     public:
        Vertice(int data) {
            data_ = data;
        }

        int getData() const{
            return data_;
        }

     private:
        int data_;
    };

 public:
    Grafo();
    void inserirVertice(int data);
    void inserirAresta(Vertice v1, Vertice v2);
    void imprimeVertices();
    void imprimeListaArestas();
    structures::LinkedList<const Vertice*> listaVertices;
    int vertices{0};
    int arestas{0};
};

Grafo::Grafo() {}

void Grafo::inserirVertice(int data) {
    Vertice *v = new Vertice(data);
    listaVertices.push_back(v);
    vertices++;
}


// void Grafo::inserirAresta(Grafo::Vertice v1, Grafo::Vertice v2) {

// }

void Grafo::imprimeVertices() {
    for(int i = 0; i < vertices; i++) {
        cout << listaVertices.at(i)->getData() << endl;
    }
}

