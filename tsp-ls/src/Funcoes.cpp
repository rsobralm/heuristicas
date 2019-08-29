
#include "Funcoes.h"
#include "CustoIn.h"


void printData(int dimension, double**matrizAdj)
{
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++)
  {
    for (size_t j = 1; j <= dimension; j++)
    {
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}

void printSolution(vector<int> anyVector)
{ // printa um vetor qualquer
  vector<int>::iterator v = anyVector.begin();
  cout << "\n";
  while (v != anyVector.end())
  {
    cout << *v << " ";
    v++;
  }
}


double custoTotal(vector<int> &solucao, double**matrizAdj)
{ // explora a matriz e retorna o custo de uma solucao
  double custo = 0;
  for (int i = 0, j = 1; i < solucao.size() - 1; i++, j++)
  {
    custo = custo + matrizAdj[solucao[i]][solucao[j]];
  }
  return custo;
}



double cpuTime()
{
  static struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return ((double)usage.ru_utime.tv_sec) + (((double)usage.ru_utime.tv_usec) / ((double)1000000));
}

void printTime(double &tempo_construction, double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3 )
{
  cout << "Tempo medio de execucao da SI: " << (tempo_construction) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao da troca: " << (tempo_swap) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt: " << (tempo_reinsertion) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt2: " << (tempo_orOpt2) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do Or-opt3: " << (tempo_orOpt3) << " (s)";
  cout << "\n"
       << "Tempo medio de execucao do 2-opt: " << (tempo_2opt) << " (s)";

  cout << "\n\n";
}

void organizaMatriz(int dimension, double** matrizAdj ,vector<vector<int>> &matrizOrg)
{
      struct istorado
    {
        int contador;
        double **matrizAdj;
        bool operator()(const int& a, const int& b) const
        {
            return matrizAdj[contador][a] <  matrizAdj[contador][b]; 
        }
    }tora;

    tora.contador = 1;
    tora.matrizAdj = matrizAdj;

  vector<int> optimal;

  for (int i = 1; i <= dimension; i++)
  {
    optimal.push_back(i);
  }

  for (int i = 0; i < dimension; i++)
  {
    matrizOrg.push_back(optimal);
    sort(matrizOrg[i].begin(), matrizOrg[i].end(), tora);
    tora.contador++;
  }
}
