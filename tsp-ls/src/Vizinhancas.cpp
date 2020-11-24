
#include "Vizinhancas.h"
#include "Funcoes.h"

using namespace std;

void swap(vector<int> &solution, double &cost, int n, double &swapTime, vector<int> &positionList ,double**adjMatrix, vector<vector<int>> &orgMatrix)
{ // faz a troca de posição entre dois nós

 // double swapBegin = cpuTime();
  vector<int> s = solution;
  double delta;
  double betterDelta = std::numeric_limits<double>::infinity();
  //double fs = costTotal(s);
  int pos_i = -1, pos_j = -1; // guarda as posições para realizar a operação
  for (int i = 2; i < solution.size() - 2; i++)
  { // exclui da operação a ultima e penultima posição do vetor
    //for(int j = i + 1; j < solution.size() - 1; j++){
    for (int j = 1; j <= 15; j++)
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
    for (int j = 1; j <= 15; j++)
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
  //double swapEnd = cpuTime();
  //swapTime += (swapEnd - swapBegin);
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
  //double reinsertionBegin = cpuTime();
  vector<int> s = solution;
  double betterDelta = 0;
  double delta;
  int pos_i = -1, pos_j = -1;

  for (int i = 1; i < solution.size() - 1; i++)
  { // varre a solução exceto o 0 e o final
    for (int j = 1; j <= 15; j++)
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

  //double reinsertionEnd = cpuTime();
 // reinsertionTime += (reinsertionEnd - reinsertionBegin);
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

 // double twoOptBegin = cpuTime();
  vector<int> s = solution;
  double delta, betterDelta = 0;
  int pos_i = -1, pos_j;
  for (int i = 1; i < solution.size() - 1; i++)
  { // varre do primeiro ao ultimo elemento da solution
    for (int j = 1; j <= 15; j++)
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
//  double twoOptEnd = cpuTime();
//  twoOptTime += (twoOptEnd - twoOptBegin);
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
 // double orOpt2Begin = cpuTime();
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

 // double fimOropt2 = cpuTime();
 // orOpt2Time += (fimOropt2 - orOpt2Begin);
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
  //double orOpt3Begin = cpuTime();
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

  //double fimOropt3 = cpuTime();
  //orOpt3Time += (fimOropt3 - orOpt3Begin);
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
  //double orOpt2Begin = cpuTime();
  vector<int> s = v;
  double betterDelta = 0;
  double delta, deltaRemove;

  int pos_i = -1, pos_j;
  for (int i = 1; i < v.size() - quantidade; i++)
  { // or-2-op/or-3-opt precisa comecar no maximo no penultimo antes do size
    deltaRemove = m[v[i]][v[i - 1]] + m[v[i + (quantidade - 1)]][v[i + quantidade]];
    for (int j = 1; j <= 15; j++)
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

  //double fimOropt2 = cpuTime();
  //orOpt2Time += (fimOropt2 - orOpt2Begin);
}

phiData ***phi;
phiData ***phiSub;

void initializePhiMatrix(int n){

  phiSub = new phiData**[2];
  phi = new phiData**[2];
  for(int x = 0; x < 2; ++x) {
    phiSub[x] = new phiData*[n];
    phi[x] = new phiData*[n];
    for(int y = 0; y < n; ++y) {
      phiSub[x][y] = new phiData[n];
      phi[x][y] = new phiData[n];
      for(int z = 0; z < n; ++z) { // initialize the values to whatever you want the default to be
          phiSub[x][y][z] = {0, 0 ,0.0};
          phi[x][y][z] = {0, 0, 0.0};
      }
    }
  }
}


double deltaX(vector<int> &s, int x, int i, int j, double**matrizAdj){

  double delta;
  if(x == 0)
    delta = matrizAdj[s[i]][s[j]] + matrizAdj[s[i+1]][s[j+1]];
  else
    delta = matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i+1]][s[j]];

  return delta - matrizAdj[s[i]][s[i+1]] - matrizAdj[s[j]][s[j+1]];
}

void movefourOpt(vector<int> &s, double &cost, FourOptMoveData d){

  vector<int> newSolution;
  int dimension = s.size()-1;
  vector<int> pi1;
  vector<int> pi2;
  vector<int> pi3;
  vector<int> pi4;
  vector<int> pi5;

  pi1.assign(&s[0], &s[d.i1+1]);
  pi2.assign(&s[d.i1+1], &s[d.i2+1]);
  pi3.assign(&s[d.i2+1], &s[d.j1+1]);
  pi4.assign(&s[d.j1+1], &s[d.j2+1]);
  pi5.assign(&s[d.j2+1], &s[dimension+1]);

  if(d.x1 == 1 && d.x2 == 1){
    //vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    newSolution.insert(newSolution.end(), pi1.begin(), pi1.end());
    newSolution.insert(newSolution.end(), pi4.begin(), pi4.end());
    newSolution.insert(newSolution.end(), pi3.begin(), pi3.end());
    newSolution.insert(newSolution.end(), pi2.begin(), pi2.end());
    newSolution.insert(newSolution.end(), pi5.begin(), pi5.end());
  }
  if(d.x1 == 0 && d.x2 == 1){
    newSolution.insert(newSolution.end(), pi1.begin(), pi1.end());
    newSolution.insert(newSolution.end(), pi3.rbegin(), pi3.rend());
    newSolution.insert(newSolution.end(), pi4.rbegin(), pi4.rend());
    newSolution.insert(newSolution.end(), pi2.begin(), pi2.end());
    newSolution.insert(newSolution.end(), pi5.begin(), pi5.end());
  }
  if(d.x1 == 1 && d.x2 == 0){
    newSolution.insert(newSolution.end(), pi1.begin(), pi1.end());
    newSolution.insert(newSolution.end(), pi4.begin(), pi4.end());
    newSolution.insert(newSolution.end(), pi2.rbegin(), pi2.rend());
    newSolution.insert(newSolution.end(), pi3.rbegin(), pi3.rend());
    newSolution.insert(newSolution.end(), pi5.begin(), pi5.end());
  }


  s = newSolution;
  cost += d.costVar;
}

void fourOpt(vector<int> &s, double &cost, int dimension, vector<int> &positionList, double**matrizAdj){

  int n = s.size();
  double inicio4opt = cpuTime();
  double fim4opt;

  double deltaBest = 0;
  //int i2, j1, j2;
  double delta_type1, delta_type2A, delta_type2B;
  FourOptMoveData delta_best;
  double best_cost_var;

  delta_best = (FourOptMoveData ){0, 0, -1, -1, -1, -1, 0.0};

    for(int j1 = 2; j1 <= n-2; j1++){
      for(int i2 = 1; i2 <= j1-1; i2++){
        for(int x = 0; x <= 1; x++){
          if(i2 == 1){
            phiSub[x][i2][j1].i = 0;
            phiSub[x][i2][j1].j = j1;
            phiSub[x][i2][j1].cost = deltaX(s,x,0,j1, matrizAdj);
          }
          else{
            if(phiSub[x][i2 - 1][j1].cost < deltaX(s,x,i2-1,j1, matrizAdj))
              phiSub[x][i2][j1] = phiSub[x][i2-1][j1];
            else{
              phiSub[x][i2][j1].i = i2-1;
              phiSub[x][i2][j1].j = j1;
              phiSub[x][i2][j1].cost = deltaX(s,x,i2-1,j1, matrizAdj);
            }
          }
        }
      }
    }
  for(int i2 = 1; i2 < n-2; i2++){
    for(int j2 = i2+2; j2 <= n-2; j2++){
      for(int x = 0; x <= 1; x++){
        if(j2 == i2+2){
          phi[x][i2][j2] = phiSub[x][i2][i2+1];
        }
        else{
          if(phi[x][i2][j2-1].cost < phiSub[x][i2][j2-1].cost)
            phi[x][i2][j2] = phi[x][i2][j2-1];
          else
            phi[x][i2][j2] = phiSub[x][i2][j2-1];
        }
      }
      delta_type1 = deltaX(s, 1, i2, j2, matrizAdj) + phi[1][i2][j2].cost; // Two disconnecting 2-opts.
      delta_type2A = deltaX(s, 1, i2, j2, matrizAdj) + phi[0][i2][j2].cost; // A connecting and a disconnecting 2-opt;
      delta_type2B = deltaX(s, 0, i2, j2, matrizAdj) + phi[1][i2][j2].cost; // A connecting and a disconnecting 2-opt.

      
     // cout  << " i2: " << i2 << " j2: " << j2 << endl;
      //cout << delta_type1 << " " << delta_type2A << " " << delta_type2B << endl;

      best_cost_var = min({ delta_best.costVar, delta_type1, delta_type2A, delta_type2B });
      //cout << "best " << best_cost_var << endl;
      if (best_cost_var == delta_type1)
          delta_best = (FourOptMoveData){1, 1, phi[1][i2][j2].i, phi[1][i2][j2].j, i2, j2, delta_type1};
      else if (best_cost_var == delta_type2A)
          delta_best = (FourOptMoveData){0, 1, phi[0][i2][j2].i, phi[0][i2][j2].j, i2, j2, delta_type2A};
      else if (best_cost_var == delta_type2B)
          delta_best = (FourOptMoveData){1, 0, phi[1][i2][j2].i, phi[1][i2][j2].j, i2, j2, delta_type2B};

      //cout << phi[0][i2][j2].i << " "<< phi[1][i2][j2].i << " " << phi[0][i2][j2].j << " "<< phi[1][i2][j2].j << " " << i2 << " " << j2 << endl;
      //cout << delta_type1 << " " << delta_type2A << " "<< delta_type2B <<endl;
    }
  }

  if(delta_best.costVar < 0.0){
    //cout << delta_best.i1 <<" " <<delta_best.i2<<" " << delta_best.j1<<" " << delta_best.j2 << " " << delta_best.costVar <<" type: " << delta_best.x1 <<" " << delta_best.x2<< endl;
    movefourOpt(s, cost, delta_best);
    fim4opt = cpuTime();
    //tempo_4opt += (fim4opt - inicio4opt);
    //melhoras4opt++;

    for (int i = 0; i < positionList.size(); i++)
    {
      positionList[s[i]] = i;
    }

    return;
  }
  fim4opt = cpuTime();
  //tempo_4opt += (fim4opt - inicio4opt);

}