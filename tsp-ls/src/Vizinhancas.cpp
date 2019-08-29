
#include "Vizinhancas.h"
#include "Funcoes.h"

using namespace std;

void swap(vector<int> &solution, double &cost, int n, double &swapTime, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &orgMatrix)
{ // faz a troca de posição entre dois nós

  double swapBegin = cpuTime();
  vector<int> s = solution;
  double delta;
  double betterDelta = std::numeric_limits<double>::infinity();
  //double fs = costTotal(s);
  int pos_i = -1, pos_j = -1; // guarda as posições para realizar a operação
  for (int i = 2; i < solution.size() - 2; i++)
  { // exclui da operação a ultima e penultima posição do vetor
    //for(int j = i + 1; j < solution.size() - 1; j++){
    for (int j = 1; j <= 20; j++)
    { // pega os 5 vizinhos mais proximos
      int node = orgMatrix[solution[i] - 1][j];
      int nodePos = positionList[node];

      if (node!= 1 && i != nodePos)
      {
        //if(i <= j){ // nao repetir swap
        //cout << "i:" << i << "j:" << j << endl;
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
              pos_i = i + k;
              pos_j = nodePos;
            }
          }
        }
      }
    }
  }
  //////// REINSERINDO NAS PONTAS DA solution;
  for (int l = 1; l <= 2; l++)
  {
    int i = 1;
    if (l == 2)
    {
      i = n - 1;
    }
    for (int j = 1; j <= 20; j++)
    { // pega os 5 vizinhos mais proximos
      int node = orgMatrix[solution[i] - 1][j];
      int nodePos = positionList[node];
      if (node != 1 && i != nodePos)
      {
        //if(i <= j){ // nao repetir swap
        //cout << "i:" << i << "j:" << j << endl;
        if (i == 1)
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
                pos_i = i + k;
                pos_j = nodePos;
              }
            }
          }
        }
        else
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
                pos_i = i + k;
                pos_j = nodePos;
              }
            }
          }
        }
      }
    }
  }
  if (pos_i > 0)
  { // realiza a operação
    solution[pos_i] = s[pos_j];
    solution[pos_j] = s[pos_i];
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

inline double calculaDeltaSwap(int i, int j, vector<int> &s, double** adjMatrix)
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

void reInsertion(vector<int> &solution, double &cost,int n, double &reinsertionTime, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &orgMatrix)
{  // reinsere um nó em posição diferente
  double reinsertionBegin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int pos_i = -1, pos_j = -1;

  for (int i = 1; i < solution.size() - 1; i++)
  { // varre a solução exceto o 0 e o final
    for (int j = 1; j <= 20; j++)
    {
      int node = orgMatrix[solution[i] - 1][j];
      //cout << "no:" << no << endl;
      int nodePos = positionList[node] - 1; // coloca o nó da posicão atras do vizinho mais proximo
      if (nodePos < i)
      {
        nodePos++;
      }
      //cout << "nodePos:" << nodePos << endl;
      if (node != 1 && i != nodePos)
      {

        //Delta para reinserção de 'i' após 'nodePos'
        delta = calculaDeltaReInsertion(i, nodePos, s, adjMatrix);
        //cout << "Delta1: " << delta << "\n";
        if (delta < 0)
        {

          if (delta < betterDelta)
          {
            betterDelta = delta;
            pos_i = i;
            pos_j = nodePos;
          }
        }

        //Delta para reinserção de 'nodePos' após 'i'
        delta = calculaDeltaReInsertion(nodePos, i, s, adjMatrix);
        //cout << "Delta1: " << delta << "\n";
        if (delta < 0)
        {
          if (delta < betterDelta)
          {
            betterDelta = delta;
            pos_i = nodePos;
            pos_j = i;
          }
        }

        //Delta para reinserção de 'i' antes de 'nodePos'

        // if ((nodePos - 1) != i && nodePos != 1)
        // {
        //   delta = calculaDeltaReInsertion(i, nodePos - 1, s);
        //   //cout << "Delta1: " << delta << "\n";

        //   if (delta < 0)
        //   {
        //     if (delta < betterDelta)
        //     {
        //       betterDelta = delta;
        //       pos_i = i;
        //       pos_j = nodePos - 1;
        //     }
        //   }
        // }
      }
    }
  }

  if (pos_i > 0)
  {
    //cout << "Delta final: " << delta << endl;
    solution.erase(solution.begin() + pos_i);
    solution.insert(solution.begin() + pos_j, s[pos_i]);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double reinsertionEnd = cpuTime();
  reinsertionTime += (reinsertionEnd - reinsertionBegin);
}

inline double calculaDeltaReInsertion(int i, int j, vector<int> &s, double**adjMatrix)
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

void twoOptN(vector<int> &solution, double &cost,int n, double &twoOptTime, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &orgMatrix)
{ // inverte uma subsequencia da solução

  double twoOptBegin = cpuTime();
  vector<int> s = solution;
  double delta, betterDelta = 0;
  int pos_i = -1, pos_j;
  for (int i = 1; i < solution.size() - 1; i++)
  { // varre do primeiro ao ultimo elemento da solution
    for (int j = 1; j <= 20; j++)
    {
      int node = orgMatrix[solution[i] - 1][j];
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
              pos_i = i + 1;
              pos_j = nodePos;
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
            pos_i = nodePos + 1;
            pos_j = i;
          }
        }
      }
    }
  }
  if (pos_i > 0)
  {
    //cout << "i:" << pos_i << "j:" << pos_j << endl;
    for (int k = pos_i; k <= pos_j; k++)
    { // invertendo as posições
      solution[k] = s[pos_j + pos_i - k];
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

inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double**adjMatrix)
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

void orOpt2(vector<int> &solution, double &cost,int n, double &orOpt2Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &orgMatrix)
{ // reinsere subsequencia de dois nós em posição diferente
  double orOpt2Begin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int pos_i = -1, pos_j;
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
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if (pos_i > 0)
  {
    solution.erase(solution.begin() + pos_i, solution.begin() + pos_i + 2);
    solution.insert(solution.begin() + pos_j, &s[pos_i], &s[pos_i] + 2);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  orOpt2Time += (fimOropt2 - orOpt2Begin);
}

inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double**adjMatrix)
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

void orOpt3(vector<int> &solution, double &cost,int n, double &orOpt3Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &orgMatrix)
{ // reinsere subsequencia de tres nós em posição diferente
  double orOpt3Begin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int pos_i = -1, pos_j;

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
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if (pos_i > 0)
  {
    solution.erase(solution.begin() + pos_i, solution.begin() + pos_i + 3);
    solution.insert(solution.begin() + pos_j, &s[pos_i], &s[pos_i] + 3);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[solution[i]] = i;
    }
  }

  double fimOropt3 = cpuTime();
  orOpt3Time += (fimOropt3 - orOpt3Begin);
}

inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double**adjMatrix)
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

void orOptN(vector<int> &v, double &cost, int quantidade, int n, double &orOpt2Time, vector<int> &positionList, double**adjMatrix, vector<vector<int>> &orgMatrix)
{                         // reinsere subsequencia de dois nós em posição diferente
  double **m = adjMatrix; //diminui o tamanho da declaraçao ali embaixo
  double orOpt2Begin = cpuTime();
  vector<int> s = v;
  double betterDelta = 0;
  double delta, deltaRemove;

  int pos_i = -1, pos_j;
  for (int i = 1; i < v.size() - quantidade; i++)
  { // or-2-op/or-3-opt precisa comecar no maximo no penultimo antes do size
    deltaRemove = m[v[i]][v[i - 1]] + m[v[i + (quantidade - 1)]][v[i + quantidade]];
    for (int j = 1; j <= 20; j++)
    { //E terminar no maximo qnt antes de size
      int node = orgMatrix[v[i] - 1][j];
      int nodePos = positionList[node];
      if (i != nodePos && nodePos < (v.size() - (quantidade + 1)))
      {

        if (i < nodePos)
        { //reinsercao em um indice maior do vetor
          //delta = (m[v[i]][v[j]] + m[v[i]][v[j + 1]] + m[v[i - 1]][v[i + 1]]) -
          //        (m[v[i]][v[i + 1]] + m[v[i]][v[i - 1]] + m[v[j]][v[j + 1]]);
          delta = m[v[i - 1]][v[i + quantidade]] + m[v[i]][v[nodePos + (quantidade - 1)]] + m[v[i + (quantidade - 1)]][v[nodePos + quantidade]] -
                  m[v[nodePos + (quantidade - 1)]][v[nodePos + quantidade]] - deltaRemove;
        }
        else
        { //reinsercao em um indice betterDelta
          //delta = (m[v[i]][v[nodePos]] + m[v[i]][v[nodePos - 1]] + m[v[i - 1]][v[i + 1]]) -
          //        (m[v[i]][v[i - 1]] + m[v[i]][v[i + 1]] + m[v[nodePos]][v[nodePos - 1]]);

          if(quantidade == 2)
            delta = calculaDeltaOrOpt2(i,nodePos,v,adjMatrix); 

          if(quantidade == 3)
            delta = calculaDeltaOrOpt3(i,nodePos,v,adjMatrix);      

          //delta = (m[v[i]][v[nodePos]] + m[v[i - (quantidade - 1)]][v[nodePos - 1]] + m[v[i - quantidade]][v[i + 1]]) -
          //      (m[v[i - (quantidade - 1)]][v[i - quantidade]] + m[v[i]][v[i + 1]] + m[v[nodePos]][v[nodePos - 1]]);

        }
        if (delta <= betterDelta && abs((i - nodePos)) > quantidade)
        {
          betterDelta = delta;
          pos_i = i;
          pos_j = nodePos;
        }
      }
    }
  }
  if (pos_i > 0)
  {
    v.erase(v.begin() + pos_i, v.begin() + pos_i + quantidade);
    v.insert(v.begin() + pos_j, &s[pos_i], &s[pos_i] + quantidade);
    cost = cost + betterDelta;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[v[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  orOpt2Time += (fimOropt2 - orOpt2Begin);
}
