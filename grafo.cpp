#include <iostream>
#include <math.h>
#include "grafo.h"



Grafo::Grafo() = default;

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    lista_vertices.push_back(Vertice(data, index));
    Vertice v = Vertice(data, index);
    map_lista_adj[v];
    map_cor[v] = color::BRANCO;
    map_distancia[v] = 0;
    map_index[index] = v;
    ultimo++;
    cout << data << endl;
}

void Grafo::inserirAresta(int v1, int v2, int peso) {
    Vertice vi = map_index[v1];
    Vertice vj = map_index[v2];
    
    pair<Vertice, Vertice> p1(vi, vj);
    map_lista_adj[vi].push_back(vj);
    map_peso[make_pair(vi, vj)] = peso;
    cout << "aresta(" << v1 << ", " << v2 << ")" << endl;
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
    }
    return false;
}

map<int, int> Grafo::dijkstra() {
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

string Grafo::maze(int index1, int index2, int linhas, int colunas) {
    Vertice v1 = map_index[index1];
    Vertice v2 = map_index[index2];
    
    limitarBusca(index1, index2, linhas, colunas);
    if(BFS(v1, v2)) {
        gerarGraphVizDot(linhas, colunas);
        system("xdot graphviz.dot");
        for(auto& mc : map_cor) {
            if(mc.second == color::VERMELHO)
                mc.second = color::BRANCO;
        }
        gerarGraphVizDot(linhas, colunas);
        system("xdot graphviz.dot");
        return caminho(v1, v2);
    } else {
        for(auto& mc : map_cor) {
            if(mc.second == color::VERMELHO)
                mc.second = color::BRANCO;
        }
        if(BFS(v1, v2)) {
            gerarGraphVizDot(linhas, colunas);
            system("xdot graphviz.dot");
            return caminho(v1, v2);
        }
    }
    return "erro";
}

void Grafo::limitarBusca(int index1, int index2, int linhas, int colunas) {
    int vertice_referencia = index1;
    int dimensao = (linhas * colunas) - 1;
    int temp = index1;
    if(index2 > index1) {
        if(index1 > (colunas - 1))
            vertice_referencia -= colunas;
        while(true) {
            if((temp + colunas) > index2) {
                if((temp + colunas) > dimensao)
                    vertice_referencia--;
                else {
                    if(temp == index2 || (temp + colunas) == index2) { vertice_referencia++; break; }  // por enquanto
                    int linha_atual = temp + 1, linha_inferior = temp + colunas;
                    int resto_linha_atual, resto_linha_inferior;
                    while(true) {
                        if(linha_atual == index2) { vertice_referencia--; break; }
                        if(linha_inferior == index2) { vertice_referencia++; break; }
                        resto_linha_atual = (linha_atual+1)%colunas;
                        resto_linha_inferior = linha_inferior%colunas;
                        if( (linha_atual+1)%colunas ) linha_atual++;
                        else { vertice_referencia++; break; }
                        if ( linha_inferior%colunas ) linha_inferior--;
                        else { vertice_referencia--; break; }
                        // linha_atual++; linha_inferior--;
                    }
                }
                // temp > index2 ? vertice_referencia++ : vertice_referencia--;
                break;
            }
            temp += colunas;
        }
    } else {
        if(index1 <= ((dimensao)-colunas))
            vertice_referencia += colunas;
        while(true) {
            if((temp - colunas) < index2) {
                if((temp - colunas) < 0)
                    vertice_referencia++;
                else {
                    if(temp == index2 || (temp - colunas) == index2) { vertice_referencia++; break; }  // por enquanto
                    int linha_atual = temp - 1, linha_superior = temp - colunas;
                    while(true) {
                        if(linha_atual == index2) { vertice_referencia++; break; }
                        if(linha_superior == index2) { vertice_referencia--; break; }
                        if( (linha_atual%colunas) ) linha_atual--;
                        else { vertice_referencia--; break; }
                        if( ((linha_superior+1)%colunas) ) linha_superior++;
                        else { vertice_referencia++; break; }
                        // linha_atual--; linha_superior++;
                    }
                }
                // temp < index2 ? vertice_referencia-- : (vertice_referencia -= colunas)--;
                break;
            }
            temp -= colunas;
        }
    }
    if(map_cor[map_index[vertice_referencia]] != color::PRETO)
        map_cor[map_index[vertice_referencia]] = color::VERMELHO;

    temp = vertice_referencia;
    while((temp -= colunas) > 0) {
        if(map_cor[map_index[temp]] != color::PRETO)
            map_cor[map_index[temp]] = color::VERMELHO;
    }
    temp = vertice_referencia;
    while((temp += colunas) < dimensao) {
        if(map_cor[map_index[temp]] != color::PRETO)
            map_cor[map_index[temp]] = color::VERMELHO;
    }

    // traçar linha horizontal
    cout << "vertice_referencia: " << vertice_referencia << endl;
    cout << "vertice_referencia%colunas: " <<  vertice_referencia%colunas << endl;
    
    if(index1 >= colunas && index1 <= (dimensao - colunas)){
        // para a esquerda
        for(int i = 1; i <= vertice_referencia%colunas; i++) {
            if(map_cor[map_index[vertice_referencia - i]] != color::PRETO)
                map_cor[map_index[vertice_referencia - i]] = color::VERMELHO;
        }
    
        // para a direita
        for(int i = 1; i < (colunas-(vertice_referencia%colunas)); i++) {
            if(map_cor[map_index[vertice_referencia + i]] != color::PRETO)
                map_cor[map_index[vertice_referencia + i]] = color::VERMELHO;
        }
    }
    gerarGraphVizDot(linhas, colunas);
    system("xdot graphviz.dot");
}

string Grafo::caminho(Vertice v1, Vertice v2) {
    stack<int> stack;
    auto current = v2;
    stack.push(current.getIndex());
    map_cor[current] = color::PRETO;
    while(!(current == v1)) {
        for(auto& la : map_lista_adj[current]) {
            if((map_distancia[la] == map_distancia[current] - 1) && map_cor[la] == color::CINZA) {
                map_cor[la] = color::PRETO;
                stack.push(la.getIndex());
                current = la;
                break;
            }
        }
    }
    string path = "" + to_string(stack.top());
    map_caminho[caminhos].push_back(stack.top());
    stack.pop();
    while(!stack.empty()) {
        path += "->" + to_string(stack.top());
        map_caminho[caminhos].push_back(stack.top());
        stack.pop();
    }
    ++caminhos;
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

void Grafo::gerarGraphVizDot(int linhas, int colunas) {
    ofstream myfile;
    myfile.open ("graphviz.dot");

    myfile << "digraph G {" << endl;
    for(auto& current : lista_vertices) {
        for(auto& mla : map_lista_adj[current])
            myfile << current.getIndex() << "->" << mla.getIndex() << "[arrowhead = \"none\"]" << endl;
    }
    for(int i = 0; i < linhas; i++) {
        myfile << "{rank = same; ";
        for(int j = 0; j < colunas; j++) {
            int current = j+(i*colunas);
            myfile << current << " ";
        }
        myfile << "}" << endl;
    }
    for(auto& mc : map_cor) {
        if(mc.second == color::VERMELHO) {
            myfile << mc.first.getIndex() << " [style=filled, fillcolor=red]" << endl;
        } else if(mc.second == color::CINZA) {
            myfile << mc.first.getIndex() << " [style=filled, fillcolor=grey]" << endl;
        }
    }
    int i = 0;
    for(auto& m_caminho : map_caminho) {
        for(auto& lista_caminhos : m_caminho.second)
            myfile << lista_caminhos << " [style=filled, fillcolor=" << map_cor_caminho[m_caminho.first%7] << "]" << endl;
    }
    myfile << "}" << endl;

    myfile.close();
}

void Grafo::gerarMapaCorCaminho() {
    map_cor_caminho[0] = "black";
    map_cor_caminho[1] = "blue";
    map_cor_caminho[2] = "sienna";
    map_cor_caminho[3] = "purple";
    map_cor_caminho[4] = "green";
    map_cor_caminho[5] = "turquoise";
    map_cor_caminho[6] = "yellow";
}
