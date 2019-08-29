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

  /*struct Compara
  {
    int contador;
    double **matrizAdj;
 
    bool Compare(const int &a, const int &b){
       return (matrizAdj[contador][a] < matrizAdj[contador][b]);
       }

    void azar(int i, vector<vector<int>> &matrizOrg){
        sort(matrizOrg[i].begin(), matrizOrg[i].end(),Compare);
    }
  }comparacao;*/


  struct istorado
{
    int contador;
    double **matrizAdj;
    bool operator()(const int& a, const int& b) const
    {
        return matrizAdj[contador][a] <  matrizAdj[contador][b]; 
    }
}tora;


bool compMatriz(const int &a, const int &b, double **matrizAdj, int contador);

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

  int contador = 1;

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

  //organizaMatriz();

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
    sort(matrizOrg[i].begin(), matrizOrg[i].end(),tora);
    //comparacao.azar(i, matrizOrg);
    tora.contador++;
  }

  /*for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      cout << matrizOrg[i][j] << " ";
    }
    cout << endl;
  }*/
    /*double custo = 0;
    candidatos = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,1};
    cout << matrizOrg[7][13] <<"\n";
    printSolution(candidatos);
    twoOptN(candidatos, custo);
    printSolution(candidatos);*/
 
  //rvnd(cidades);
  //printSolution(cidades);
  //printSolution(candidatos);
  //perturb(candidatos);

  cidades = gils_rvnd(i_max, i_ils, dimension, tempo_construction, tempo_swap, tempo_reinsertion, tempo_2opt, tempo_orOpt2, tempo_orOpt3, solucaoInvertida, matrizAdj, matrizOrg);

  printSolution(cidades);

  valor = custoTotal(cidades, matrizAdj);
  cout << "\n\ncusto: " << custoTotal(cidades, matrizAdj) <<"\n\n";
  printTime(tempo_construction, tempo_swap, tempo_reinsertion, tempo_2opt, tempo_orOpt2, tempo_orOpt3);

  double after = cpuTime();
  //cidades = construction(0.5);
  //swap(cidades);
  //printData();
  double tempo_total = after - before;
  cout << "Tempo de Execucao: " << tempo_total << endl;
  // somaTempos += tempo_total;
  // somaValores += valor;
  //printTime();
  //cout << "Valor Medio da Solucao: " << (somaValores/10) << endl;
  //cout << "Tempo Medio de Execucao: " << (somaTempos/10) << " (s)" << endl;
  //printTime();
  return 0;
}


/*bool compMatriz(const int &a, const int &b) // comparação dos custos utilizada para ordenar os objetos
{
  return matrizAdj[contador][a] < matrizAdj[contador][b];
}*/


