#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include <random>
#include <tuple>

using namespace std;

class Graph{

    private:
        int order;
        int numEdges = 0;
        bool** matrix;
        bool** matrixConverted; // matriz obtida apóss converter o vetor de índices
        bool* binaryVector;// representação da matriz de adjacência em um vetor binário
        int* indexVector;// representação da matriz de adjacência em um vetor de índices
        mt19937 *gen;
        void fillGraph();
        int fRec(int i, int j, int aux);
        
    public:
        Graph(int order, mt19937 *gen);
        ~Graph();
        int getOrder();
        void printGraphCmd();
        void printGraphTxt(string pathname);
        void printBinaryVector();
        void printIndexVector();
        void printMatrixConvertedCmd();
        int getNumEdges();
        bool* matrixToBinaryVector();
        int* binaryVectorToIndexVector();
        bool** indexVectorToMatrix();
        int* merge(int *v1,int s1, int *v2, int s2);
        int* match(int *v1,int s1, int *v2, int s2);
        int mapMatrixToIndexVectorAnalytic(int i, int j);
        int mapMatrixToIndexVectorRecursive(int i, int j);
        int mapMatrixToIndexVectorIteration(int i, int j);
        tuple<int, int> mapIndexVectorToMatrixIteration(int k);
};

#endif