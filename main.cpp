#include <iostream>
#include <time.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    clock_t t_inicio, t_fim, t_decorrido;
    Grafo gr = Grafo();
    
    // int linhas = 10, colunas = 10;
    for(int ordem = 11; ordem < 52; ordem++) {
        int linhas = ordem, colunas = ordem;
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

        // gerar caminhos
        t_inicio = clock();
        
        float centro = (ordem/2)-0.5;
        centro += centro*ordem;
        float inferior_esquerdo = ordem*(ordem-1), superior_direito = ordem-1, inferior_direito = (ordem*ordem)-1;
        gr.maze(0, inferior_esquerdo);
        gr.maze(superior_direito, inferior_direito);
        gr.maze(centro, superior_direito);
        gr.maze(centro, 0);
        gr.maze(centro, inferior_direito);
        
        t_fim = clock();

        t_decorrido = ((t_fim - t_inicio) / (CLOCKS_PER_SEC / 1000));
        // t_decorrido = ((float) (t_fim - t_inicio) ) / CLOCKS_PER_SEC;
        cout << "para ordem " << ordem << ", tempo = " << t_decorrido << endl;
        ordem++;
    }

    // cout << gr.maze(33, 58) << endl;
    // cout << gr.maze(26, 75) << endl;
    // cout << gr.maze(16, 69) << endl;
    // cout << gr.maze(38, 63) << endl;

    return 0;
}
