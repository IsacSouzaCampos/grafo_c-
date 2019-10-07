#ifndef GRAFO_H
#define GRAFO_H
#include <list>

using namespace std;

class Grafo {
 private:
    class Vertice {
     public:
        list<Vertice> listaVizinhos;

        Vertice() {}

        Vertice(int data, int index) {
            data_ = data;
            index_ = index;
        }
        int getData() const{ return data_; }
        int getIndex() const { return index_; }
        bool operator==(const Vertice &rhs) {
           return data_ == rhs.getData() && index_ == rhs.getIndex();
        }

     private:
        int data_;
        int index_;
    };

 public:
    Grafo();
    list<Vertice> listaVertices;
    void inserirVertice(int data);
    bool inserirAresta(int v1, int v2);
    bool deletarVertice(int index);
    bool deletarAresta(int v1, int v2);
    void imprimirListaAdjacentes();
    void imprimirVertices();
    void DFS(int data);
    int existe(int data);
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};

#endif // GRAFO_H