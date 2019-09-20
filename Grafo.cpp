#include <iostream>
#include <limits.h>
// #include "Grafo.h"
#include "linked_list.cpp"

using namespace std;


class Grafo {
 private:
    class Vertice {
     public:
        structures::LinkedList<Vertice*> listaArestas;

        Vertice(int data, int index) {
            data_ = data;
            index_ = index;
        }
        int getData() const{ return data_; }
        int getIndex() const { return index_; }
        void imprimirAdjacentes() {

        }

     private:
        int data_;
        int index_;
    };

 public:
    Grafo();
    structures::LinkedList<Vertice*> listaVertices;
    void inserirVertice(int data);
    void inserirAresta(Grafo::Vertice* v1, Grafo::Vertice* v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    int vertices{0};
    int arestas{0};
};

Grafo::Grafo() {}

void Grafo::inserirVertice(int data) {
    int index = vertices;
    Vertice *v = new Vertice(data, index);
    listaVertices.push_back(v);
    vertices++;
}


void Grafo::inserirAresta(Grafo::Vertice* v1, Grafo::Vertice* v2) {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    v1->listaArestas.push_back(v2);
}

void Grafo::imprimirListaAdjacentes() {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    for(int i = 0; i < vertices; i++) {
        cout << "[v" << i << "]: " << flush;
        for(int j = 0; j < listaVertices.at(i)->listaArestas.size(); j++) {
            cout << "[v" << listaVertices.at(i)->listaArestas.at(j)->getIndex() << "] / " << flush;
        }
        cout << endl;
    }
}

void Grafo::imprimirVertices() {
    for(int i = 0; i < vertices; i++) {
        cout << listaVertices.at(i)->getData() << endl;
    }
}

