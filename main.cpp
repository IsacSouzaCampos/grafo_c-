#include <iostream>
#include <time.h>
#include "grafo.h"

using namespace std;

void gerarGrafo(int linhas, int colunas, Grafo& gr) {
    clock_t t_inicio, t_fim, t_decorrido;

    for(int i = 0; i < linhas*colunas; i++)
        gr.inserirVertice(i);

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
}

int main(int argc, char* argv[]) {
    Grafo gr = Grafo();
    gr.gerarMapaCorCaminho();
    // int ordem = 10;
    int linhas = 12, colunas = 12;
    gerarGrafo(linhas, colunas, gr);


    for(int i = floor(linhas/8); i < floor((linhas*7)/8); i++) {
        int linha = i*colunas;
        for(int j = floor(colunas/8); j < floor((colunas*7)/8); j++) {
            int v = linha+j;
            gr.map_peso[make_pair(gr.map_index[v], gr.map_index[v+1])] = 2;
            // gr.map_cor[gr.map_index[v]] = color::VERMELHO;
            // gr.map_cor[gr.map_index[v+1]] = color::VERMELHO;
        }
    }
    for(int i = floor(linhas/4); i < floor((linhas*3)/4)-1; i++) {
        int linha = i*colunas;
        for(int j = floor(colunas/4); j < floor((colunas*3)/4)-1; j++) {
            int v = linha+j;
            gr.map_peso[make_pair(gr.map_index[v], gr.map_index[v+1])] = 3;
            // gr.map_cor[gr.map_index[v]] = color::CINZA;
            // gr.map_cor[gr.map_index[v+1]] = color::CINZA;
        }
    }
    for(int i = floor(linhas/3); i < floor((linhas*2)/3)-1; i++) {
        int linha = i*colunas;
        for(int j = floor(colunas/3); j < floor((colunas*2)/3)-1; j++) {
            int v = linha+j;
            gr.map_peso[make_pair(gr.map_index[v], gr.map_index[v+1])] = 4;
            // gr.map_cor[gr.map_index[v]] = color::VERMELHO;
            // gr.map_cor[gr.map_index[v+1]] = color::VERMELHO;
        }
    }
    gr.gerarGraphVizDot(linhas, colunas);

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
