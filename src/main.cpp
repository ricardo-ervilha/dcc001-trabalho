#include <iostream>
#include <chrono>
#include "../object/Graph.cpp"

using namespace std;

void luquetas(Graph *graph){
    graph->matrixToBinaryVector();
    graph->printBinaryVector();

    graph->binaryVectorToIndexVector();
    graph->printIndexVector();

    graph->indexVectorToMatrix();
    cout << "Matrix convertida..." << endl;
    graph->printMatrixConvertedCmd();

    int v1[] = {4};
    int v2[] = {1, 4, 5};
    int *v3 = graph->merge(v1, 1, v2, 3);
    int *v4 = graph->match(v1, 1, v2, 3);

    cout << "merge: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v3[i] << "\t";
    }

    cout << endl;
    cout << "match: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v4[i] << "\t";
    }
    cout << endl;
}

void ricardo(Graph *graph){
    
    int i = 2;
    int j = 3;
    cout << "Indice (i,j) mapeado analiticamente em: " <<  graph->mapMatrixToIndexVectorAnalytic(i,j) << endl;

    cout << "Indice (i,j) mapeado recursivamente em: " <<  graph->mapMatrixToIndexVectorRecursive(i,j) << endl;
    
    cout << "Indice (i,j) mapeado iterativamente em: " <<  graph->mapMatrixToIndexVectorRecursive(i,j) << endl;
}

int main()
{

    // Seed
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    cout << "Seed: " << seed << endl;
    mt19937 gen(seed);

    // Teste
    int order = 5;
    Graph *graph = new Graph(order, &gen);
    graph->printGraphCmd();
    cout << "Número de Arestas: " << graph->getNumEdges() << endl;
    
    graph->matrixToBinaryVector();
    graph->printBinaryVector();

    graph->binaryVectorToIndexVector();
    graph->printIndexVector();

    int k;
    cin >> k;

    tuple<int, int> aux = graph->mapIndexVectorToMatrixAnalytic(k);
    cout << "i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;
}