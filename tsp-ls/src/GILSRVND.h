#ifndef GILSRVND_H
#define GILSRVND_H

#include <vector>
#include <limits>
#include <random>
#include "RVND.h"
#include "Construcao.h"
#include "Perturbacao.h"

using namespace std;

vector<int> gils_rvnd(int iMax, int iIls, vector<int> &melhoras, double &totalmelhoras, int n, double &constructionTime , double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
vector<int> &positionList, double** adjList, vector<vector<int>> &arrangedMatrix);

#endif