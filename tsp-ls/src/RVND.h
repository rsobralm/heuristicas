#ifndef RVND_H
#define RVND_H

#include "Vizinhancas.h"

using namespace std;

void rvnd(vector<int> &solution, double &cost, int n,  double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
vector<int> &positionList, double** adjMatrix, vector<vector<int>> &orgMatrix);

#endif