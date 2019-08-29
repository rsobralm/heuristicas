#ifndef GILSRVND_H
#define GILSRVND_H

#include <vector>
#include <limits>
#include <random>
#include "RVND.h"
#include "Construcao.h"
#include "Perturbacao.h"

using namespace std;

vector<int> gils_rvnd(int i_max, int i_ils,  int dimension, double &tempo_construction , double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3,
vector<int> &solucaoInvertida, double** matrizAdj, vector<vector<int>> &matrizOrg);

#endif