#include <iostream>
#include <chrono>
#include "../object/Graph.cpp"

using namespace std;

int main(){

    //Seed
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    //Teste
    int order = 5;
    Graph* graph = new Graph(order, &gen);
    graph->printGraphCmd();
    graph->printGraphTxt("../outputs/grafo.dot");
}