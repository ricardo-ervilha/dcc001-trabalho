#ifndef UTILS_H
#define UTILS_H

#include <random>

using namespace std;

/**
 *
 * @param min
 * @param max
 * @param gen
 * @return
 */
double doubleRandom(double min, double max, mt19937 *gen)
{
    uniform_real_distribution<double> distributionDouble(min, max); // distribuição uniforme entre min e max
    return distributionDouble(*gen);
}

/**
 *
 * @param min
 * @param max
 * @param gen
 * @return
 */
int intRandom(int min, int max, mt19937 *gen)
{
    uniform_int_distribution<int> distributionInt(min, max); // distribuição uniforme entre min e max
    return distributionInt(*gen);
}

/**
 *
 * @param m
 * @return
 */
int pellSquareRoot(int m){
    int n = 0;
    int i = 1;
    while (m >= i){
        m = m - i;
        i = i + 2;
        n = n + 1;
    }

    return n;
}

#endif