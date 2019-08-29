
#include "Vizinhancas.h"
#include "Funcoes.h"

using namespace std;

//Faz a troca de posição entre dois nós.
void swap(vector<int> &solution, double &cost, int n, double &swapTime, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{

  double swapBegin = cpuTime();
  vector<int> s = solution;
  double delta;
  double betterDelta = std::numeric_limits<double>::infinity();

  int posI = -1, posJ = -1;                             // guarda as posições para realizar a operação
  for (int i = 2; i < solution.size() - 2; i++)           // exclui da operação a ultima e penultima posição do vetor
  {  
    for (int j = 1; j <= 20; j++)                           // pega os 20 vizinhos mais proximos
    {
      
      int node = arrangedMatrix[solution[i] - 1][j];
      int nodePos = positionList[node];

      if (node != 1 && i != nodePos)
      {

        for (int k = -1; k <= 1; k++)
        {
          if (i + k < nodePos)
            delta = calculaDeltaSwap(i + k, nodePos, s, adjMatrix);
          else
            delta = calculaDeltaSwap(nodePos, i + k, s, adjMatrix);

          if (delta < 0)
          {
            if (delta < betterDelta)
            {
              betterDelta = delta;
              posI = i + k;
              posJ = nodePos;
            }
          }
        }
      }
    }
  }
  //////// REINSERINDO NAS PONTAS DA solution;
  for (int l = 1; l <= 2; l++)
  {
    int i = 1;                                          //Extremidade inicial da solução
    if (l == 2)                                         //Extremidade final da solucção
    {
      i = n - 1;
    }
    for (int j = 1; j <= 20; j++)                       // pega os 20 vizinhos mais proximos
    { 
      
      int node = arrangedMatrix[solution[i] - 1][j];
      int nodePos = positionList[node];
      if (node != 1 && i != nodePos)
      {
        if (i == 1)                                     //Extremidade inicial da solução
        { 
          for (int k = 0; k <= 1; k++)
          {
            if (i + k < nodePos)
              delta = calculaDeltaSwap(i + k, nodePos, s, adjMatrix);
            else
              delta = calculaDeltaSwap(nodePos, i + k, s, adjMatrix);
            if (delta < 0)
            {
              if (delta < betterDelta)
              {
                betterDelta = delta;
                posI = i + k;
                posJ = nodePos;
              }
            }
          }
        }
        else                                            //Extremidade final da solucção
        {
          for (int k = -1; k <= 0; k++)
          {
            if (i + k < nodePos)
              delta = calculaDeltaSwap(i + k, nodePos, s, adjMatrix);
            else
              delta = calculaDeltaSwap(nodePos, i + k, s, adjMatrix);
            if (delta < 0)
            {
              if (delta < betterDelta)
              {
                betterDelta = delta;
                posI = i + k;
                posJ = nodePos;
              }
            }
          }
        }
      }
    }
  }
  if (posI > 0)
  { // realiza a operação
    solution[posI] = s[posJ];
    solution[posJ] = s[posI];
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }
  //cout << cost << "\n";
  double swapEnd = cpuTime();
  swapTime += (swapEnd - swapBegin);
}

inline double calculaDeltaSwap(int i, int j, vector<int> &s, double **adjMatrix)
{
  double delta;
  if (i + 1 == j)
  {
    delta = adjMatrix[s[i - 1]][s[j]] + adjMatrix[s[i]][s[j + 1]] - adjMatrix[s[i - 1]][s[j - 1]] - adjMatrix[s[i + 1]][s[j + 1]];
  }
  else
  {
    delta = adjMatrix[s[i]][s[j - 1]] + adjMatrix[s[i]][s[j + 1]] + adjMatrix[s[j]][s[i - 1]] + adjMatrix[s[j]][s[i + 1]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i]][s[i + 1]] - adjMatrix[s[j]][s[j - 1]] - adjMatrix[s[j]][s[j + 1]];
  }
  //cout << "delta swap: " << delta <<endl;
  return delta;
}

// reinsere um nó em posição diferente
void reInsertion(vector<int> &solution, double &cost, int n, double &reinsertionTime, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{ 
  double reinsertionBegin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int posI = -1, posJ = -1;

  for (int i = 1; i < solution.size() - 1; i++)   // varre a solução exceto o 0 e o final
  { 
    for (int j = 1; j <= 20; j++)
    {
      int node = arrangedMatrix[solution[i] - 1][j]; //cout << "no:" << no << endl;
      
      int nodePos = positionList[node] - 1; // coloca o nó da posicão atras do vizinho mais proximo
      if (nodePos < i)
      {
        nodePos++;
      }

      if (node != 1 && i != nodePos)
      {

        //Delta para reinserção de 'i' após 'nodePos'
        delta = calculaDeltaReInsertion(i, nodePos, s, adjMatrix);

        if (delta < 0)
        {

          if (delta < betterDelta)
          {
            betterDelta = delta;
            posI = i;
            posJ = nodePos;
          }
        }

        //Delta para reinserção de 'nodePos' após 'i'
        delta = calculaDeltaReInsertion(nodePos, i, s, adjMatrix);

        if (delta < 0)
        {
          if (delta < betterDelta)
          {
            betterDelta = delta;
            posI = nodePos;
            posJ = i;
          }
        }

      }
    }
  }

  if (posI > 0)
  {

    solution.erase(solution.begin() + posI);
    solution.insert(solution.begin() + posJ, s[posI]);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double reinsertionEnd = cpuTime();
  reinsertionTime += (reinsertionEnd - reinsertionBegin);
}

inline double calculaDeltaReInsertion(int i, int j, vector<int> &s, double **adjMatrix)
{
  double delta;
  if (i <= j)
  {
    delta = adjMatrix[s[i]][s[j + 1]] + adjMatrix[s[i]][s[j]] + adjMatrix[s[i - 1]][s[i + 1]] - adjMatrix[s[j]][s[j + 1]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i]][s[i + 1]];
  }
  else
  {
    delta = adjMatrix[s[i]][s[j - 1]] + adjMatrix[s[i]][s[j]] + adjMatrix[s[i - 1]][s[i + 1]] - adjMatrix[s[j]][s[j - 1]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i]][s[i + 1]];
  }
  return delta;
}

void twoOptN(vector<int> &solution, double &cost, int n, double &twoOptTime, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{ // inverte uma subsequencia da solução

  double twoOptBegin = cpuTime();
  vector<int> s = solution;
  double delta, betterDelta = 0;
  int posI = -1, posJ;
  for (int i = 1; i < solution.size() - 1; i++)
  { // varre do primeiro ao ultimo elemento da solution
    for (int j = 1; j <= 20; j++)
    {
      int node = arrangedMatrix[solution[i] - 1][j];
      int nodePos = positionList[node];
      if (i != nodePos && node != 1)
      {
        if (nodePos > i)
        {
          delta = calculaDeltaTwoOpt(i + 1, nodePos, s, adjMatrix);
          //cout << "delta1:" << delta << endl;
          if (delta < 0)
          {
            if (delta < betterDelta)
            {
              betterDelta = delta;
              posI = i + 1;
              posJ = nodePos;
            }
          }
        }
        if (nodePos < i)
        {
          delta = calculaDeltaTwoOpt(nodePos + 1, i, s, adjMatrix);
          //cout << "delta2:" << delta << endl;
          if (delta < betterDelta)
          {
            betterDelta = delta;
            posI = nodePos + 1;
            posJ = i;
          }
        }
      }
    }
  }
  if (posI > 0)
  {
    //cout << "i:" << posI << "j:" << posJ << endl;
    for (int k = posI; k <= posJ; k++)
    { // invertendo as posições
      solution[k] = s[posJ + posI - k];
    }
    cost = cost + betterDelta;
    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }
  double twoOptEnd = cpuTime();
  twoOptTime += (twoOptEnd - twoOptBegin);
}

inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double **adjMatrix)
{
  double delta;
  if (j == (i + 1))
  {
    delta = adjMatrix[s[i - 1]][s[j]] + adjMatrix[s[i]][s[j + 1]] - adjMatrix[s[i - 1]][s[j - 1]] - adjMatrix[s[j]][s[j + 1]];
  }
  else
  {
    delta = adjMatrix[s[i - 1]][s[j]] + adjMatrix[s[i]][s[j + 1]] - adjMatrix[s[i - 1]][s[i]] - adjMatrix[s[j]][s[j + 1]];
  }
  return delta;
}

void orOpt2(vector<int> &solution, double &cost, int n, double &orOpt2Time, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{ // reinsere subsequencia de dois nós em posição diferente
  double orOpt2Begin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int posI = -1, posJ;
  for (int i = 1; i < solution.size() - 2; i++)
  {
    for (int j = 1; j < solution.size() - 3; j++)
    {
      if (i != j)
      {
        delta = calculaDeltaOrOpt2(i, j, s, adjMatrix);
        if (delta < 0)
        {
          if (delta < betterDelta)
          {
            betterDelta = delta;
            posI = i;
            posJ = j;
          }
        }
      }
    }
  }
  if (posI > 0)
  {
    solution.erase(solution.begin() + posI, solution.begin() + posI + 2);
    solution.insert(solution.begin() + posJ, &s[posI], &s[posI] + 2);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  orOpt2Time += (fimOropt2 - orOpt2Begin);
}

inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double **adjMatrix)
{
  double delta;
  if (i < j)
  {
    delta = adjMatrix[s[i - 1]][s[i + 2]] + adjMatrix[s[i]][s[j + 1]] + adjMatrix[s[i + 1]][s[j + 2]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i + 1]][s[i + 2]] - adjMatrix[s[j + 1]][s[j + 2]];
  }
  else
  {
    delta = adjMatrix[s[i]][s[j - 1]] + adjMatrix[s[i + 1]][s[j]] + adjMatrix[s[i + 2]][s[i - 1]] - adjMatrix[s[j]][s[j - 1]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i + 1]][s[i + 2]];
  }

  return delta;
}

void orOpt3(vector<int> &solution, double &cost, int n, double &orOpt3Time, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{ // reinsere subsequencia de tres nós em posição diferente
  double orOpt3Begin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int posI = -1, posJ;

  for (int i = 1; i < solution.size() - 3; i++)
  {
    for (int j = 1; j < solution.size() - 4; j++)
    {
      if (i != j)
      {
        delta = calculaDeltaOrOpt3(i, j, s, adjMatrix);
        if (delta < 0)
        {
          if (delta < betterDelta)
          {
            betterDelta = delta;
            posI = i;
            posJ = j;
          }
        }
      }
    }
  }
  if (posI > 0)
  {
    solution.erase(solution.begin() + posI, solution.begin() + posI + 3);
    solution.insert(solution.begin() + posJ, &s[posI], &s[posI] + 3);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double fimOropt3 = cpuTime();
  orOpt3Time += (fimOropt3 - orOpt3Begin);
}

inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double **adjMatrix)
{
  double delta;
  if (i < j)
  {
    delta = adjMatrix[s[i - 1]][s[i + 3]] + adjMatrix[s[i]][s[j + 2]] + adjMatrix[s[i + 2]][s[j + 3]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i + 2]][s[i + 3]] - adjMatrix[s[j + 2]][s[j + 3]];
  }
  else
  {
    delta = adjMatrix[s[i]][s[j - 1]] + adjMatrix[s[i + 2]][s[j]] + adjMatrix[s[i - 1]][s[i + 3]] - adjMatrix[s[j]][s[j - 1]] - adjMatrix[s[i]][s[i - 1]] - adjMatrix[s[i + 2]][s[i + 3]];
  }

  return delta;
}

void orOptN(vector<int> &v, double &cost, int quantidade, int n, double &orOpt2Time, vector<int> &positionList, double **adjMatrix, vector<vector<int>> &arrangedMatrix)
{                         // reinsere subsequencia de dois nós em posição diferente
  double **m = adjMatrix; //diminui o tamanho da declaraçao ali embaixo
  double orOpt2Begin = cpuTime();
  vector<int> s = v;
  double betterDelta = 0;
  double delta, deltaRemove;

  int posI = -1, posJ;
  for (int i = 1; i < v.size() - quantidade; i++)
  { // or-2-op/or-3-opt precisa comecar no maximo no penultimo antes do size
    deltaRemove = m[v[i]][v[i - 1]] + m[v[i + (quantidade - 1)]][v[i + quantidade]];
    for (int j = 1; j <= 20; j++)
    { //E terminar no maximo qnt antes de size
      int node = arrangedMatrix[v[i] - 1][j];
      int nodePos = positionList[node];
      if (i != nodePos && nodePos < (v.size() - (quantidade + 1)))
      {

        if (i < nodePos)
        {
          delta = m[v[i - 1]][v[i + quantidade]] + m[v[i]][v[nodePos + (quantidade - 1)]] + m[v[i + (quantidade - 1)]][v[nodePos + quantidade]] -
                  m[v[nodePos + (quantidade - 1)]][v[nodePos + quantidade]] - deltaRemove;
        }
        else
        { //reinsercao em um indice betterDelta
          //delta = (m[v[i]][v[nodePos]] + m[v[i]][v[nodePos - 1]] + m[v[i - 1]][v[i + 1]]) -
          //        (m[v[i]][v[i - 1]] + m[v[i]][v[i + 1]] + m[v[nodePos]][v[nodePos - 1]]);

          if (quantidade == 2)
            delta = calculaDeltaOrOpt2(i, nodePos, v, adjMatrix);

          if (quantidade == 3)
            delta = calculaDeltaOrOpt3(i, nodePos, v, adjMatrix);

          //delta = (m[v[i]][v[nodePos]] + m[v[i - (quantidade - 1)]][v[nodePos - 1]] + m[v[i - quantidade]][v[i + 1]]) -
          //      (m[v[i - (quantidade - 1)]][v[i - quantidade]] + m[v[i]][v[i + 1]] + m[v[nodePos]][v[nodePos - 1]]);
        }
        if (delta <= betterDelta && abs((i - nodePos)) > quantidade)
        {
          betterDelta = delta;
          posI = i;
          posJ = nodePos;
        }
      }
    }
  }
  if (posI > 0)
  {
    v.erase(v.begin() + posI, v.begin() + posI + quantidade);
    v.insert(v.begin() + posJ, &s[posI], &s[posI] + quantidade);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[v[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  orOpt2Time += (fimOropt2 - orOpt2Begin);
}
