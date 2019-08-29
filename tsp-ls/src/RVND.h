#ifndef RVND_H
#define RVND_H

#include "Vizinhancas.h"

using namespace std;

void rvnd(vector<int> &solucao, double &custo, int dimension,  double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3,
vector<int> &solucaoInvertida, double** matrizAdj, vector<vector<int>> &matrizOrg);

#endif