#ifndef Construcao_H
#define Construcao_H

#include "CustoIn.h"
#include <vector>
#include "Funcoes.h"

using namespace std;

vector<int> construction(double alfa, double &custo, int dimension, double &tempo_construction, vector<int> &solucaoInvertida, double ** matrizAdj);
vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> &s, double **matrizAdj);
bool comp(const CustoIn &a, const CustoIn &b);

#endif