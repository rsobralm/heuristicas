#include "readData.h"
#include "CustoIn.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <chrono>
#include <sys/timeb.h>
#include <sys/resource.h>

#include "GILSRVND.h"
#include "Funcoes.h"
#include "RVND.h"
#include "Construcao.h"
#include "Perturbacao.h"
#include "MinSpanningTree.h"
#include "CandidateList.h"

using namespace std;


int main(int argc, char **argv)
{

  double **adjMatrix;  // matriz de adjacencia
  double **matrizDist; // matriz reorganizada;
  int n;       // quantidade total de vertices
  vector<int> cidades;
  vector<int> solucaum;
  vector<int> candidatos;
  vector<vector<int>> orgMatrix;
  vector<int> positionList;

  std::chrono::time_point<std::chrono::system_clock> temp1, temp2;
  double execTime = 0;
  double somacustos = 0;
  double constructionTime = 0;
  double swapTime = 0;
  double reinsertionTime = 0;
  double TwoOptTime = 0;
  double orOpt2Time = 0;
  double orOpt3Time = 0;


  std::string arg1(argv[1]);
  cout << arg1 << endl;
  int i_max = 50;
  int i_ils;
  readData(argc, argv, &n, &adjMatrix);
  vector<int> tempPositionList(n + 1);
  positionList = tempPositionList;
  srand((unsigned)time(0));

  if (n >= 150)
  {
    i_ils = n / 2;
  }
  else
  {
    i_ils = n;
  }

  for(int i =0; i < 10; i++){
  double before = cpuTime();

  //organizaMatriz(n, adjMatrix, orgMatrix);
  
  generateCandidateList(orgMatrix, adjMatrix, n);


  cidades = gils_rvnd(i_max, i_ils, n, constructionTime, swapTime, reinsertionTime, TwoOptTime, orOpt2Time, orOpt3Time, positionList, adjMatrix, orgMatrix);

  //printSolution(cidades);
  somacustos += totalCost(cidades, adjMatrix);

  //cout << "\n\ncusto: " << totalCost(cidades, adjMatrix) <<"\n\n";
  //printTime(constructionTime, swapTime, reinsertionTime, TwoOptTime, orOpt2Time, orOpt3Time);

  double after = cpuTime();
  execTime += (after - before);
  }

  cout << "custo: " << (somacustos/10) << " \n\n";
  cout << "Tempo medio de execucao da SI: " << (constructionTime/10) << " (s)";
  cout << "\n" << "Tempo medio de execucao da troca: " << (swapTime/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt: " << (reinsertionTime/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt2: " << (orOpt2Time/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt3: " << (orOpt3Time/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do 2-opt: " << (TwoOptTime/10)<< " (s)";

  cout << "\n\n";

  cout << "Tempo de Execucao: " << (execTime/10) << endl;
  
  return 0;
}

