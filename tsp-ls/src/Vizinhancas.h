#ifndef Vizinhancas_H
#define Vizinhancas_H

#include <iostream>
#include "Funcoes.h"

using namespace std;

void swap(vector<int> &solution, double &cost, int n, double &swapTime, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &arrangedMatrix);
inline double calculaDeltaSwap(int i, int j, vector<int> &s, double** adjMatrix);

void reInsertion(vector<int> &solution, double &cost,int n, double &reinsertionTime, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &arrangedMatrix);
inline double calculaDeltaReInsertion(int i, int j, vector<int> &s, double**adjMatrix);

void twoOptN(vector<int> &solution, double &cost,int n, double &twoOptTime, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);
inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double**adjMatrix);

void orOpt2(vector<int> &solution, double &cost,int n, double &orOpt2Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);
inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double**adjMatrix);

void orOpt3(vector<int> &solution, double &cost,int n, double &orOpt3Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);
inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double**adjMatrix);

void orOptN(vector<int> &v, double &cost, int quantidade, int n, double &orOpt2Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);

#endif