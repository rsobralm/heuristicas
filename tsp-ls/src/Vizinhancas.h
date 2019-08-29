#ifndef Vizinhancas_H
#define Vizinhancas_H

#include <iostream>
#include "Funcoes.h"

using namespace std;

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

//double custoTotal(vector<int> &solucao);
#endif