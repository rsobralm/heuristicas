#ifndef Funcoes_H
#define Funcoes_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/timeb.h>
#include <sys/resource.h>
#include "CustoIn.h"

using namespace std;

void printData(int dimension, double **matrizAdj);
void printSolution(vector<int> anyVector);
double custoTotal(vector<int> &solucao, double **matrizAdj);
double cpuTime();
void printTime(double &tempo_construction, double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3 );
void organizaMatriz(int dimension, double ** matrizAdj, vector<vector<int>> &matrizOrg);
bool compMatriz(const int &a, const int &b, int &contador, double ** matrizAdj);


#endif