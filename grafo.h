#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <queue>
#include <list>
#include <bits/stdc++.h> 
#include <limits.h>
#include <map>
#include <string.h>

enum color {
    BRANCO,
    CINZA,
    PRETO,
    VERMELHO
};

using namespace std;

class Grafo {
 public:
    class Vertice {
     public:

        Vertice() = default;

        Vertice(int data, int index) {
            data_ = data;
            index_ = index;
        }
        int getData() const { return data_; }
        int getIndex() const { return index_; }
        int getAltura() const { return altura_; }
        void setAltura(int altura) { altura_ = altura; }


         bool operator<(const Grafo::Vertice &rhs) const {
            return getIndex() < rhs.getIndex();
         }

         bool operator==(const Grafo::Vertice &rhs) const {
               return getData() == rhs.getData() && getIndex() == rhs.getIndex();
         }

     private:
        int data_;
        int index_;
        int altura_ {0};
    };

    Grafo();
    list<Vertice> lista_vertices;
    void inserirVertice(int data);
    void inserirAresta(int v1, int v2, int peso);
    void imprimirVertices();
    void DFS(); // busca em profundidade
    bool BFS(Vertice v1, Vertice v2); // busca em largura
    map<int, int> dijkstra();
    string maze(int index1, int index2, int linhas, int colunas);
    void limitarBusca(int index1, int index2, int linhas, int colunas);
    string caminho(Vertice v1, Vertice v2);
    void imprimirCaminho(int index1, int index2, map<int, int> caminhos);
    void atualizarOrdem(int ordem);
    void gerarGraphVizDot(int linhas, int colunas);
    void gerarMapaCorCaminho();
    void gerarPesos(int linhas, int colunas);
    map<Vertice, list<Vertice>> map_lista_adj;
    map<Vertice, color> map_cor;
    map<pair<Vertice, Vertice>, int> map_peso;
    map<Vertice, int> map_distancia;
    map<int, Vertice> map_index;
    map<int, string> map_cor_caminho;
    map<int, list<int>> map_caminho;
    int caminhos{0};
    int ultimo{0};
};

#endif // GRAFO_H
