#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <queue>
#include <list>
#include <vector>

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
        color visitado_ {BRANCO};
    };

    Grafo();
    list<Vertice> listaVertices;
    list<pair<Vertice, Vertice>> listaArestas;
    list<pair<pair<Vertice, Vertice>, int>> listaPesos;
    void inserirVertice(int data);
    bool inserirAresta(int v1, int v2);
    bool deletarVertice(int index);
    bool deletarAresta(int v1, int v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    void DFS(); // busca em profundidade
    void BFS(); // busca em largura
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};

#endif // GRAFO_H