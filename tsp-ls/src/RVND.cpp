
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
      swap(solution, mCost, n, swapTime, positionList, adjMatrix, orgMatrix);
      break;

    case 1:
    {
      //temp1 = std::chrono::system_clock::now();
      reInsertion(solution, mCost, n, reinsertionTime, positionList, adjMatrix, orgMatrix);
      //temp2 = std::chrono::system_clock::now();
      //totalTempo = totalTempo + std::chrono::duration_cast<std::chrono::microseconds>(temp2 - temp1).count();
    }
    break;

    case 2:
      twoOptN(solution, mCost, n, twoOptTime, positionList, adjMatrix, orgMatrix);
      break;

    case 3:
      orOptN(solution, mCost, 2, n, orOpt2Time, positionList, adjMatrix, orgMatrix);
      break;

    case 4:
      orOptN(solution, mCost, 3, n, orOpt3Time, positionList, adjMatrix, orgMatrix);
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