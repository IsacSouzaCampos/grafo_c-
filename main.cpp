#include <iostream>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    Grafo gr = Grafo();
    
    int linhas = 3, colunas = 3;
    for(int i = 0; i < linhas*colunas; i++) {
        gr.inserirVertice(i);
    }

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas-1; j++) {
            int v1 = (i*linhas)+j;
            int v2 = v1+1;
            gr.inserirAresta(v1, v2, 1);
            gr.inserirAresta(v2, v1, 1);
        }
    }
    for(int j = 0; j < colunas; j++) {
        for(int i = 0; i < linhas-1; i++) {
            int v1 = j+(i*colunas);
            int v2 = v1+colunas;
            gr.inserirAresta(v1, v2, 1);
            gr.inserirAresta(v2, v1, 1);
        }
    }

    // for(auto& m : gr.lista_adj) {
    //     cout << m.first.getIndex() << ": " << flush;
    //     for(auto& ml : m.second) {
    //         cout << ml.getIndex() << " / " << flush;
    //     }
    //     cout << endl;
    // }

    gr.DFS();
    // cout << endl;
    // gr.BFS();
    // cout << endl;
    // list<pair<int, int>> caminhos = gr.dijkstra();
    // gr.imprimirCaminho(0, 55, caminhos);
    // cout << endl;
    // gr.imprimirCaminho(0, 33, caminhos);
    // cout << endl;

    return 0;
}
