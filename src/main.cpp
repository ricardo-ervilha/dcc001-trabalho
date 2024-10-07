#include <iostream>
#include <chrono>
#include "../object/Graph.cpp"
#include "../include/Color.h"

using namespace std;

int main()
{
     Color::Modifier bg_purple(Color::BG_PURPLE);
     Color::Modifier bg_def(Color::BG_DEFAULT);
     Color::Modifier fg_blue(Color::FG_BLUE);
     Color::Modifier fg_green(Color::FG_GREEN);
     Color::Modifier fg_def(Color::FG_DEFAULT);

     // Geração de Seed
     // unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
     unsigned int seed = 2738370113;
     cout << "Valor da Seed: " << seed << endl;
     mt19937 gen(seed);

     // Geração do Grafo com ordem especificada.
     int order;
     cout << "Informe o número de vértices do grafo: ";
     cin >> order;
     cout << endl;
     Graph *graph = new Graph(order, &gen);

     cout << "\n-------------- Questões 1 e 2 - Geração do Grafo --------------"
          << endl;
     cout << "Complexidade => " << bg_purple << "O(|E|)" << bg_def << endl;

     cout << "\n# Número de Vértices: " << fg_green << order << fg_def << endl;

     int max_order = order * (order - 1 ) / 2;
     cout << "# Número máximo de arestas em um grafo completo: " << fg_green << max_order << fg_def << endl;

     if(10*order <= max_order){
          cout << "# Número de Arestas[" << fg_blue << order << fg_def << " , " << fg_blue << 10 * order << fg_def << "]: " << fg_green << graph->getNumEdges() << fg_def << endl;
     }else {
          cout << "# Número de Arestas[" << fg_blue << order << fg_def << " , " << fg_blue << max_order << fg_def << "]: " << fg_green << graph->getNumEdges() << fg_def << endl;
     }
     
     cout << "\nMatriz de Adjacências: " << endl;
     graph->printGraphCmd();

     // Questão 3: Converter matriz para vetor binário.
     cout << "\n\n-------------- Questão 3 - matrix A ==> vetor binário V --------------"
          << endl;
     cout << "Complexidade => " << bg_purple << "O(|V|²)" << bg_def << endl;
     graph->matrixToBinaryVector();
     graph->printBinaryVector();
     cout << endl;

     // Questão 4: Converter vetor binário para vetor de índices.
     cout << "\n\n-------------- Questão 4 - vetor binário V ==> vetor índices I --------------"
          << endl;
     cout << "Complexidade => " << bg_purple << "O(|V|²)" << bg_def << endl;

     int *v1 = graph->binaryVectorToIndexVector();
     graph->printIndexVector();
     cout << endl;

     // Questão 5: Converter do vetor de índices para a matriz de adjacências.
     cout << "\n\n-------------- Questão 5 - vetor índices I ==>  matrix binária A --------------"
          << endl;
     graph->indexVectorToMatrix();
     graph->printMatrixConvertedCmd();
     cout << endl;

     // Questão 6: A partir do (i, j) da matriz acessar o índice k do vetor de índices.
     cout << "\n\n-------------- Questão 6 - Mapeamento (i,j) ==> k --------------"
          << endl;
     int i = 2;
     int j = 5;

     cout << "(ANALÍTICO) - Complexidade => " << bg_purple << "O(1)" << bg_def <<  " - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorAnalytic(i, j) << endl;

     cout << "(ITERATIVO) - Complexidade => " << bg_purple << "O(|V|)" << bg_def << " - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorIteration(i, j) << endl;

     cout << "(RECURSIVO) - Complexidade => " << bg_purple << "O(|V|)" << bg_def << " - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorRecursive(i, j) << endl;
     cout << endl;

     // Questão 7: A partir do k do vetor de índices encontrar o (i, j) da matriz.
     cout << "\n\n-------------- Questão 7 - Mapeamento (i,j) ==> k --------------"
          << endl;
     int k = 15;

     tuple<int, int> aux = graph->mapIndexVectorToMatrixAnalytic(k);
     cout << "Mapeamento ANALÍTICO  - Complexidade => " << bg_purple << "O(|V|^{1/2})" << bg_def << " => Valor de i e j a partir de k = " << k <<  " => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;

     aux = graph->mapIndexVectorToMatrixIteration(k);
     cout << "Mapeamento ITERATIVO  - Complexidade => " << bg_purple << "O(|V|^{1/2})" << bg_def << " => Valor de i e j a partir de k = " << k << " => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;
     cout << endl;

     //----------------------------------------------------------------------------------------

     mt19937 gen2(2 * seed);
     Graph *graph2 = new Graph(order, &gen2);
     graph2->matrixToBinaryVector();
     int *v2 = graph2->binaryVectorToIndexVector();
     graph2->printIndexVector();
     cout << endl;

     // Questão 8: Match e Merge dos vetores de índice.
     int sizeMerge, sizeMatch;
     int sizeMerge2, sizeMatch2;

     int *v32 = graph->mergeQuadratico(graph->getMatrix(), graph2->getMatrix(), &sizeMerge2);
     int *v3 = graph->merge(v1, graph->getNumEdges(), v2, graph2->getNumEdges(), &sizeMerge);

     int *v4 = graph->match(v1, graph->getNumEdges(), v2, graph2->getNumEdges(), &sizeMatch);
     int *v42 = graph->matchQuadratico(graph->getMatrix(), graph2->getMatrix(), &sizeMatch2);

     cout << "\n-------------- Questão 8 - Merge/Match: --------------\n"
          << endl;
     cout << "Grafo 1 - Índices: ";
     for (int i = 0; i < graph->getNumEdges(); i++)
     {
          cout << v1[i] << " ";
     }
     cout << endl;

     cout << "Grafo 2 - Índices: ";
     for (int i = 0; i < graph2->getNumEdges(); i++)
     {
          cout << v2[i] << " ";
     }
     cout << endl;

     cout << "\n\nMerge " << bg_purple << "O(|V|²)" << bg_def << ": \n\t";
     for (int i = 0; i < sizeMerge2; i++)
     {
          cout << v32[i] << " ";
     }
     cout << endl;

     cout << "Merge " << bg_purple << "O(|E|)" << bg_def <<  ":\n\t";
     for (int i = 0; i < sizeMerge; i++)
     {
          cout << v3[i] << " ";
     }
     cout << endl;

     cout << "\n\n";

     cout << "Match: " << bg_purple <<  "O(|V|²)" << bg_def << ": \n\t";
     for (int i = 0; i < sizeMatch2; i++)
     {
          cout << v42[i] << " ";
     }
     cout << endl;

     cout << "Match: " << bg_purple <<  "O(|E|)"  << bg_def << ": \n\t";
     for (int i = 0; i < sizeMatch; i++)
     {
          cout << v4[i] << " ";
     }
     cout << endl;
}