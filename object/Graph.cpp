#include <iostream>
#include <fstream>
#include "../include/Graph.h"
#include "../include/Utils.h"

using namespace std;

Graph::Graph(int order, mt19937* gen){
    
    //Salva as variáveis do Grafo
    this->order = order;
    this->gen = gen;


    //Instancia a matriz de adjacências
    this->matrix = new bool*[this->order];

    for(int i = 0; i < this->order; i++)
        this->matrix[i] = new bool[this->order];


    //Preenche o grafo com valores
    this->fillGraph();
}

Graph::~Graph(){
    for(int i = 0; i < this->order; i++)
        delete [] matrix[i];

    delete [] matrix;
}

int Graph::getOrder(){
    return this->order;
}

void Graph::fillGraph(){

    for(int i = 0; i < this->order; i++){
        for(int j = i+1; j < this->order; j++){
            
            this->matrix[i][j] = intRandom(0, 1, this->gen) == 1; 
            
            if(this->matrix[i][j] == 1) 
                this->numEdges += 1;

            this->matrix[j][i] = this->matrix[i][j]; //grafo não direcionado
            this->matrix[i][i] = 0; //sem self-loop
        }
    }

}

void Graph::printGraphCmd(){

    for(int i = 0; i < this->order; i++){
        for(int j = 0; j < this->order; j++){
            cout << this->matrix[i][j] << "\t";
        }
        cout << endl;
    }

}

void Graph::printGraphTxt(string pathname){
    ofstream file(pathname);

    if(file.is_open()){
        file << "graph grafo {" << endl;

        for(int i = 0; i < this->order; i++){
            for(int j = 0; j < this->order; j++){
                if(i < j && this->matrix[i][j] == 1)
                    file << "\t" << i << " -- " << j << ";" << endl;
            }
        }

        file << "}";
    } else{
        cerr << "Exceção durante abertura/escrita no arquivo" << endl;
    }
    
    file.close();
}

int Graph::getNumEdges(){
    return this->numEdges;
}