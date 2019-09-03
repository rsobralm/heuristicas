#ifndef Vizinhancas_H
#define Vizinhancas_H

#include <iostream>
#include "Funcoes.h"

using namespace std;

void swap(int ils, int maxIter, vector<int> &melhoras, double &totalmelhoras,vector<int> &solution, double &cost, int n, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &arrangedMatrix);

inline double calculaDeltaSwap(int i, int j, vector<int> &s, double** adjMatrix);

void reInsertion(int ils, int maxIter, vector<int> &melhoras, double &totalmelhoras,vector<int> &solution, double &cost,int n, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &arrangedMatrix);

inline double calculaDeltaReInsertion(int i, int j, vector<int> &s, double**adjMatrix);

void twoOptN(int ils, int maxIter, vector<int> &melhoras, double &totalmelhoras, vector<int> &solution, double &cost,int n, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);

inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double**adjMatrix);

inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double**adjMatrix);

inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double**adjMatrix);

void orOptN(int ils, int maxIter, vector<int> &melhoras, double &totalmelhoras, vector<int> &v, double &cost, int quantidade, int n, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &arrangedMatrix);

#endif