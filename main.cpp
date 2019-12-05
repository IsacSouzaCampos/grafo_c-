#include <iostream>
#include <time.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    clock_t t_inicio, t_fim, t_decorrido;
    
    Grafo gr = Grafo();
    int ordem = 10;
    int linhas = 5, colunas = 9;

    for(int i = 0; i < linhas*colunas; i++) {
        gr.inserirVertice(i);
    }

    t_inicio = clock();
    
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas-1; j++) {
            int v1 = j+(i*colunas);
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
    t_fim = clock();
    t_decorrido = ((t_fim - t_inicio) / (CLOCKS_PER_SEC / 1000));
    cout << "tempo = " << t_decorrido << endl;

    int opcao = -1;
    while(opcao) {
        cout << "\n[1]: inserir caminho\n[0]: sair\nopcao: " << flush;
        cin >> opcao;
        switch(opcao) {
            case 1: int vi, vj;
                    cout << "vertice inicial: " << flush;
                    cin >> vi;
                    cout << "vertice final: " << flush;
                    cin >> vj;
                    cout << gr.maze(vi, vj, linhas, colunas) << endl;
                    break;
            case 0: break;
        }
        if(opcao) {
            gr.gerarGraphVizDot(linhas, colunas);
            system("xdot graphviz.dot");
        }
    }

    return 0;
}
