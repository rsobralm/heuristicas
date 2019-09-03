#ifndef Funcoes_H
#define Funcoes_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/timeb.h>
#include <sys/resource.h>
#include "CustoIn.h"

extern std::vector<int> melhoras;
extern double totalmelhoras;

using namespace std;

void printData(int dimension, double **adjMatrix);
void printSolution(vector<int> anyVector);
double totalCost(vector<int> &solution, double **adjMatrix);
double cpuTime();
void printTime(double &constructionTime, double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time);
void arrangeMatrix(int dimension, double **adjMatrix, vector<vector<int>> &arrangedMatrix);
int defineMaxIterator(int n, vector<int> melhoras, double totalmelhoras);



#endif