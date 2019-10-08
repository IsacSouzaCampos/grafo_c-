#ifndef GRAFO_H
#define GRAFO_H
// #include <unordered_map>
#include <stack>
#include <list>

using namespace std;

class Grafo {
 public:
    class Vertice {
     public:
        list<Vertice> listaVizinhos;

        Vertice() = default;

        Vertice(int data, int index) {
            data_ = data;
            index_ = index;
        }
        int getData() const { return data_; }
        int getIndex() const { return index_; }
        bool isVisited() const { return visitado_; }
        void setVisited(bool visitado) { visitado_ = visitado; }
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
        bool visitado_ {false};
        int altura_ {0};
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
    int DFS();
    int existe(Vertice& v, stack<Vertice&>& sck, int data, int& index);
    int vertices{0};
    int arestas{0};
    int ultimo{0};
};


#endif // GRAFO_H