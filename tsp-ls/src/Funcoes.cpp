
#include "Funcoes.h"
#include "CustoIn.h"

//Printa a matriz de adjacência.
void printData(int dimension, double **adjMatrix)
{
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++)
  {
    for (size_t j = 1; j <= dimension; j++)
    {
      cout << adjMatrix[i][j] << " ";
    }
    cout << endl;
  }
}

//Printa um vetor qualquer;
void printSolution(vector<int> anyVector)
{
  vector<int>::iterator v = anyVector.begin();
  cout << "\n";
  while (v != anyVector.end())
  {
    cout << *v << " ";
    v++;
  }
}

//Itera sobre a solução e retorna seu cost baseado na matriz de adjacência.
double totalCost(vector<int> &solution, double **adjMatrix)
{
  double cost = 0;
  for (int i = 0, j = 1; i < solution.size() - 1; i++, j++)
  {
    cost = cost + adjMatrix[solution[i]][solution[j]];
  }
  return cost;
}


double cpuTime()
{
  static struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return ((double)usage.ru_utime.tv_sec) + (((double)usage.ru_utime.tv_usec) / ((double)1000000));
}


void printTime(double &constructionTime, double &swapTime, double &reinsertionTime, double &twoOptTime, double &orOpt2Time, double &orOpt3Time)
{
  cout << "Tempo medio de execucao da SI: " << (constructionTime) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao da troca: " << (swapTime) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt: " << (reinsertionTime) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt2: " << (orOpt2Time) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt3: " << (orOpt3Time) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do 2-opt: " << (twoOptTime) << " (s)";

  cout << "\n\n";
}

//Retorna uma matriz em que toda linha possui nós ordenados em relação a sua distância ao elemento da primeira coluna.
void arrangeMatrix(int dimension, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{
  struct istorado
  {
    int counter;
    double **adjMatrix;
    bool operator()(const int &a, const int &b) const
    {
      return adjMatrix[counter][a] < adjMatrix[counter][b];
    }
  } tora;

  tora.counter = 1;
  tora.adjMatrix = adjMatrix;

  vector<int> optimal;

  for (int i = 1; i <= dimension; i++)
  {
    optimal.push_back(i);
  }

  for (int i = 0; i < dimension; i++)
  {
    arrangedMatrix.push_back(optimal);
    sort(arrangedMatrix[i].begin(), arrangedMatrix[i].end(), tora);
    tora.counter++;
  }
}