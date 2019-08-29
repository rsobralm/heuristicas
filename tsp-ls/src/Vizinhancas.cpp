
#include "Vizinhancas.h"
#include "Funcoes.h"

using namespace std;

void swap(vector<int> &solucao, double &custo, int dimension, double &tempo_swap, vector<int> &solucaoInvertida ,double**matrizAdj, vector<vector<int>> &matrizOrg)
{ // faz a troca de posição entre dois nós

  /*double inicioSwap = cpuTime();
  vector<int> s = solucao;
  double delta;
  double menor = std::numeric_limits<double>::infinity();
  //double fs = custoTotal(s);
  int pos_i = -1, pos_j = -1; // guarda as posições para realizar a operação
  for(int i = 1; i < solucao.size() - 1; i++){ // exclui da operação a primeira e a ultima posição do vetor
    for(int j = i + 1; j < solucao.size() - 1; j++){
      //if(i <= j){ // nao repetir swap
        //cout << "i:" << i << "j:" << j << endl;
        delta = calculaDeltaSwap(i,j,s);
        //d = custoTotal(solucao) - fs;
        //cout <<"delta real: " << d << " delta calc: " << delta << endl;
      if(delta < 0){
        if(delta < menor){
            menor = delta;
            pos_i = i;
            pos_j = j;
        }
      }
    }
  }
   if(pos_i > 0){ // realiza a operação
    solucao[pos_i] = s[pos_j];
    solucao[pos_j] = s[pos_i];
    custo = custo + menor;
  }
  double fimSwap = cpuTime();
  tempo_swap += (fimSwap - inicioSwap);
*/

  double inicioSwap = cpuTime();
  vector<int> s = solucao;
  double delta;
  double menor = std::numeric_limits<double>::infinity();
  //double fs = custoTotal(s);
  int pos_i = -1, pos_j = -1; // guarda as posições para realizar a operação
  for (int i = 2; i < solucao.size() - 2; i++)
  { // exclui da operação a ultima e penultima posição do vetor
    //for(int j = i + 1; j < solucao.size() - 1; j++){
    for (int j = 1; j <= 20; j++)
    { // pega os 5 vizinhos mais proximos
      int no = matrizOrg[solucao[i] - 1][j];
      int muda = solucaoInvertida[no];

      if (no != 1 && i != muda)
      {
        //if(i <= j){ // nao repetir swap
        //cout << "i:" << i << "j:" << j << endl;
        for (int k = -1; k <= 1; k++)
        {
          if (i + k < muda)
            delta = calculaDeltaSwap(i + k, muda, s, matrizAdj);
          else
            delta = calculaDeltaSwap(muda, i + k, s, matrizAdj);

          if (delta < 0)
          {
            if (delta < menor)
            {
              menor = delta;
              pos_i = i + k;
              pos_j = muda;
            }
          }
        }
      }
    }
  }
  //////// REINSERINDO NAS PONTAS DA SOLUCAO;
  for (int l = 1; l <= 2; l++)
  {
    int i = 1;
    if (l == 2)
    {
      i = dimension - 1;
    }
    for (int j = 1; j <= 20; j++)
    { // pega os 5 vizinhos mais proximos
      int no = matrizOrg[solucao[i] - 1][j];
      int muda = solucaoInvertida[no];
      if (no != 1 && i != muda)
      {
        //if(i <= j){ // nao repetir swap
        //cout << "i:" << i << "j:" << j << endl;
        if (i == 1)
        {
          for (int k = 0; k <= 1; k++)
          {
            if (i + k < muda)
              delta = calculaDeltaSwap(i + k, muda, s, matrizAdj);
            else
              delta = calculaDeltaSwap(muda, i + k, s, matrizAdj);
            if (delta < 0)
            {
              if (delta < menor)
              {
                menor = delta;
                pos_i = i + k;
                pos_j = muda;
              }
            }
          }
        }
        else
        {
          for (int k = -1; k <= 0; k++)
          {
            if (i + k < muda)
              delta = calculaDeltaSwap(i + k, muda, s, matrizAdj);
            else
              delta = calculaDeltaSwap(muda, i + k, s, matrizAdj);
            if (delta < 0)
            {
              if (delta < menor)
              {
                menor = delta;
                pos_i = i + k;
                pos_j = muda;
              }
            }
          }
        }
      }
    }
  }
  if (pos_i > 0)
  { // realiza a operação
    solucao[pos_i] = s[pos_j];
    solucao[pos_j] = s[pos_i];
    custo = custo + menor;

    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[solucao[i]] = i;
    }
  }
  //cout << custo << "\n";
  double fimSwap = cpuTime();
  tempo_swap += (fimSwap - inicioSwap);
}

inline double calculaDeltaSwap(int i, int j, vector<int> &s, double** matrizAdj)
{
  double delta;
  if (i + 1 == j)
  {
    delta = matrizAdj[s[i - 1]][s[j]] + matrizAdj[s[i]][s[j + 1]] - matrizAdj[s[i - 1]][s[j - 1]] - matrizAdj[s[i + 1]][s[j + 1]];
  }
  else
  {
    delta = matrizAdj[s[i]][s[j - 1]] + matrizAdj[s[i]][s[j + 1]] + matrizAdj[s[j]][s[i - 1]] + matrizAdj[s[j]][s[i + 1]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i]][s[i + 1]] - matrizAdj[s[j]][s[j - 1]] - matrizAdj[s[j]][s[j + 1]];
  }
  //cout << "delta swap: " << delta <<endl;
  return delta;
}

void reInsertion(vector<int> &solucao, double &custo,int dimension, double &tempo_reinsertion, vector<int> &solucaoInvertida ,double**matrizAdj, vector<vector<int>> &matrizOrg)
{  // reinsere um nó em posição diferente
  double inicioreinsertion = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j = -1;

  for (int i = 1; i < solucao.size() - 1; i++)
  { // varre a solução exceto o 0 e o final
    for (int j = 1; j <= 20; j++)
    {
      int no = matrizOrg[solucao[i] - 1][j];
      //cout << "no:" << no << endl;
      int muda = solucaoInvertida[no] - 1; // coloca o nó da posicão atras do vizinho mais proximo
      if (muda < i)
      {
        muda++;
      }
      //cout << "muda:" << muda << endl;
      if (no != 1 && i != muda)
      {

        //Delta para reinserção de 'i' após 'muda'
        delta = calculaDeltaReInsertion(i, muda, s, matrizAdj);
        //cout << "Delta1: " << delta << "\n";
        if (delta < 0)
        {

          if (delta < menor)
          {
            menor = delta;
            pos_i = i;
            pos_j = muda;
          }
        }

        //Delta para reinserção de 'muda' após 'i'
        delta = calculaDeltaReInsertion(muda, i, s, matrizAdj);
        //cout << "Delta1: " << delta << "\n";
        if (delta < 0)
        {
          if (delta < menor)
          {
            menor = delta;
            pos_i = muda;
            pos_j = i;
          }
        }

        //Delta para reinserção de 'i' antes de 'muda'

        // if ((muda - 1) != i && muda != 1)
        // {
        //   delta = calculaDeltaReInsertion(i, muda - 1, s);
        //   //cout << "Delta1: " << delta << "\n";

        //   if (delta < 0)
        //   {
        //     if (delta < menor)
        //     {
        //       menor = delta;
        //       pos_i = i;
        //       pos_j = muda - 1;
        //     }
        //   }
        // }
      }
    }
  }

  if (pos_i > 0)
  {
    //cout << "Delta final: " << delta << endl;
    solucao.erase(solucao.begin() + pos_i);
    solucao.insert(solucao.begin() + pos_j, s[pos_i]);
    custo = custo + menor;

    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[solucao[i]] = i;
    }
  }

  double fimReinsertion = cpuTime();
  tempo_reinsertion += (fimReinsertion - inicioreinsertion);
}

inline double calculaDeltaReInsertion(int i, int j, vector<int> &s, double**matrizAdj)
{
  double delta;
  if (i <= j)
  {
    delta = matrizAdj[s[i]][s[j + 1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i - 1]][s[i + 1]] - matrizAdj[s[j]][s[j + 1]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i]][s[i + 1]];
  }
  else
  {
    delta = matrizAdj[s[i]][s[j - 1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i - 1]][s[i + 1]] - matrizAdj[s[j]][s[j - 1]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i]][s[i + 1]];
  }
  return delta;
}

void twoOptN(vector<int> &solucao, double &custo,int dimension, double &tempo_2opt, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg)
{ // inverte uma subsequencia da solução
  /*double inicio2opt = cpuTime();
  vector<int> s = solucao;
  double delta, menor = 0;
  int pos_i = -1, pos_j;
  for (int i = 1; i < solucao.size() - 2; i++){
    for (int j = i + 1; j < solucao.size() - 1; j++){
      delta = calculaDeltaTwoOpt(i, j, s);
      if (delta < 0){
        if (delta < menor){
          menor = delta;
          pos_i = i;
          pos_j = j;
        }
      }
    }
  }
  if (pos_i > 0){
    for (int k = pos_i; k <= pos_j; k++){ // invertendo as posições
      solucao[k] = s[pos_j + pos_i - k];
    }
    custo = custo + menor;
    for (int i = 0; i < solucaoInvertida.size(); i++){
      solucaoInvertida[solucao[i]] = i;
    }
  }
  double fim2opt = cpuTime();
  tempo_2opt += (fim2opt - inicio2opt);*/
  double inicio2opt = cpuTime();
  vector<int> s = solucao;
  double delta, menor = 0;
  int pos_i = -1, pos_j;
  for (int i = 1; i < solucao.size() - 1; i++)
  { // varre do primeiro ao ultimo elemento da solucao
    for (int j = 1; j <= 20; j++)
    {
      int no = matrizOrg[solucao[i] - 1][j];
      int muda = solucaoInvertida[no];
      if (i != muda && no != 1)
      {
        if (muda > i)
        {
          delta = calculaDeltaTwoOpt(i + 1, muda, s, matrizAdj);
          //cout << "delta1:" << delta << endl;
          if (delta < 0)
          {
            if (delta < menor)
            {
              menor = delta;
              pos_i = i + 1;
              pos_j = muda;
            }
          }
        }
        if (muda < i)
        {
          delta = calculaDeltaTwoOpt(muda + 1, i, s, matrizAdj);
          //cout << "delta2:" << delta << endl;
          if (delta < menor)
          {
            menor = delta;
            pos_i = muda + 1;
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
      solucao[k] = s[pos_j + pos_i - k];
    }
    custo = custo + menor;
    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[solucao[i]] = i;
    }
  }
  double fim2opt = cpuTime();
  tempo_2opt += (fim2opt - inicio2opt);
}

inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s, double**matrizAdj)
{
  double delta;
  if (j == (i + 1))
  {
    delta = matrizAdj[s[i - 1]][s[j]] + matrizAdj[s[i]][s[j + 1]] - matrizAdj[s[i - 1]][s[j - 1]] - matrizAdj[s[j]][s[j + 1]];
  }
  else
  {
    delta = matrizAdj[s[i - 1]][s[j]] + matrizAdj[s[i]][s[j + 1]] - matrizAdj[s[i - 1]][s[i]] - matrizAdj[s[j]][s[j + 1]];
  }
  return delta;
}

void orOpt2(vector<int> &solucao, double &custo,int dimension, double &tempo_orOpt2, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg)
{ // reinsere subsequencia de dois nós em posição diferente
  double inicioOropt2 = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j;
  for (int i = 1; i < solucao.size() - 2; i++)
  {
    for (int j = 1; j < solucao.size() - 3; j++)
    {
      if (i != j)
      {
        delta = calculaDeltaOrOpt2(i, j, s, matrizAdj);
        if (delta < 0)
        {
          if (delta < menor)
          {
            menor = delta;
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if (pos_i > 0)
  {
    solucao.erase(solucao.begin() + pos_i, solucao.begin() + pos_i + 2);
    solucao.insert(solucao.begin() + pos_j, &s[pos_i], &s[pos_i] + 2);
    custo = custo + menor;

    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[solucao[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  tempo_orOpt2 += (fimOropt2 - inicioOropt2);
}

inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s, double**matrizAdj)
{
  double delta;
  if (i < j)
  {
    delta = matrizAdj[s[i - 1]][s[i + 2]] + matrizAdj[s[i]][s[j + 1]] + matrizAdj[s[i + 1]][s[j + 2]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i + 1]][s[i + 2]] - matrizAdj[s[j + 1]][s[j + 2]];
  }
  else
  {
    delta = matrizAdj[s[i]][s[j - 1]] + matrizAdj[s[i + 1]][s[j]] + matrizAdj[s[i + 2]][s[i - 1]] - matrizAdj[s[j]][s[j - 1]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i + 1]][s[i + 2]];
  }

  return delta;
}

void orOpt3(vector<int> &solucao, double &custo,int dimension, double &tempo_orOpt3, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg)
{ // reinsere subsequencia de tres nós em posição diferente
  double inicioOropt3 = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j;

  for (int i = 1; i < solucao.size() - 3; i++)
  {
    for (int j = 1; j < solucao.size() - 4; j++)
    {
      if (i != j)
      {
        delta = calculaDeltaOrOpt3(i, j, s, matrizAdj);
        if (delta < 0)
        {
          if (delta < menor)
          {
            menor = delta;
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if (pos_i > 0)
  {
    solucao.erase(solucao.begin() + pos_i, solucao.begin() + pos_i + 3);
    solucao.insert(solucao.begin() + pos_j, &s[pos_i], &s[pos_i] + 3);
    custo = custo + menor;

    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[solucao[i]] = i;
    }
  }

  double fimOropt3 = cpuTime();
  tempo_orOpt3 += (fimOropt3 - inicioOropt3);
}

inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s, double**matrizAdj)
{
  double delta;
  if (i < j)
  {
    delta = matrizAdj[s[i - 1]][s[i + 3]] + matrizAdj[s[i]][s[j + 2]] + matrizAdj[s[i + 2]][s[j + 3]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i + 2]][s[i + 3]] - matrizAdj[s[j + 2]][s[j + 3]];
  }
  else
  {
    delta = matrizAdj[s[i]][s[j - 1]] + matrizAdj[s[i + 2]][s[j]] + matrizAdj[s[i - 1]][s[i + 3]] - matrizAdj[s[j]][s[j - 1]] - matrizAdj[s[i]][s[i - 1]] - matrizAdj[s[i + 2]][s[i + 3]];
  }

  return delta;
}

void orOptN(vector<int> &v, double &custo, int quantidade, int dimension, double &tempo_orOpt2, vector<int> &solucaoInvertida, double**matrizAdj, vector<vector<int>> &matrizOrg)
{                         // reinsere subsequencia de dois nós em posição diferente
  double **m = matrizAdj; //diminui o tamanho da declaraçao ali embaixo
  double inicioOropt2 = cpuTime();
  vector<int> s = v;
  double menor = 0;
  double delta, deltaRemove;

  int pos_i = -1, pos_j;
  for (int i = 1; i < v.size() - quantidade; i++)
  { // or-2-op/or-3-opt precisa comecar no maximo no penultimo antes do size
    deltaRemove = m[v[i]][v[i - 1]] + m[v[i + (quantidade - 1)]][v[i + quantidade]];
    for (int j = 1; j <= 20; j++)
    { //E terminar no maximo qnt antes de size
      int no = matrizOrg[v[i] - 1][j];
      int muda = solucaoInvertida[no];
      if (i != muda && muda < (v.size() - (quantidade + 1)))
      {

        if (i < muda)
        { //reinsercao em um indice maior do vetor
          //delta = (m[v[i]][v[j]] + m[v[i]][v[j + 1]] + m[v[i - 1]][v[i + 1]]) -
          //        (m[v[i]][v[i + 1]] + m[v[i]][v[i - 1]] + m[v[j]][v[j + 1]]);
          delta = m[v[i - 1]][v[i + quantidade]] + m[v[i]][v[muda + (quantidade - 1)]] + m[v[i + (quantidade - 1)]][v[muda + quantidade]] -
                  m[v[muda + (quantidade - 1)]][v[muda + quantidade]] - deltaRemove;
        }
        else
        { //reinsercao em um indice menor
          //delta = (m[v[i]][v[muda]] + m[v[i]][v[muda - 1]] + m[v[i - 1]][v[i + 1]]) -
          //        (m[v[i]][v[i - 1]] + m[v[i]][v[i + 1]] + m[v[muda]][v[muda - 1]]);

          if(quantidade == 2)
            delta = calculaDeltaOrOpt2(i,muda,v,matrizAdj); 

          if(quantidade == 3)
            delta = calculaDeltaOrOpt3(i,muda,v,matrizAdj);      

          //delta = (m[v[i]][v[muda]] + m[v[i - (quantidade - 1)]][v[muda - 1]] + m[v[i - quantidade]][v[i + 1]]) -
          //      (m[v[i - (quantidade - 1)]][v[i - quantidade]] + m[v[i]][v[i + 1]] + m[v[muda]][v[muda - 1]]);

        }
        if (delta <= menor && abs((i - muda)) > quantidade)
        {
          menor = delta;
          pos_i = i;
          pos_j = muda;
        }
      }
    }
  }
  if (pos_i > 0)
  {
    v.erase(v.begin() + pos_i, v.begin() + pos_i + quantidade);
    v.insert(v.begin() + pos_j, &s[pos_i], &s[pos_i] + quantidade);
    custo = custo + menor;

    for (int i = 0; i < solucaoInvertida.size(); i++)
    {
      solucaoInvertida[v[i]] = i;
    }
  }

  double fimOropt2 = cpuTime();
  tempo_orOpt2 += (fimOropt2 - inicioOropt2);
}
