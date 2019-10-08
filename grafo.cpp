#include <iostream>
#define BRANCO 0
#define AMARELO 1
#define VERMEHO 2

#include "grafo.h"


Grafo::Grafo() = default;

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

bool Grafo::deletarVertice(int index) {
    for(Vertice& v : listaVertices){
         if(v.getIndex() == index) {
            listaVertices.remove(v);
            vertices--;
            return true;;
         }
    }
    return false;
}

bool Grafo::deletarAresta(int v1, int v2) {
    for(Vertice& vi : listaVertices) {
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

int Grafo::DFS() {
    stack<Vertice> stack;
    int index = -1;
    for(Vertice& v : listaVertices)
        v.setVisited(false);
    auto& raiz = *(listaVertices.begin());
    
    stack.push(raiz);

    while(!stack.empty()) {
        auto top = stack.top();
        stack.pop();
        // std::cout << top.getData() << std::endl;
        for(auto& v : top.listaVizinhos) {
            if(!v.isVisited()) {
                v.setVisited(true);
                int temp = top.getAltura() + 1;
                v.setAltura(temp);
                cout << v.getAltura() << endl;
                stack.push(v);
            }
        }
        
    }

    // for(Vertice& v : listaVertices) {
    //     if(!(v.isVisited()))
    //         index = existe(v, sck, data, index);
    //     if(index > -1)
    //         break;
    // }
    return 1;
}

// int Grafo::existe(Vertice& v, stack<Vertice&>& sck, int data, int index) {
//     // v.setVisited(true);
//     // sck.push(v);
//     // for(Vertice& ver : v.listaVizinhos) {
//     //     if(ver.getData() == data)
//     //         return ver.getIndex();
//     // }
//     return -1;
// }
