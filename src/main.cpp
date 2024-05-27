#include <iostream>
#include <chrono>
#include "../object/Graph.cpp"

using namespace std;

int main()
{

    // Seed
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    cout << "Seed: " << seed << endl;
    mt19937 gen(seed);

    // Teste
    int order = 4;
    Graph *graph = new Graph(order, &gen);
    graph->printGraphCmd();
    cout << "Número de Arestas: " << graph->getNumEdges() << endl;
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