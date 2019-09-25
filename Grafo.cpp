#include <iostream>
#include <limits.h>
#include <unordered_map>
#include "linked_list.cpp"
#define BRANCO 0
#define AMARELO 1

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

     private:
        int data_;
        int index_;
    };

 public:
    Grafo();
    structures::LinkedList<Vertice*> listaVertices;
    void inserirVertice(int data);
    void inserirAresta(Grafo::Vertice* v1, Grafo::Vertice* v2);
    void deletarVertice(int index);
    void deletarAresta(int v1, int v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    void DFS(int data);
    int existe(int data);
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};

Grafo::Grafo() {}

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    Vertice *v = new Vertice(data, index);
    listaVertices.push_back(v);
    vertices++;
    ultimo++;
}


void Grafo::inserirAresta(Grafo::Vertice* v1, Grafo::Vertice* v2) {
    if(v1 == NULL || v2 == NULL)
        throw out_of_range("erro!");
    v1->listaArestas.push_back(v2);
    v2->listaArestas.push_back(v1);
    arestas++;
}

void Grafo::deletarVertice(int index) {
    int i = 0;
    while(i < listaVertices.at(index)->listaArestas.size()) {
        int j = listaVertices.at(index)->listaArestas.at(i)->getIndex();
        deletarAresta(j, index);
        i++;
    }
    listaVertices.remove(listaVertices.at(index));
    vertices--;
}

void Grafo::deletarAresta(int v1, int v2) {
    for(int i = 0; i < vertices; i++) {
        if(listaVertices.at(i)->getIndex() == v1) {
            for(int j = 0; j < listaVertices.at(i)->listaArestas.size(); j++) {
                if(listaVertices.at(i)->listaArestas.at(j)->getIndex() == v2) {
                    listaVertices.at(i)->listaArestas.remove(listaVertices.at(i)->listaArestas.at(j));
                }
            }
        }
    }
    arestas--;
}

void Grafo::imprimirListaAdjacentes() {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    for(int i = 0; i < vertices; i++) {
        cout << "[v" << listaVertices.at(i)->getIndex() << "]: " << flush;
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

// int Grafo::DFS(int data) {
//     bool temp = false;
//     unordered_map<Vertice*, int> hm;
//     // Vertice *v = listaVertices.at(0);
//     for(int i = 0; i < vertices; i++)
//         hm[listaVertices.at(i)] = BRANCO;
//     for(int i = 0; i < vertices; i++) {
//         if(cor[i] == BRANCO)
//             temp = existe(data);
//     }
//     return -1;
// }

// int Grafo::existe(int data) {
//     bool temp = false;

//     while()
//     return -1;
// }
