#include <iostream>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    Grafo gr = Grafo();
    
    int linhas = 10, colunas = 10;
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
    
    // gr.inserirVertice(0);
    // gr.inserirVertice(1);
    // gr.inserirVertice(2);
    // gr.inserirVertice(3);
    // gr.inserirVertice(4);
    // gr.inserirVertice(5);

    // gr.inserirAresta(0, 1, 10);
    // gr.inserirAresta(0, 2, 5);
    // gr.inserirAresta(1, 3, 1);
    // gr.inserirAresta(2, 1, 3);
    // gr.inserirAresta(2, 3, 8);
    // gr.inserirAresta(2, 4, 2);
    // gr.inserirAresta(2, 4, 2);
    // gr.inserirAresta(3, 4, 4);
    // gr.inserirAresta(3, 5, 4);
    // gr.inserirAresta(4, 5, 6);

    // gr.imprimirListaAdjacentes();

    gr.DFS();
    cout << endl;
    gr.BFS();
    cout << endl;
    list<pair<int, int>> caminhos = gr.dijkstra();
    gr.imprimirCaminho(0, 55, caminhos);
    cout << endl;
    gr.imprimirCaminho(0, 33, caminhos);
    cout << endl;

    return 0;
}
