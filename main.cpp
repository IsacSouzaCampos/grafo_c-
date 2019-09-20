#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Grafo.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    Grafo *gr = new Grafo();

    gr->imprimirVertices();
    
    for(int i = 0; i < 10; i++) {
        gr->inserirVertice(i+5);
    }

    // gr->imprimirVertices();

    gr->inserirAresta(gr->listaVertices.at(2), gr->listaVertices.at(4));
    gr->inserirAresta(gr->listaVertices.at(2), gr->listaVertices.at(5));
    gr->inserirAresta(gr->listaVertices.at(3), gr->listaVertices.at(6));

    gr->imprimirListaAdjacentes();
    cout << endl;
    gr->deletarVertice(5);
    gr->deletarAresta(2, 4);
    gr->deletarAresta(4, 2);
    gr->imprimirListaAdjacentes();

    cout << endl;


//     while(true) {
//         int opcao;
//         cout << "--------------------";
//         cout << "\n\n[1] adicionar aresta\n[2] deletar aresta\n[3] existe\n[4] menor distancia\n[5] adicionar vertice" << endl;
//         cout << "[6] imprimir\n[0] sair\nopcao: " << flush;
//         cin >> opcao;

//         if(!opcao)
//             break;
//         if(opcao < 0 || opcao > 6)
//             continue;
//         switch(opcao) {
//             int vi, vf, valor;
//             case 1: cout << "--------------------" << endl;
//                     TIPOPESO peso;
//                     cout << "vi: " << flush;
//                     cin >> vi;
//                     cout << "vf: " << flush;
//                     cin >> vf;
//                     cout << "peso: " << flush;
//                     cin >> peso;
//                     criaAresta(gr, vi, vf, peso);
//                     break;
//             case 2: cout << "--------------------" << endl;
//                     cout << "vi: " << flush;
//                     cin >> vi;
//                     cout << "vf: " << flush;
//                     cin >> vf;
//                     cout << "antes de deletarAresta()" << endl;
//                     deletarAresta(gr, vi, vf);
//                     break;
//             case 3: cout << "--------------------" << endl;
//                     cout << "valor a ser encontrado: " << flush;
//                     cin >> valor;
//                     cout << "existe?: " << (buscaEmProfundidade(gr, valor) == 1 ? "sim" : "não") << endl;
//                     break;
//             case 4: {cout << "--------------------" << endl;
//                     cout << "vi: " << flush;
//                     cin >> vi;
//                     cout << "vf: " << flush;
//                     cin >> vf;
//                     int *distancia = dijkstra(gr, vi);
//                     cout << "distancia entre " << vi << " e " << vf << ": " << distancia[vf] << endl;
//                     delete distancia;
//                     break;}
//             case 5: criarVertice(gr);
//                     break;
//             case 6: imprime(gr);    
//                     break;
//         }
//     }
    return 0;
}
