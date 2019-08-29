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


using namespace std;


int main(int argc, char **argv)
{

  double **matrizAdj;  // matriz de adjacencia
  double **matrizDist; // matriz reorganizada;
  int dimension;       // quantidade total de vertices
  vector<int> cidades;
  vector<int> solucaum;
  vector<int> candidatos;
  vector<vector<int>> matrizOrg;
  vector<int> solucaoInvertida;

  std::chrono::time_point<std::chrono::system_clock> temp1, temp2;
  double totalTempo = 0;

  double tempo_construction = 0;
  double tempo_swap = 0;
  double tempo_reinsertion = 0;
  double tempo_2opt = 0;
  double tempo_orOpt2 = 0;
  double tempo_orOpt3 = 0;


  double somaTempos;
  double somaValores;
  std::string arg1(argv[1]);
  cout << arg1 << endl;
  double valor;
  int i_max = 50;
  int i_ils;
  readData(argc, argv, &dimension, &matrizAdj);
  vector<int> temporarioInvertido(dimension + 1);
  solucaoInvertida = temporarioInvertido;
  srand((unsigned)time(0));

  if (dimension >= 150)
  {
    i_ils = dimension / 2;
  }
  else
  {
    i_ils = dimension;
  }

  double before = cpuTime();

  organizaMatriz(dimension, matrizAdj, matrizOrg);

  cidades = gils_rvnd(i_max, i_ils, dimension, tempo_construction, tempo_swap, tempo_reinsertion, tempo_2opt, tempo_orOpt2, tempo_orOpt3, solucaoInvertida, matrizAdj, matrizOrg);

  printSolution(cidades);

  valor = custoTotal(cidades, matrizAdj);
  cout << "\n\ncusto: " << custoTotal(cidades, matrizAdj) <<"\n\n";
  printTime(tempo_construction, tempo_swap, tempo_reinsertion, tempo_2opt, tempo_orOpt2, tempo_orOpt3);

  double after = cpuTime();
  
  double tempo_total = after - before;
  cout << "Tempo de Execucao: " << tempo_total << endl;
  
  return 0;
}

