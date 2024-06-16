#include <iostream>
#include <fstream>
#include "../include/Graph.h"
#include "../include/Utils.h"

using namespace std;

Graph::Graph(int order, mt19937 *gen)
{

    // Salva as variáveis do Grafo
    this->order = order;
    this->gen = gen;

    // Instancia a matriz de adjacências
    this->matrix = new bool *[this->order];
    this->matrixConverted = new bool *[this->order];

    for (int i = 0; i < this->order; i++)
    {
        this->matrix[i] = new bool[this->order];
        this->matrixConverted[i] = new bool[this->order];
    }

    // Preenche o grafo com valores
    this->fillGraph();

    // Vetor para fazer a representação vetorial criado com o número de arestas.
    int size = (this->order * (this->order - 1)) / 2;
    this->binaryVector = new bool[size];

    // Vetor compactado para guardar apenas os indices das arestas existentes que estão representadas com valor 1 no binaryVector
    this->indexVector = new int[this->numEdges];
}

Graph::~Graph()
{
    for (int i = 0; i < this->order; i++)
    {
        delete[] matrix[i];
        delete[] matrixConverted[i];
    }

    delete[] matrix;
    delete[] matrixConverted;
    delete binaryVector;
    delete indexVector;
}

int Graph::getOrder()
{
    return this->order;
}

void Graph::fillGraph()
{

    for (int i = 0; i < this->order; i++)
    {
        for (int j = i + 1; j < this->order; j++)
        {

            this->matrix[i][j] = intRandom(0, 1, this->gen) == 1;

            if (this->matrix[i][j] == 1)
                this->numEdges += 1;

            this->matrix[j][i] = this->matrix[i][j]; // grafo não direcionado
            this->matrix[i][i] = 0;                  // sem self-loop
        }
    }
}

void Graph::printGraphCmd()
{

    for (int i = 0; i < this->order; i++)
    {
        for (int j = 0; j < this->order; j++)
        {
            cout << this->matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::printGraphTxt(string pathname)
{
    ofstream file(pathname);

    if (file.is_open())
    {
        file << "graph grafo {" << endl;

        for (int i = 0; i < this->order; i++)
        {
            for (int j = 0; j < this->order; j++)
            {
                if (i < j && this->matrix[i][j] == 1)
                    file << "\t" << i << " -- " << j << ";" << endl;
            }
        }

        file << "}";
    }
    else
    {
        cerr << "Exceção durante abertura/escrita no arquivo" << endl;
    }

    file.close();
}

void Graph::printBinaryVector()
{
    cout << "Representação vetorial da matriz: " << endl;
    int size = (this->order * (this->order - 1)) / 2;
    for (int k = 0; k < size; k++)
    {
        cout << this->binaryVector[k] << "\t";
    }
    cout << endl;
}

void Graph::printIndexVector()
{
    cout << "Representação com vetor de indices (endereçamento indireto) do vetor binário: " << endl;
    for (int k = 0; k < this->numEdges; k++)
    {
        cout << this->indexVector[k] << "\t";
    }
    cout << endl;
}

void Graph::printMatrixConvertedCmd()
{
    for (int i = 0; i < this->order; i++)
    {
        for (int j = 0; j < this->order; j++)
        {
            cout << this->matrixConverted[i][j] << "\t";
        }
        cout << endl;
    }
}

int Graph::getNumEdges()
{
    return this->numEdges;
}

/**
 * Converte a representação do grafo em matriz de adjacência para vetor binário
 * 
 * @return vetor binário
*/
bool *Graph::matrixToBinaryVector()
{
    int k = 0;
    for (int i = 0; i < this->order; i++)
    {
        for (int j = i + 1; j < this->order; j++)
        {
            // cout << this->matrix[i][j] << "\t";
            this->binaryVector[k++] = this->matrix[i][j];
        }
    }
    cout << endl;
    return this->binaryVector;
}

/**
 * Converte o vetor binário para vetor de índices
 * cada posição guarda o índice do valor `1` do vetor binário
 * 
 * @return vetor de índices
*/
int *Graph::binaryVectorToIndexVector()
{

    int size = (this->order * (this->order - 1)) / 2;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        this->indexVector[i] = -1;
        if (this->binaryVector[i] == 1)
        {
            this->indexVector[k++] = i;
        }
    }

    return this->indexVector;
}

/**
 * Converte o vetor de índices para matriz de adjacência
 * 
 * @return a matriz de adjacênciia a partir do vetor de índices
*/
bool **Graph::indexVectorToMatrix()
{
    cout << "Convertendo vetor de indices para matriz..." << endl;
    cout << "Conversão vetor de índices para binário: " << endl;
    int size = (this->order * (this->order - 1)) / 2;
    bool *tempBinaryVector = new bool[size];

    int k = 0;
    for (int i = 0; i < size; i++)
    {
        tempBinaryVector[i] = 0;
        if (i == this->indexVector[k])
        {
            tempBinaryVector[i] = 1;
            k++;
        }
        cout << tempBinaryVector[i] << "\t";
    }
    cout << endl;

    k = 0;
    for (int i = 0; i < this->order; i++)
    {
        for (int j = i + 1; j < this->order; j++)
        {
            this->matrixConverted[i][j] = tempBinaryVector[k];
            this->matrixConverted[j][i] = tempBinaryVector[k++];
            this->matrixConverted[i][i] = 0;
        }
    }
    return this->matrixConverted;
}


/**
 * Realiza a operação de merge entre dois vetores de índices
 * O vetor retornado irá coonter os índices que existem em `v1` ou `v2`
 * 
 * @param v1 vetor de índices 1
 * @param s1 tamanho do vetor de índices 1
 * @param v2 vetor de índices 2
 * @param s2 tamanho do vetor de índices 2
 * @return um vetor com os índices que existem em `v1` ou em `v2`
*/
int *Graph::merge(int *v1, int s1, int *v2, int s2)
{
    int *v3 = new int[s1 + s2];
    int k1 = 0, k2 = 0;
    int min = s1 < s2 ? s1 : s2;

    int i;
    for (i = 0; k1 < s1 && k2 < s2; i++)
    {
        if (v1[k1] == v2[k2])
        {
            v3[i] = v1[k1];
            k1++;
            k2++;
        }
        else if (v1[k1] < v2[k2])
        {
            v3[i] = v1[k1++];
        }
        else
        {
            v3[i] = v2[k2++];
        }
    }

    // copiar o restante de v1
    for (; k1 < s1; k1++)
    {
        v3[i++] = v1[k1];
    }

    // copiar o restante de v2
    for (; k2 < s2; k2++)
    {
        v3[i++] = v2[k2];
    }

    return v3;
}

/**
 * Realiza a operação de match entre dois vetores de índices
 * O vetor retornado irá conter apenas os índices quue existem em `v1`e `v2`
 * 
 * @param v1 vetor de índices 1
 * @param s1 tamanho do vetor de índices 1
 * @param v2 vetor de índices 2
 * @param s2 tamanho do vetor de índices 2
 * @return um vetor com apenas os índices que existem em `v1` e `v2`
*/
int *Graph::match(int *v1, int s1, int *v2, int s2)
{
    int k1 = 0, k2 = 0, k3 = 0;
    int min = s1 < s2 ? s1 : s2;
    int *v3 = new int[min];
    for (int i = 0; k1 < s1 && k2 < s2; i++)
    {
        cout << "i: " << i;
        cout << "\tk1: " << k1;
        cout << "\tk2: " << k2 << endl;

        if (v1[k1] == v2[k2])
        {
            v3[k3++] = v1[k1++];
            k2++;
        }
        else if (v1[k1] < v2[k2])
        {
            k1++;
        }
        else
        {
            k2++;
        }
    }

    return v3;
}

/**
 * Converte (i, j) em um índice único analiticamente
 */
int Graph::mapMatrixToIndexVectorAnalytic(int i, int j){
    int f_i_n = (2 * this->getOrder() - i - 1) * (i) / 2;
    return (j - i - 1) + f_i_n; //correct
}


int Graph::fRec(int i, int j, int aux){
    if(aux == 0)
        return (j - i - 1);
    else
        return (this->getOrder() - aux) + fRec(i, j, aux-1); 
}


/**
 * Converte (i, j) em um índice único recursivamente
 */
int Graph::mapMatrixToIndexVectorRecursive(int i, int j){
    return fRec(i, j, i);  
}


/**
 * Converte (i, j) em um índice único iterativamente
 */
int Graph::mapMatrixToIndexVectorIteration(int i, int j){
    
    int cont = 0;
    for(int aux = i; aux >= 0; aux--){
        if(aux != 0)
            cont += this->getOrder() - aux;
        else
            cont += j - i - 1;
    }

    return cont;
}

int Graph::findIIterative(int k){
    //Rever e entender essas contas
    int sn = this->getOrder() - 1;
    int termo = sn - 1;

    int i = 0;
    while(k >= sn){
        sn = sn + termo;
        termo = termo - 1;
        i = i + 1;
    }

    return i;
}

int Graph::findIAnalytic(int k){
    int n = this->getOrder();
    int valLeft = (2*n - 1);
    int insideSquareRoot = pow(2*n - 1, 2) - 8*k; 

    int sqrtVal = pellSquareRoot(insideSquareRoot);
    
    int i = (valLeft - sqrtVal) / 2;

    if(k < i * (2 * n - i - 1) / 2 )
        i -= 1;

    return i;
}

int Graph::findJAnalytic(int i, int k){
    int n = this->getOrder();
    
    int partial = i * (2*n - i - 1) / 2 - i - 1;
    return k - partial;
}

int Graph::findJIterative(int i, int k){
    int cont = 0;
    for(int aux = i; aux >= 0; aux--){
        if(aux != 0)
            cont -= this->getOrder() - aux;
        else
            cont += k + i + 1;
    }

    return cont;
}

/**
 * Converte k em (i, j) iterativamente
 */
tuple<int, int> Graph::mapIndexVectorToMatrixAnalytic(int k){
    int i = findIAnalytic(k);
    int j = findJAnalytic(i, k);

    return make_tuple(i, j);
}