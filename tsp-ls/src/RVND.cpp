
#include "RVND.h"

void rvnd(vector<int> &solucao, double &custo, int dimension,  double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3,
vector<int> &solucaoInvertida, double** matrizAdj, vector<vector<int>> &matrizOrg)
{
  vector<int> s = solucao;
  vector<int> nLista = {0, 1, 2, 3, 4}; // lista de estruturas
  double custoMod = custo;
  int sel, pos;

  while (!nLista.empty())
  { // roda enquanto existirem estruturas de vizinhança na lista

    int k = rand() % nLista.size();

    switch (nLista[k])
    {
    case 0:
      swap(solucao, custoMod, dimension, tempo_swap, solucaoInvertida, matrizAdj, matrizOrg);
      break;

    case 1:
    {
      //temp1 = std::chrono::system_clock::now();
      reInsertion(solucao, custoMod, dimension, tempo_reinsertion, solucaoInvertida, matrizAdj, matrizOrg);
      //temp2 = std::chrono::system_clock::now();
      //totalTempo = totalTempo + std::chrono::duration_cast<std::chrono::microseconds>(temp2 - temp1).count();
    }
    break;

    case 2:
      twoOptN(solucao, custoMod, dimension, tempo_2opt, solucaoInvertida, matrizAdj, matrizOrg);
      break;

    case 3:
      orOptN(solucao, custoMod, 2, dimension, tempo_orOpt2, solucaoInvertida, matrizAdj, matrizOrg);
      break;

    case 4:
      orOptN(solucao, custoMod, 3, dimension, tempo_orOpt3, solucaoInvertida, matrizAdj, matrizOrg);
      break;
    }

    //custoMod = custoTotal(solucao); // calcula o custo do Movimento

    if (custo > custoMod)
    { // movimento melhorou o custo
      custo = custoMod;
      s = solucao;
    }
    else
    { // nao melhorou, exclui o movimento da lista
      solucao = s;
      nLista.erase(nLista.begin() + k);
      custoMod = custo;
    }
  }
}