
#include "Construcao.h"
#include "Funcoes.h"
#include <cmath>

vector<int> construction(double alfa, double &custo, int dimension, double &tempo_construction, vector<int> &solucaoInvertida, double **matrizAdj)
{

  double inicioconstruction = cpuTime(); 

  vector<int> s = {1, 1}; // lista de cidades da solução inicial
  vector<int> listaCandidatos;
  for (int i = 2; i <= dimension; i++)
  {
    listaCandidatos.push_back(i); // insere todos os nós na lista de candidatos
  }

  for (int j = 0; j < 3; j++)
  { // tamamho subsequencia inicial
    int k = rand() % listaCandidatos.size();
    s.insert(s.begin() + 1, listaCandidatos[k]);        // adiciona cidade aleatoria a solução
    listaCandidatos.erase(listaCandidatos.begin() + k); // apaga da lista de candidatos oq ja foi pra solução
  }

  vector<CustoIn> custoInsertion = calculaCusto(listaCandidatos, s, matrizAdj); // calcula os custo de inserção dos candidatos
  std::sort(custoInsertion.begin(), custoInsertion.end(), comp);     // ordena de forma crescente de acordo com os custos

  int sel;
  while (!listaCandidatos.empty())
  {
    if (alfa == 0)
    {
      sel = 0;
      
    }
    else
    {
      sel = rand() % ((int)std::floor(alfa * (custoInsertion.size() - 1)) + 1); // escolhe um nó dentro de uma faixa definida por alfa
    }

    //cout << "sel: " << sel << endl;

    s.insert(s.begin() + custoInsertion[sel].arestaOut + 1, custoInsertion[sel].noIn); // insere o nó na solucao

    for (int i = 0; i < listaCandidatos.size(); i++)
    {
      if (listaCandidatos[i] == custoInsertion[sel].noIn)
        listaCandidatos.erase(listaCandidatos.begin() + i); // exclui o nó da lista de candidatos
    }

    custoInsertion.erase(custoInsertion.begin(), custoInsertion.begin() + custoInsertion.size()); // exclui o nó da lista de custos
    custoInsertion = calculaCusto(listaCandidatos, s, matrizAdj);                                            // calcula os novos custos de inserção
    std::sort(custoInsertion.begin(), custoInsertion.end(), comp);                                // ordena os custos
  }

  for (int i = 0; i < solucaoInvertida.size(); i++)
  {
    solucaoInvertida[s[i]] = i;
  }

  /* cout << "\nNormal: ";
  for(int i = 0; i < s.size(); i++){
    cout << s[i] << " "; 
  }

  cout << "\nInvertida: ";
  for(int i = 0; i < solucaoInvertida.size(); i++){
    cout << solucaoInvertida[i] << " "; 
  } */

  double fimConstruction = cpuTime();
  tempo_construction += (fimConstruction - inicioconstruction);

  custo = totalCost(s, matrizAdj);
  return s;
}

vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> &s, double **matrizAdj)
{
  vector<CustoIn> custoInsertion((s.size() - 1) * listaCandidatos.size());
  for (int i = 0, j = 1, l = 0; i < s.size() - 1; i++, j++)
  {
    for (auto k : listaCandidatos)
    {
      custoInsertion[l].custo = matrizAdj[s[i]][k] + matrizAdj[s[j]][k] - matrizAdj[s[i]][s[j]]; // custo
      custoInsertion[l].noIn = k;                                                                // nó inserido
      custoInsertion[l].arestaOut = i;                                                           // posicao de inserção;
      l++;
    }
  }

  return custoInsertion;
}

bool comp(const CustoIn &a, const CustoIn &b) // comparação dos custos utilizada para ordenar os objetos
{
  return a.custo < b.custo;
}