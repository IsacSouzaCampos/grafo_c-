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
    cout << data << endl;
}

bool Grafo::inserirAresta(int v1, int v2, int peso) {
    Vertice vi, vj;
    int cont = 0;

    for(auto& v : lista_vertices) {
        int index = v.getIndex();
        if(v1 == index) {
            vi = v;
            cont++;
            if(cont == 2) {
                pair<Vertice, Vertice> p1(vi, vj);
                lista_arestas.push_back(make_pair(p1, peso));
                map_lista_adj[vi].push_back(vj);
                map_peso[make_pair(vi, vj)] = peso;
                arestas++;
                cout << "aresta(" << v1 << ", " << v2 << ")" << endl;
                return true;
            }
        } else if(v2 == index) {
            vj = v;
            cont++;
            if(cont == 2) {
                pair<Vertice, Vertice> p1(vi, vj);
                lista_arestas.push_back(make_pair(p1, peso));
                map_lista_adj[vi].push_back(vj);
                map_peso[make_pair(vi, vj)] = peso;
                arestas++;
                cout << "aresta(" << v1 << ", " << v2 << ")" << endl;
                return true;
            }
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

bool Grafo::BFS(Vertice v1,Vertice v2) {
    queue<Vertice> queue;
    for(auto& mc : map_cor) {
        if(mc.second == color::CINZA)
            mc.second = color::BRANCO;
    }
    for(auto& md : map_distancia)
        md.second = 0;

    auto raiz = v1;
    queue.push(raiz);
    
    map_cor[raiz] = color::CINZA;
    while(!queue.empty()) {
        auto current = queue.front();

        // bool branco = false;
        // for(auto& la : map_lista_adj[current]) {
        //     if(map_cor[la] == color::BRANCO) {
        //         branco = true;
        //         break;
        //     }
        // }
        // if(!branco)
        //     map_cor[current] = color::PRETO;
        
        for(auto& la : map_lista_adj[current]) {
            if(la == v2) {
                map_distancia[la] = map_distancia[current] + 1;
                return true;
            }
            if(map_cor[la] == color::BRANCO) {
                map_distancia[la] = map_distancia[current] + 1;
                map_cor[la] = color::CINZA;
                queue.push(la);
            }
        }
        queue.pop();
        // cout << current.getData() << endl;
    }
    return false;
}

map<int, int> Grafo::dijkstra() {
    // int qtd_fechados = lista_vertices.size();
    map<int, int> caminhos; // pair<atual, anterior>
    typedef pair<int, Vertice> p;
    priority_queue<p, vector<p>, greater<p>> dist;
    for(auto& v : lista_vertices) {
        map_cor[v] = color::BRANCO;
        map_distancia[v] = INT_MAX/2;
        caminhos[v.getIndex()] = v.getIndex();
    }

    auto& temp = *(lista_vertices.begin());
    map_distancia[temp] = 0;
    auto current = *(lista_vertices.begin());
    map_cor[current] = color::PRETO;
    map_distancia[current] = 0;
    dist.push(make_pair(0, current));
    
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

string Grafo::maze(int index1, int index2) {
    Vertice v1, v2;
    int distancia;
    for(auto& v : lista_vertices) {
        if(v.getIndex() == index1) {
            v1 = v;
        } else if(v.getIndex() == index2) {
            v2 = v;
        }
    }
    if(BFS(v1, v2))
        return path(v1, v2);
    return "erro";
}

string Grafo::path(Vertice v1, Vertice v2) {
    stack<int> stack;
    auto current = v2;
    stack.push(current.getIndex());
    map_cor[current] = color::PRETO;
    while(!(current == v1)) {
        bool aux = false;
        for(auto& la : map_lista_adj[current]) {
            if((map_distancia[la] == map_distancia[current] - 1) && map_cor[la] != color::PRETO && !aux) {
                map_cor[la] = color::PRETO;
                stack.push(la.getIndex());
                current = la;
                aux = true;
            }
        }
    }
    string path = "" + to_string(stack.top());
    stack.pop();
    while(!stack.empty()) {
        path += "->" + to_string(stack.top());
        stack.pop();
    }
    return path;
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

void Grafo::atualizarOrdem(int ordem) {
    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j < ordem; j++) {
            int v = (i*ordem)+j;
            map_cor[Vertice(v, v)] = color::BRANCO;
        }
    }
}
