
#include "Construcao.h"
#include "Funcoes.h"

vector<int> construction(double alpha, double &cost, int n, double &constructionTime, vector<int> &positionList, double **adjMatrix)
{

  double begin = cpuTime(); 

  vector<int> s = {1, 1}; // lista de cidades da solução inicial
  vector<int> candidateList;
  for (int i = 2; i <= n; i++)
  {
    candidateList.push_back(i); // insere todos os nós na lista de candidatos
  }

  for (int j = 0; j < 3; j++)
  { // tamamho subsequencia inicial
    int k = rand() % candidateList.size();
    s.insert(s.begin() + 1, candidateList[k]);        // adiciona cidade aleatoria a solução
    candidateList.erase(candidateList.begin() + k); // apaga da lista de candidatos oq ja foi pra solução
  }

  vector<CustoIn> insertionCosts = getCost(candidateList, s, adjMatrix); // calcula os cost de inserção dos candidatos
  std::sort(insertionCosts.begin(), insertionCosts.end(), comp);     // ordena de forma crescente de acordo com os custos

  int sel;
  while (!candidateList.empty())
  {
    if (alpha == 0)
    {
      sel = 0;
    }
    else
    {
      sel = rand() % ((int)std::floor(alpha * (insertionCosts.size() - 1)) + 1); // escolhe um nó dentro de uma faixa definida por alpha
    }

    //cout << "sel: " << sel << endl;

    s.insert(s.begin() + insertionCosts[sel].edgeOut + 1, insertionCosts[sel].nodeIn); // insere o nó na solucao

    for (int i = 0; i < candidateList.size(); i++)
    {
      if (candidateList[i] == insertionCosts[sel].nodeIn)
        candidateList.erase(candidateList.begin() + i); // exclui o nó da lista de candidatos
    }

    insertionCosts.erase(insertionCosts.begin(), insertionCosts.begin() + insertionCosts.size()); // exclui o nó da lista de custos
    insertionCosts = getCost(candidateList, s, adjMatrix);                                            // calcula os novos custos de inserção
    std::sort(insertionCosts.begin(), insertionCosts.end(), comp);                                // ordena os custos
  }

  for (int i = 0; i < positionList.size(); i++)
  {
    positionList[s[i]] = i;
  }

  /* cout << "\nNormal: ";
  for(int i = 0; i < s.size(); i++){
    cout << s[i] << " "; 
  }

  cout << "\nInvertida: ";
  for(int i = 0; i < positionList.size(); i++){
    cout << positionList[i] << " "; 
  } */

  double end = cpuTime();
  constructionTime += (end- begin);

  cost = totalCost(s, adjMatrix);
  return s;
}

vector<CustoIn> getCost(vector<int> candidateList, vector<int> &s, double **adjMatrix)
{
  vector<CustoIn> insertionCosts((s.size() - 1) * candidateList.size());
  for (int i = 0, j = 1, l = 0; i < s.size() - 1; i++, j++)
  {
    for (auto k : candidateList)
    {
      insertionCosts[l].cost = adjMatrix[s[i]][k] + adjMatrix[s[j]][k] - adjMatrix[s[i]][s[j]]; // cost
      insertionCosts[l].nodeIn = k;                                                                // nó inserido
      insertionCosts[l].edgeOut = i;                                                           // posicao de inserção;
      l++;
    }
  }

  return insertionCosts;
}

bool comp(const CustoIn &a, const CustoIn &b) // comparação dos custos utilizada para ordenar os objetos
{
  return a.cost < b.cost;
}