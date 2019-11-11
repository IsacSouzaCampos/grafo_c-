#include <iostream>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    Grafo gr = Grafo();
    
    int linhas = 10, colunas = 10;
    for(int i = 0; i < linhas*colunas; i++) {
        gr.inserirVertice(i);
    }

    // gr.inserirAresta(0, 1, 1);
    // gr.inserirAresta(1, 2, 3);
    // gr.inserirAresta(2, 3, 2);
    // gr.inserirAresta(2, 4, 4);
    // gr.inserirAresta(0, 5, 3);
    // gr.inserirAresta(5, 6, 2);
    // gr.inserirAresta(6, 7, 5);
    // gr.inserirAresta(6, 8, 1);

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

    // for(auto& m : gr.map_lista_adj) {
    //     cout << m.first.getIndex() << ": " << flush;
    //     for(auto& ml : m.second) {
    //         cout << ml.getIndex() << " / " << flush;
    //     }
    //     cout << endl;
    // }

    cout << gr.maze(0, 55) << endl;
    cout << gr.maze(0, 33) << endl;

    return 0;
}
