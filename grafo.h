#ifndef GRAFO_H
#define GRAFO_H
#include <unordered_map>
#include <list>

using namespace std;

class Grafo {
 public:
    class Vertice {
     public:
        list<Vertice> listaVizinhos;

        Vertice() {}

        Vertice(int data, int index) {
            data_ = data;
            index_ = index;
        }
        int getData() const { return data_; }
        int getIndex() const { return index_; }
        bool isVisited() const { return visitado_; }
        bool setVisited(bool visitado) { visitado_ = visitado; }


     private:
        int data_;
        int index_;
        bool visitado_{false};
    };

    Grafo();
    list<Vertice> listaVertices;
   //  unordered_map<Vertice, int> umap;
    void inserirVertice(int data);
    bool inserirAresta(int v1, int v2);
    bool deletarVertice(int index);
    bool deletarAresta(int v1, int v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    int DFS(int data);
    int existe(int data);
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};

bool operator==(const Grafo::Vertice &lhs, const Grafo::Vertice &rhs) {
      return lhs.getData() == rhs.getData() && lhs.getIndex() == rhs.getIndex();
}

bool operator<(const Grafo::Vertice &lhs, const Grafo::Vertice &rhs) {
   return lhs.getIndex() < rhs.getIndex();
}

#endif // GRAFO_H