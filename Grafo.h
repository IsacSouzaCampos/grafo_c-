
#ifndef _GRAFO_H_
#define _GRAFO_H_

#define true 1
#define false 0

#define BRANCO 0
#define AMARELO 1
// #define VERMELHO 2

typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;    // vertice destino
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    int index;
    ADJACENCIA *cab;
    // VERTICE *prox;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    int maiorPeso;
    VERTICE *adj;
} GRAFO;

GRAFO *criaGrafo(int v);
ADJACENCIA *criaAdj(int v, int peso);
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p);
void imprime(GRAFO *gr);
bool buscaEmProfundidade(GRAFO *g, int valor);
bool existe(GRAFO *g, int i, int *cor, int valor);
void inicializaDijkstra(GRAFO *g, int *d, int *p, int s);
void atualizaDistancia(GRAFO *g, int *d, int *p, int u, int v);
int *dijkstra(GRAFO *g, int s);
bool existeAberto(GRAFO *g, bool *aberto);
int menorDistancia(GRAFO *g, bool *aberto, int *d);

#endif