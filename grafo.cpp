#include <iostream>
#include "grafo.h"



Grafo::Grafo() = default;

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    lista_vertices.push_back(Vertice(data, index));
    Vertice v = Vertice(data, index);
    map_lista_adj[v];
    map_cor[v] = color::BRANCO;
    map_distancia[v] = 0;
    vertices++;
    ultimo++;
}


bool Grafo::inserirAresta(int v1, int v2, int peso) {
    for(auto& vi : lista_vertices) {
        if(vi.getIndex() == v1) {
            for(auto& vj : lista_vertices) {
                if(vj.getIndex() == v2) {
                    pair<Vertice, Vertice> p1(vi, vj);
                    lista_arestas.push_back(make_pair(p1, peso));
                    map_lista_adj[vi].push_back(vj);
                    map_peso[make_pair(vi, vj)] = peso;
                    arestas++;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::deletarVertice(int index) {
    for(auto& v : lista_vertices){
        if(v.getIndex() == index) {
            for(auto& a : lista_arestas) {
                if(a.first.first == v || a.first.second == v) {
                    pair<Vertice, Vertice> p1(a.first.first, a.first.second);
                    lista_arestas.remove(make_pair(p1, a.second));
                }
            }
            lista_vertices.remove(v);
            vertices--;
            return true;;
        }
    }
    return false;
}

bool Grafo::deletarAresta(int v1, int v2) {
    for(auto& a : lista_arestas) {
        if(a.first.first.getIndex() == v1 && a.first.second.getIndex() == v2) {
            pair<Vertice, Vertice> p1(a.first.first, a.first.second);
            lista_arestas.remove(make_pair(p1, a.second));
            arestas--;
            return true;
        }
    }
    return false;
}

void Grafo::imprimirListaAdjacentes() {
    if(lista_vertices.empty())
        throw out_of_range("lista vazia!");
    for(auto& vi : lista_vertices) {
        cout << "[v" << vi.getIndex() << "]: " << flush;
        for(auto& a : lista_arestas) {
            if(a.first.first == vi)
                cout << "[v" << a.first.second.getIndex() << "] / " << flush;
        }
        cout << endl;
    }
}

void Grafo::imprimirVertices() {
    for(auto& v : lista_vertices)
        cout << v.getData() << endl;
}

void Grafo::DFS() {
    stack<Vertice> stack;   // cria a stack
    for(auto& mc : map_cor)   // setta todos os vertices para branco
        mc.second = color::BRANCO;

    auto raiz = *(map_lista_adj.begin());  // copia do primeiro vertice da lista
    stack.push(raiz.first);   // poe o vertice na stack

    while(!stack.empty()) {
        auto current = stack.top();    // cópia do vertice da stack
        // atualizarCorLista(current, color::CINZA);
        map_cor[current] = color::CINZA;

        bool branco = false;
        for(auto& la : map_lista_adj[current]) {
            if(map_cor[la] == color::BRANCO) {
                branco = true;
                break;
            }
        }
        if(!branco) {
            // atualizarCorLista(current, color::PRETO);
            map_cor[current] = color::PRETO;
            cout << current.getData() << endl;
            stack.pop();
        }
        
        for(auto& la : map_lista_adj[current]) {
            if(map_cor[la] == color::BRANCO) {
                // atualizarCorLista(a.first.second, color::CINZA);
                map_cor[la] = color::CINZA;
                stack.push(la);
            }
        }
    }
}

void Grafo::BFS() {
    queue<Vertice> queue;
    for(auto& mc : map_cor)
        mc.second = color::BRANCO;

    auto raiz = *(map_lista_adj.begin());
    queue.push(raiz.first);

    while(!queue.empty()) {
        auto current = queue.front();
        // atualizarCorLista(current, color::PRETO);
        map_cor[current] = color::PRETO;

        bool branco = false;
        for(auto& la : map_lista_adj[current]) {
            if(map_cor[la] == color::BRANCO) {
                branco = true;
                break;
            }
        }
        if(!branco)
            map_cor[current] = color::PRETO;
            // atualizarCorLista(current, color::PRETO);
        
        for(auto& la : map_lista_adj[current]) {
            if(map_cor[la] == color::BRANCO) {
                map_cor[la] = color::CINZA;
                queue.push(la);
            }
        }
        queue.pop();
        cout << current.getData() << endl;
    }
}

map<int, int> Grafo::dijkstra() {
    // int qtd_fechados = lista_vertices.size();
    map<int, int> caminhos; // pair<atual, anterior>
    typedef pair<int, Vertice> p;
    priority_queue<p, vector<p>, greater<p>> dist;
    for(auto& v : lista_vertices) {
        v.setColor(color::BRANCO);
        map_cor[v] = color::BRANCO;
        v.setDistancia(INT_MAX/2);
        map_distancia[v] = INT_MAX/2;
        caminhos[v.getIndex()] = v.getIndex();
    }

    auto& temp = *(lista_vertices.begin());
    temp.setDistancia(0);
    map_distancia[temp] = 0;
    auto current = *(lista_vertices.begin());
    current.setColor(color::PRETO);
    map_cor[current] = color::PRETO;
    current.setDistancia(0);
    map_distancia[current] = 0;
    dist.push(make_pair(0, current));

    // while(!dist.empty()) {
    //     dist.pop();
    //     for(auto& a : lista_arestas) {
    //         if(a.first.first == current) {
    //             for(auto& v : lista_vertices) {
    //                 if(v == a.first.second && v.getDistancia() > current.getDistancia() + a.second) {
    //                     v.setDistancia(current.getDistancia() + a.second);
    //                     dist.push(make_pair(v.getDistancia(), v));
    //                     for(auto& c : caminhos) {
    //                         if(c.first == v.getIndex())
    //                             c.second = current.getIndex();
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     current = dist.top().second;
    // }
    while(!dist.empty()) {
        dist.pop();
        for(auto& la : map_lista_adj[current]) {
            if(map_distancia[la] > map_distancia[current] + map_peso[make_pair(current, la)]) {
                map_distancia[la] = map_distancia[current] + map_peso[make_pair(current, la)];
                dist.push(make_pair(map_distancia[la], la));
                for(auto& c : caminhos) {
                    if(c.first == la.getIndex())
                        c.second = current.getIndex();
                }
            }
        }
        current = dist.top().second;
    }
    return caminhos;
}

void Grafo::maze(int index1, int index2) {
    Vertice v1, v2;
    for(auto& v : lista_vertices) {
        if(v.getIndex() == index1) {
            v1 = v;
        } else if(v.getIndex() == index2) {
            v2 = v;
        }
    }


}

void Grafo::atualizarCorLista(Vertice& v, color cor) {
    for(auto& a : lista_arestas) {
        if(a.first.first == v) {
            a.first.first.setColor(cor);
        } else if(a.first.second == v) {
            a.first.second.setColor(cor);
        }
    }
}

void Grafo::imprimirCaminho(int index1, int index2, map<int, int> caminhos) {
    stack<int> stack;

    int current = index2;
    stack.push(current);
    while(current != index1) {
        for(auto& c : caminhos) {
            if(c.first == current) {
                stack.push(c.second);
                current = c.second;
                break;
            }
        }
    }

    cout << stack.top();
    stack.pop();
    while(!stack.empty()) {
        cout << " -> " << stack.top();
        stack.pop();
    }
}
