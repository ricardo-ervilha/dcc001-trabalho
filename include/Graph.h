#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include <random>

using namespace std;

class Graph{

    private:
        int order;
        int** matrix;
        mt19937 *gen;
        void fillGraph();

    public:
        Graph(int order, mt19937 *gen);
        ~Graph();
        int getOrder();
        void printGraphCmd();
        void printGraphTxt(string pathname);
};

#endif