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

    cout << "\n-------------- Questões 1 e 2 - Geração do Grafo --------------"
         << endl;
    cout << "Complexidade: O(|E|)" << endl;

    cout << "\n# Número de Vértices: " << order << endl;
    cout << "# Número de Arestas[" << order << " , " << 10 * order << "]: " << graph->getNumEdges() << endl;
    cout << "\nMatriz de Adjacências: " << endl;
    graph->printGraphCmd();

    // Questão 3: Converter matriz para vetor binário.
    cout << "\n\n-------------- Questão 3 - matrix A ==> vetor binário V --------------"
         << endl;
    cout << "Complexidade => O(|V|²)" << endl;
    graph->matrixToBinaryVector();
    graph->printBinaryVector();
    cout << endl;

    // Questão 4: Converter vetor binário para vetor de índices.
    cout << "\n\n-------------- Questão 4 - vetor binário V ==> vetor índices I --------------"
         << endl;
    cout << "Complexidade => O(|V|²)\n"
         << endl;
    int *v1 = graph->binaryVectorToIndexVector();
    graph->printIndexVector();
    cout << endl;

    // Questão 5: Converter do vetor de índices para a matriz de adjacências.
    cout << "\n\n-------------- Questão 5 - vetor índices I ==>  matrix binária A --------------"
         << endl;
    // cout << "Complexidade => O(|V|²)\n" << endl;
    graph->indexVectorToMatrix();
    graph->printMatrixConvertedCmd();
    cout << endl;

    // Questão 6: A partir do (i, j) da matriz acessar o índice k do vetor de índices.
    cout << "\n\n-------------- Questão 6 - Mapeamento (i,j) ==> k --------------"
         << endl;
    int i = 2;
    int j = 5;

    cout << "(ANALÍTICO) - Complexidade: O(1)   - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorAnalytic(i, j) << endl;

    cout << "(ITERATIVO) - Complexidade: O(|V|) - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorIteration(i, j) << endl;

    cout << "(RECURSIVO) - Complexidade: O(|V|) - Valor do índice k a partir do i: " << i << " e j: " << j << " => " << graph->mapMatrixToIndexVectorRecursive(i, j) << endl;
    cout << endl;

    // Questão 7: A partir do k do vetor de índices encontrar o (i, j) da matriz.
    cout << "\n\n-------------- Questão 7 - Mapeamento (i,j) ==> k --------------"
         << endl;
    int k = 9;

    tuple<int, int> aux = graph->mapIndexVectorToMatrixAnalytic(k);
    cout << "Mapeamento ANALÍTICO  - Complexidade: O(|V|) => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;

    aux = graph->mapIndexVectorToMatrixIteration(k);
    cout << "Mapeamento ITERATIVO  - Complexidade: O(|V|) => i: " << get<0>(aux) << " j: " << get<1>(aux) << endl;
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

    cout << "\n\nMerge O(n²): \n\t";
    for (int i = 0; i < sizeMerge2; i++)
    {
        cout << v32[i] << " ";
    }
    cout << endl;

    cout << "Merge O(n): \n\t";
    for (int i = 0; i < sizeMerge; i++)
    {
        cout << v3[i] << " ";
    }
    cout << endl;

    cout << "\n\n";

    cout << "Match: O(n²): \n\t";
    for (int i = 0; i < sizeMatch2; i++)
    {
        cout << v42[i] << " ";
    }
    cout << endl;

    cout << "Match O(n): \n\t";
    for (int i = 0; i < sizeMatch; i++)
    {
        cout << v4[i] << " ";
    }
    cout << endl;
}