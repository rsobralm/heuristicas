#ifndef Vizinhancas_H
#define Vizinhancas_H

#include <iostream>
#include "Funcoes.h"

using namespace std;

struct FourOptMoveData
{
  int x1, x2;
  int i1, j1;
  int i2, j2;
  double costVar;
};

struct phiData
{
  int i, j;
  double cost;
};

void swap(vector<int> &solucao, double &custo,int dimension, double &tempo_swap, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);
double calculaDeltaSwap(int i, int j, vector<int> &s, double**matrizAdj);
void reInsertion(vector<int> &solucao, double &custo,int dimension, double &tempo_reinsertion, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);
double calculaDeltaReInsertion(int i, int j, vector<int> &s, double**matrizAdj);
void twoOptN(vector<int> &solucao, double &custo,int dimension, double &tempo_2opt, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);
double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double**matrizAdj);
void orOpt2(vector<int> &solucao, double &custo, int quantidade, int dimension, double &tempo_orOpt2, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);
double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double**matrizAdj);
void orOpt3(vector<int> &solucao, double &custo,int dimension, double &tempo_orOpt3, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);
double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double**matrizAdj);
void orOptN(vector<int> &solucao, double &custo, int quantidade, int dimension, double &tempo_orOpt2, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg);


void initializePhiMatrix(int n);
void movefourOpt(vector<int> &s, double &cost, FourOptMoveData d);
void fourOpt(vector<int> &s, double &cost, int dimension, vector<int> &solucaoInvertida, double**matrizAdj);
double deltaX(vector<int> &s, int x, int i, int j, double**matrizAdj);
#endif