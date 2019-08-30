
#include "RVND.h"

void rvnd(vector<int> &solution, double &cost, int n, double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
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
      swap(solution, auxCost, n, swapTime, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      swapTime += (end - begin);
    }
      break;

    case 1:
    {
      double begin = cpuTime();
      reInsertion(solution, auxCost, n, reinsertionTime, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      reinsertionTime += (end - begin);
    }
    break;

    case 2:
    {
      double begin = cpuTime();
      twoOptN(solution, auxCost, n, twoOptTime, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      twoOptTime += (end - begin);
    }
      break;

    case 3:
    {
      double begin = cpuTime();
      orOptN(solution, auxCost, 2, n, orOpt2Time, positionList, adjMatrix, arrangedMatrix);
      double end = cpuTime();
      orOpt2Time += (end - begin);
    }
      break;

    case 4:
    {
      double begin = cpuTime();
      orOptN(solution, auxCost, 3, n, orOpt3Time, positionList, adjMatrix, arrangedMatrix);
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