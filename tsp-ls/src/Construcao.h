#ifndef Construcao_H
#define Construcao_H

#include "CustoIn.h"
#include <vector>
#include "Funcoes.h"
#include <cmath>

using namespace std;

vector<int> construction(double alpha, double &cost, int n, double &constructionTime, vector<int> &positionList, double **adjMatrix);
vector<CustoIn> getCost(vector<int> candidateList, vector<int> &s, double **adjMatrix);
bool comp(const CustoIn &a, const CustoIn &b);

#endif