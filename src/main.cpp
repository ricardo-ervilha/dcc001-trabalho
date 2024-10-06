#include <iostream>
#include <chrono>
#include "../object/Graph.cpp"

using namespace std;

int main()
{
    // Geração de Seed
    // unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    unsigned int seed = 2738370113;
    cout << "Valor da Seed: " << seed << endl;
    mt19937 gen(seed);

    // Geração do Grafo com ordem especificada.
    int order = 8;
    Graph *graph = new Graph(order, &gen);

    graph->printGraphCmd();
    cout << "# Número de Arestas: " << graph->getNumEdges() << endl;

    // Questão 3: Converter matriz para vetor binário.
    graph->matrixToBinaryVector();
    graph->printBinaryVector();
    cout << endl;

    // Questão 4: Converter vetor binário para vetor de índices.
    int *v1 = graph->binaryVectorToIndexVector();
    graph->printIndexVector();
    cout << endl;

    // Questão 5: Converter do vetor de índices para a matriz de adjacências.
    graph->indexVectorToMatrix();
    graph->printMatrixConvertedCmd();
    cout << endl;

    // Questão 6: A partir do (i, j) da matriz acessar o índice k do vetor de índices.
    int i = 2;
    int j = 5;

    cout << "(ANALÍTICO) Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorAnalytic(i, j) << endl;

    cout << "(ITERATIVO) Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorAnalytic(i, j) << endl;

    cout << "(RECURSIVO) Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorAnalytic(i, j) << endl;
    cout << endl;

    // Questão 7: A partir do k do vetor de índices encontrar o (i, j) da matriz.
    int k = 15;

    tuple<int, int> aux = graph->mapIndexVectorToMatrixAnalytic(k);
    cout << "Mapeamento ANALÍTICO => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;

    aux = graph->mapIndexVectorToMatrixIteration(k);
    cout << "Mapeamento ITERATIVO => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;
    cout << endl;

    //----------------------------------------------------------------------------------------

    mt19937 gen2(2*seed);
    Graph *graph2 = new Graph(order, &gen2);
    graph2->matrixToBinaryVector();
    int *v2 = graph2->binaryVectorToIndexVector();
    graph2->printIndexVector();
    cout << endl;


    // Questão 8: Match e Merge dos vetores de índice.
    int *v3 = graph->merge(v1, graph->getNumEdges(), v2, graph2->getNumEdges());
    int *v4 = graph->match(v2, graph->getNumEdges(), v2, graph2->getNumEdges());

    cout << "# Merge: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v3[i] << "\t";
    }
    cout << endl;
    
    cout << "# Match: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v4[i] << "\t";
    }
    cout << endl;
}