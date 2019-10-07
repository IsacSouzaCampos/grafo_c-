#include <iostream>
#include <unordered_map>
#define BRANCO 0
#define AMARELO 1

#include "grafo.h"


Grafo::Grafo() {}

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    Vertice v = Vertice(data, index);
    listaVertices.push_back(v);
    vertices++;
    ultimo++;
}


bool Grafo::inserirAresta(int v1, int v2) {
    for(Vertice& vi : listaVertices) {
        if(vi.getIndex() == v1) {
            for(Vertice& vj : listaVertices) {
                if(vj.getIndex() == v2) {
                    vi.listaVizinhos.push_back(vj);
                    vj.listaVizinhos.push_back(vi);
                    // cout << vi.listaArestas.size() << endl;
                    // cout << vj.listaArestas.size() << endl;
                    arestas++;
                    return true;
                }
            }
        }
    }
    return false;
}


// bool Grafo::inserirAresta(int v1, int v2) {
//     for(auto vi = listaVertices.begin(); vi != listaVertices.end(); ++vi) {
//         if((*vi).getIndex() == v1) {
//             for(auto vj = listaVertices.begin(); vj != listaVertices.end(); ++vj) {
//                 if((*vj).getIndex() == v2) {
//                     (*vi).listaVizinhos.push_back(*vj);
//                     (*vj).listaVizinhos.push_back(*vi);
//                     cout << (*vi).listaVizinhos.size() << endl;
//                     cout << (*vj).listaVizinhos.size() << endl;
//                     arestas++;
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }



bool Grafo::deletarVertice(int index) {
    for(Vertice v : listaVertices){
         if(v.getIndex() == index) {
            listaVertices.remove(v);
            vertices--;
            return true;;
         }
    }
    return false;
}

bool Grafo::deletarAresta(int v1, int v2) {
    for(Vertice vi : listaVertices) {
        if(vi.getIndex() == v1) {
            for(Vertice vj : vi.listaVizinhos) {
                if(vj.getIndex() == v2) {
                    vi.listaVizinhos.remove(vj);
                    vj.listaVizinhos.remove(vi);
                    arestas--;
                    return true;
                }
            }
        }
    }
    return false;
}

void Grafo::imprimirListaAdjacentes() {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    for(Vertice vi : listaVertices) {
        cout << "[v" << vi.getIndex() << "]: " << flush;
        // cout << vi.listaVizinhos.size() << endl;
        for(Vertice vj : vi.listaVizinhos) {
            cout << "[v" << vj.getIndex() << "] / " << flush;
        }
        cout << endl;
    }
}

void Grafo::imprimirVertices() {
    for(Vertice v : listaVertices)
        cout << v.getData() << endl;
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
