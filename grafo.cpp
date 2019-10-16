#include <iostream>
#include "grafo.h"



Grafo::Grafo() = default;

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    listaVertices.push_back(Vertice(data, index));
    vertices++;
    ultimo++;
}


bool Grafo::inserirAresta(int v1, int v2) {
    for(auto& vi : listaVertices) {
        if(vi.getIndex() == v1) {
            for(auto& vj : listaVertices) {
                if(vj.getIndex() == v2) {
                    listaArestas.push_back(make_pair(vi, vj));
                    listaArestas.push_back(make_pair(vj, vi));
                    arestas++;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::deletarVertice(int index) {
    for(auto& v : listaVertices){
        if(v.getIndex() == index) {
            for(auto& a : listaArestas) {
                if(a.first == v || a.second == v)
                    listaArestas.remove(a);
            }
            listaVertices.remove(v);
            vertices--;
            return true;;
        }
    }
    return false;
}

bool Grafo::deletarAresta(int v1, int v2) {
    for(auto& a : listaArestas) {
        if(a.first.getIndex() == v1 && a.second.getIndex() == v2) {
            listaArestas.remove(make_pair(a.first, a.second));
            listaArestas.remove(make_pair(a.second, a.first));
            arestas--;
            return true;
        }
    }
    return false;
}

void Grafo::imprimirListaAdjacentes() {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    for(auto& vi : listaVertices) {
        cout << "[v" << vi.getIndex() << "]: " << flush;
        for(auto& vj : listaArestas) {
            if(vj.first == vi)
                cout << "[v" << vj.second.getIndex() << "] / " << flush;
        }
        cout << endl;
    }
}

void Grafo::imprimirVertices() {
    for(auto& v : listaVertices)
        cout << v.getData() << endl;
}

void Grafo::DFS() {
    stack<Vertice> stack;   // cria a stack
    for(auto& a : listaArestas) {   // setta todos os vertices para branco
        a.first.setColor(color::BRANCO);
        a.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());  // copia do primeiro vertice da lista
    stack.push(raiz);   // poe o vertice na stack

    while(!stack.empty()) {
        auto current = stack.top();    // cópia do vertice da stack
        for(auto& a : listaArestas) {
            if(a.first == current) {
                a.first.setColor(color::CINZA);
            } else if(a.second == current) {
                a.second.setColor(color::CINZA);
            }
        }

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first == current) {
                if(a.second.getColor() == color::BRANCO) {
                    branco = true;
                    break;
                }
            }
        }
        if(!branco) {
            current.setColor(color::PRETO);
            for(auto& a : listaArestas) {
                if(a.first == current) {
                    a.first.setColor(color::PRETO);
                } else if(a.second == current) {
                    a.second.setColor(color::PRETO);
                }
            }
            cout << current.getData() << endl;
            stack.pop();
        }
        
        for(auto& a : listaArestas) {
            if(a.first == current){
                if(a.second.getColor() == color::BRANCO) {
                    // a.second.setColor(color::CINZA);
                    stack.push(a.second);
                }
            }
        }
    }
}

void Grafo::BFS() {
    queue<Vertice> queue;
    for(auto& a : listaArestas) {
        a.first.setColor(color::BRANCO);
        a.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());
    queue.push(raiz);

    while(!queue.empty()) {
        auto current = queue.front();
        for(auto& a : listaArestas) {
            if(a.first == current) {
                a.first.setColor(color::CINZA);
            } else if(a.second == current) {
                a.second.setColor(color::CINZA);
            }
        }

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first == current) {
                if(a.second.getColor() == color::BRANCO) {
                    branco = true;
                    continue;
                }
            }
        }
        if(!branco) {
            current.setColor(color::PRETO);
            for(auto& a : listaArestas) {
                if(a.first == current) {
                    a.first.setColor(color::PRETO);
                } else if(a.second == current) {
                    a.second.setColor(color::PRETO);
                }
            }
        }
        
        for(auto& a : listaArestas) {
            if(a.first == current) {
                if(a.second.getColor() == color::BRANCO) {
                    a.second.setColor(color::CINZA);
                    queue.push(a.second);
                }
            }
        }
        queue.pop();
        cout << current.getData() << endl;
    }
}
