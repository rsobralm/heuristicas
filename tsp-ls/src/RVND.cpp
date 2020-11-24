
#include "RVND.h"

void rvnd(vector<int> &solution, double &cost, int n,  double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
vector<int> &positionList, double** adjMatrix, vector<vector<int>> &orgMatrix)
{
  vector<int> s = solution;
  vector<int> nbList = {0, 1, 2, 3, 4}; // lista de estruturas
  double mCost = cost;
  int sel, pos;

  while (!nbList.empty())
  { // roda enquanto existirem estruturas de vizinhança na lista

    int k = rand() % nbList.size();

    switch (nbList[k])
    {
    case 0:
    {
      double begin = cpuTime();
      swap(solution, mCost, n, swapTime, positionList, adjMatrix, orgMatrix);
      double end = cpuTime();
      swapTime += (end - begin);
    }
      break;

    case 1:
    {
      double begin = cpuTime();
      reInsertion(solution, mCost, n, reinsertionTime, positionList, adjMatrix, orgMatrix);
      double end = cpuTime();
      reinsertionTime += (end - begin);
    }
    break;

    case 2:
    {
      double begin = cpuTime();
      twoOptN(solution, mCost, n, twoOptTime, positionList, adjMatrix, orgMatrix);
      double end = cpuTime();
      twoOptTime += (end - begin);
    }
      break;

    case 3:
    {
      double begin = cpuTime();
      orOptN(solution, mCost, 2, n, orOpt2Time, positionList, adjMatrix, orgMatrix);
      double end = cpuTime();
      orOpt2Time += (end - begin);
    }
      break;

    case 4:
    {
      double begin = cpuTime();
      orOptN(solution, mCost, 3, n, orOpt3Time, positionList, adjMatrix, orgMatrix);
      double end = cpuTime();
      orOpt3Time += (end - begin);
    }
      break;

   case 5:
    {
      double begin = cpuTime();
      fourOpt(solution, mCost, n, positionList, adjMatrix);
      double end = cpuTime();
      //fourOptTime += (end - begin);
    }
      break;
  }

    //mCost = costTotal(solution); // calcula o cost do Movimento

    if (cost > mCost)
    { // movimento melhorou o cost
      cost = mCost;
      s = solution;
    }
    else
    { // nao melhorou, exclui o movimento da lista
      solution = s;
      nbList.erase(nbList.begin() + k);
      mCost = cost;
    }
  }
}