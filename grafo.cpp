#include <iostream>
#include "grafo.h"



Grafo::Grafo() = default;

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    listaVertices.push_back(Vertice(data, index));
    vertices++;
    ultimo++;
}


bool Grafo::inserirAresta(int v1, int v2, int peso) {
    for(auto& vi : listaVertices) {
        if(vi.getIndex() == v1) {
            for(auto& vj : listaVertices) {
                if(vj.getIndex() == v2) {
                    pair<Vertice, Vertice> p1(vi, vj);
                    pair<Vertice, Vertice> p2(vj, vi);
                    // listaArestas.push_back(p1);
                    // listaArestas.push_back(p2);
                    listaArestas.push_back(make_pair(p1, peso));
                    listaArestas.push_back(make_pair(p2, peso));
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
                if(a.first.first == v || a.first.second == v) {
                    pair<Vertice, Vertice> p1(a.first.first, a.first.second);
                    pair<Vertice, Vertice> p2(a.first.second, a.first.first);
                    listaArestas.remove(make_pair(p1, a.second));
                    listaArestas.remove(make_pair(p2, a.second));
                }
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
        if(a.first.first.getIndex() == v1 && a.first.second.getIndex() == v2) {
            pair<Vertice, Vertice> p1(a.first.first, a.first.second);
            pair<Vertice, Vertice> p2(a.first.second, a.first.first);
            listaArestas.remove(make_pair(p1, a.second));
            listaArestas.remove(make_pair(p2, a.second));
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
        for(auto& a : listaArestas) {
            if(a.first.first == vi)
                cout << "[v" << a.first.second.getIndex() << "] / " << flush;
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
        a.first.first.setColor(color::BRANCO);
        a.first.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());  // copia do primeiro vertice da lista
    stack.push(raiz);   // poe o vertice na stack

    while(!stack.empty()) {
        auto current = stack.top();    // cópia do vertice da stack
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                a.first.first.setColor(color::CINZA);
            } else if(a.first.second == current) {
                a.first.second.setColor(color::CINZA);
            }
        }

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    branco = true;
                    break;
                }
            }
        }
        if(!branco) {
            current.setColor(color::PRETO);
            for(auto& a : listaArestas) {
                if(a.first.first == current) {
                    a.first.first.setColor(color::PRETO);
                } else if(a.first.second == current) {
                    a.first.second.setColor(color::PRETO);
                }
            }
            cout << current.getData() << endl;
            stack.pop();
        }
        
        for(auto& a : listaArestas) {
            if(a.first.first == current){
                if(a.first.second.getColor() == color::BRANCO) {
                    // a.first.second.setColor(color::CINZA);
                    stack.push(a.first.second);
                }
            }
        }
    }
}

void Grafo::BFS() {
    queue<Vertice> queue;
    for(auto& a : listaArestas) {
        a.first.first.setColor(color::BRANCO);
        a.first.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());
    queue.push(raiz);

    while(!queue.empty()) {
        auto current = queue.front();
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                a.first.first.setColor(color::CINZA);
            } else if(a.first.second == current) {
                a.first.second.setColor(color::CINZA);
            }
        }

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    branco = true;
                    continue;
                }
            }
        }
        if(!branco) {
            current.setColor(color::PRETO);
            for(auto& a : listaArestas) {
                if(a.first.first == current) {
                    a.first.first.setColor(color::PRETO);
                } else if(a.first.second == current) {
                    a.first.second.setColor(color::PRETO);
                }
            }
        }
        
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    a.first.second.setColor(color::CINZA);
                    queue.push(a.first.second);
                }
            }
        }
        queue.pop();
        cout << current.getData() << endl;
    }
}

void Grafo::dijkstra() {
    int qtd_fechados = listaVertices.size();
    list<pair<Vertice, int>> dist;
    for(auto& v : listaVertices) {
        v.setColor(color::BRANCO);
        dist.push_back(make_pair(v, INT_MAX/2));
    }

    auto current = *(dist.begin());
    auto prox = *(dist.begin());
    current.first.setDistancia(0);
    current.first.setColor(color::PRETO);
    current.second = 0;
    dist.pop_front();
    dist.push_front(make_pair(current.first, 0));
    

    int menor_distancia = INT_MAX/2;
    while(qtd_fechados) {
        int distancia = current.second;
        for(auto& a : listaArestas) {
            if(a.first.first == current.first) {                                            // se first do pair = current
                for(auto& d : dist) {                                                       // atualizar lista de distancias
                    if(d.first == a.first.second && d.first.getColor() == color::BRANCO) {  // se elemento do d = vizinho do current                                          // distancia = current.get
                        d.second = distancia + a.second;                                    // atualiza distancia do vizinho em dist

                        if(d.second < menor_distancia) {
                            menor_distancia = d.second;                                    // atualiza a menor distancia
                            prox = d;                                                       // atualiza o prox vetor (menor dist)
                        }
                        break;
                    }
                }
            }
        }   // finaliza atualizacao dos vizinhosm de current
        // if(prox.first.getColor() == color::PRETO)
        //     qtd_fechados++;
        prox.first.setColor(color::PRETO);
        current = prox;
        menor_distancia = current.second;
        qtd_fechados--;
    }

    for(auto& d : dist)
        cout << d.first.getData() << " - " << d.second << endl;
}
