
#include "RVND.h"

void rvnd(int ils, int maxIter, vector<int> &melhoras, double &totalmelhoras,vector<int> &solution, double &cost, int n, double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
          vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{
  vector<int> s = solution;
  vector<int> nbList = {0, 1, 2, 3, 4}; // lista de estruturas
  double auxCost = cost;
  int sel, pos;

  while (!nbList.empty())
  { // roda enquanto existirem estruturas de vizinhança na lista

    int k = rand() % nbList.size();

    switch (nbList[k])
    {
    case 0:
    {
      double begin = cpuTime();
      swap(ils, maxIter, melhoras, totalmelhoras, solution, auxCost, n, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      swapTime += (end - begin);
    }
      break;

    case 1:
    {
      double begin = cpuTime();
      reInsertion(ils, maxIter, melhoras, totalmelhoras,solution, auxCost, n, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      reinsertionTime += (end - begin);
    }
    break;

    case 2:
    {
      double begin = cpuTime();
      twoOptN(ils, maxIter, melhoras, totalmelhoras,solution, auxCost, n, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      twoOptTime += (end - begin);
    }
      break;

    case 3:
    {
      double begin = cpuTime();
      orOptN(ils, maxIter, melhoras, totalmelhoras,solution, auxCost, 2, n, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      orOpt2Time += (end - begin);
    }
      break;

    case 4:
    {
      double begin = cpuTime();
      orOptN(ils, maxIter, melhoras, totalmelhoras,solution, auxCost, 3, n, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      orOpt3Time += (end - begin);
    }
      break;
  }

    if (cost > auxCost)   // movimento melhorou o custo
    {
      cost = auxCost;
      s = solution;
    }
    else    // nao melhorou, exclui o movimento da lista de vizinhança
    { 
      solution = s;
      nbList.erase(nbList.begin() + k);
      auxCost = cost;
    }
  }
}