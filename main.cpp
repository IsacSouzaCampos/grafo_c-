#include <iostream>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    Grafo gr = Grafo();

    gr.imprimirVertices();
    
    gr.inserirVertice(0);
    gr.inserirVertice(1);
    gr.inserirVertice(2);
    gr.inserirVertice(3);
    gr.inserirVertice(4);

    gr.inserirAresta(0, 1, 1);
    gr.inserirAresta(1, 2, 3);
    gr.inserirAresta(0, 3, 5);
    gr.inserirAresta(3, 4, 2);

    // gr.imprimirListaAdjacentes();

    // gr.DFS();
    // gr.BFS();
    gr.dijkstra();
    cout << endl;

    return 0;
}
