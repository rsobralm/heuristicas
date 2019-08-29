#include "GILSRVND.h"

vector<int> gils_rvnd(int iMax, int iIls,  int n, double &constructionTime, double &swapTime, double &reinsertionT, double &twoOptTime, double &orOpt2Time, double &orOpt3Time,
vector<int> &positionList, double** adjMatrix, vector<vector<int>> &organizedMatrix)
{

  double finalCost = numeric_limits<double>::infinity(); // custo final
  vector<int> solution, auxSolution, bestSolution;        // s, s', s*
  double firstCost, auxCost;
  for (int i = 0; i < iMax; i++)
  {

    double alfa = (double)rand() / RAND_MAX; // gera aleatorio entre 0 e 1
    solution = construction(alfa, firstCost, n, constructionTime, positionList, adjMatrix); // constroi solucao inicial
    auxSolution = solution;
    auxCost = firstCost;
    int iter_ILS = 0;
    while (iter_ILS < iIls)
    {
      //cout << "RVND " << i << endl;
      rvnd(solution, firstCost, n, swapTime, reinsertionT, twoOptTime, orOpt2Time, orOpt3Time, positionList, adjMatrix, organizedMatrix); // explora as estruturas de vizinhança
      if (firstCost < auxCost)
      {
        auxSolution = solution;
        auxCost = firstCost;
        iter_ILS = 0;
      }
      solution = perturb(auxSolution, n, positionList); // perturba a solução evitando resultado ótimo local
      firstCost = custoTotal(solution, adjMatrix);
      iter_ILS++;
    }
    if (auxCost < finalCost)
    {

      bestSolution = auxSolution;
      finalCost = auxCost;
    }
  }
  return bestSolution; // retorna a melhor solucao
}
