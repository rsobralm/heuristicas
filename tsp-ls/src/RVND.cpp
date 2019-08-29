
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
      swap(solution, auxCost, n, swapTime, positionList, adjMatrix, arrangedMatrix);
      break;

    case 1:
      reInsertion(solution, auxCost, n, reinsertionTime, positionList, adjMatrix, arrangedMatrix);
      break;

    case 2:
      twoOptN(solution, auxCost, n, twoOptTime, positionList, adjMatrix, arrangedMatrix);
      break;

    case 3:
      orOptN(solution, auxCost, 2, n, orOpt2Time, positionList, adjMatrix, arrangedMatrix);
      break;

    case 4:
      orOptN(solution, auxCost, 3, n, orOpt3Time, positionList, adjMatrix, arrangedMatrix);
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