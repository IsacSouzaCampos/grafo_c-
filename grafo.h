#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <queue>
#include <list>
#include <bits/stdc++.h> 
#include <limits.h>
#include <map>

enum color {
    BRANCO,
    CINZA,
    PRETO
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
        color getColor() const { return visitado_; }
        void setColor(color visitado) { visitado_ = visitado; }
        int getAltura() const { return altura_; }
        void setAltura(int altura) { altura_ = altura; }
        int getDistancia() const { return distancia_; }
        void setDistancia(int distancia) { distancia_ = distancia; }


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
        int distancia_{0};
        color visitado_ {BRANCO};
    };

    Grafo();
    list<Vertice> lista_vertices;
    list<pair<pair<Vertice, Vertice>, int>> lista_arestas;
    void inserirVertice(int data);
    bool inserirAresta(int v1, int v2, int peso);
    bool deletarVertice(int index);
    bool deletarAresta(int v1, int v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    void DFS(); // busca em profundidade
    void BFS(); // busca em largura
    map<int, int> dijkstra();
    void maze(int index1, int index2);
    void atualizarCorLista(Vertice& v, color cor);
    void imprimirCaminho(int index1, int index2, map<int, int> caminhos);
    map<Vertice, list<Vertice>> map_lista_adj;
    map<Vertice, color> map_cor;
    map<pair<Vertice, Vertice>, int> map_peso;
    map<Vertice, int> map_distancia;
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};

#endif // GRAFO_H
