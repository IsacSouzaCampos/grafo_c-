#include <iostream>
#include <time.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    clock_t t_inicio, t_fim, t_decorrido;

    ofstream myfile;
    myfile.open ("result.csv");
    
    
    // int linhas = 10, colunas = 10;
    Grafo gr = Grafo();
    int ordem_plano = 301;
    int linhas = ordem_plano, colunas = ordem_plano;

    for(int i = 0; i < linhas*colunas; i++) {
        gr.inserirVertice(i);
    }

    t_inicio = clock();
    
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
    t_fim = clock();
    t_decorrido = ((t_fim - t_inicio) / (CLOCKS_PER_SEC / 1000));
    cout << "tempo = " << t_decorrido << endl;

    // tornar todos os vertices bloqueados
    for(auto& mc : gr.map_cor)
        mc.second = color::PRETO;

    for(int ordem = 3; ordem < ordem_plano; ordem++) {
        gr.atualizarOrdem(ordem);

        // gerar caminhos
        t_inicio = clock();

        float centro = (ordem/2)-0.5;
        centro += (centro*ordem)+ordem;
        centro -= (ordem/2)-0.5;
        float inferior_esquerdo = ordem*(ordem-1), superior_direito = ordem-1, inferior_direito = (ordem*ordem)-1;
        gr.maze(0, inferior_esquerdo);
        gr.maze(superior_direito, inferior_direito);
        gr.maze(centro, superior_direito);
        gr.maze(centro, 0);
        gr.maze(centro, inferior_direito);

        t_fim = clock();

        t_decorrido = ((t_fim - t_inicio) / (CLOCKS_PER_SEC / 1000));
        // t_decorrido = ((float) (t_fim - t_inicio) ) / CLOCKS_PER_SEC;
        myfile << ordem << ","<< t_decorrido << endl;
        cout << "para ordem " << ordem << ", tempo = " << t_decorrido << endl;
        ordem++;
    }

    // cout << gr.maze(33, 58) << endl;
    // cout << gr.maze(26, 75) << endl;
    // cout << gr.maze(16, 69) << endl;
    // cout << gr.maze(38, 63) << endl;
    // gr.imprimirListaAdjacentes();

    myfile.close();

    return 0;
}
