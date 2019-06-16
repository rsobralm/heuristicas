#include "readData.h"
#include "CustoIn.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

double ** matrizAdj; // matriz de adjacencia
double ** matrizDist; // matriz reorganizada;
int dimension; // quantidade total de vertices
vector<int> cidades;
vector<int> candidatos;

void printData();
vector<int> construction(int tamanhoInicial);
void printSolution(vector<int> anyVector);
void candidates();
bool comp(const CustoIn& a, const CustoIn& b);
vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> s);
vector<int> swap(vector<int> solucao);
double calculaDeltaSwap(int i, int j, vector<int> s);
vector<int> reIsertion(vector<int>solucao);
double custoTotal(vector<int>solucao);
double calculaDeltaReInsertion(int i, int j, vector<int> s);
vector<int> TwoOptN(vector<int> solucao);
double calculaDeltaTwoOpt(int i, int j, vector<int> s);
vector<int> orOpt2(vector<int> solucao);
double calculaDeltaOrOpt2(int i, int j, vector<int> s);

int main(int argc, char** argv) {

    srand((unsigned)time(0));

    readData(argc, argv, &dimension, &matrizAdj);
   // printData();
    vector<int> teste = construction(7);
    printSolution(teste);
    //cout << "custo: " << custoTotal(teste) << endl;
    //cidades = swap(teste);
    //cidades = reIsertion(teste);
    //vector<int> tora = {1,2,3,4,5,6,7,8,9,1};
    //printSolution(tora);
    cidades = orOpt2(teste);
    printSolution(cidades);
    //cout << "custo: " << custoTotal(cidades) << endl;
  
    
    return 0;

    

}

void printData() {
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++) {
    for (size_t j = 1; j <= dimension; j++) {
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}

vector<int> construction(int tamanhoInicial){ 
  vector<int> s = {1,1};// lista de cidades da solução inicial
  vector<int> listaCandidatos;
  for(int i = 2; i <= dimension; i++){
    listaCandidatos.push_back(i);
  }

  for(int j = 0; j < tamanhoInicial; j++){
    int k = rand() % listaCandidatos.size();
    s.insert(s.begin() + 1, listaCandidatos[k]); // adiciona cidade aleatoria a solução
    listaCandidatos.erase(listaCandidatos.begin() + k); // apaga da lista de candidatos oq ja foi pra solução
  }


 vector<CustoIn> custoInsertion = calculaCusto(listaCandidatos, s);

  
  std::sort(custoInsertion.begin(), custoInsertion.end(), comp);

  int sel;
  while(!listaCandidatos.empty()){
    if(custoInsertion.size() > 3){
    sel = rand() % 2; }
    else {
      sel = rand() % custoInsertion.size();
      cout << sel << endl;
    }
    
    s.insert(s.begin() + custoInsertion[sel].arestaOut + 1, custoInsertion[sel].noIn); // SEG FAULT ERRO QUANDO ALTERA O PENULTIMO ELEMENTO
    
    for(int i = 0; i < listaCandidatos.size(); i++){
      if(listaCandidatos[i]==custoInsertion[sel].noIn)
        listaCandidatos.erase(listaCandidatos.begin() + i);
    }
    
    custoInsertion.erase(custoInsertion.begin(), custoInsertion.begin() + custoInsertion.size());
    custoInsertion = calculaCusto(listaCandidatos, s);
    std::sort(custoInsertion.begin(), custoInsertion.end(), comp);

  }

  return s;

}


void printSolution(vector<int> anyVector){ // printa um vetor qualquer
   vector<int>::iterator v = anyVector.begin(); 
   while( v != anyVector.end()) {
      cout << *v << endl;
      v++;
   }
}

 bool comp(const CustoIn& a, const CustoIn& b) // comparação dos custos utilizada para ordenar os objetos
  {
    return a.custo < b.custo;
  }

vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> s){
  vector<CustoIn> custoInsertion ((s.size() - 1) * listaCandidatos.size());
  for(int i = 0, j = 1, l = 0; i < s.size()-1; i++, j++){
    for(auto k : listaCandidatos){
      custoInsertion[l].custo = matrizAdj[s[i]][k] +  matrizAdj[s[j]][k] - matrizAdj[s[i]][s[j]]; 
      custoInsertion[l].noIn = k;
      custoInsertion[l].arestaOut = i;
      l++;
    }
  }
  return custoInsertion;


}

vector<int> swap(vector<int> solucao){
  vector<int> solCopy = solucao;
  vector<int> melhor;
  double d, d2;
  double menor;
  double fs = custoTotal(solucao);
  for(int i = 1; i < solucao.size() - 1; i++){ // excluir da operação a primeira e a ultima posição do vetor
    for(int j = 1; j < solucao.size() - 1; j++){ 
      if(i <= j){ // nao repetir swap
        int aux = solucao[i];
        solCopy[i] = solucao[j];
        solCopy[j] = aux;
        d2 = calculaDeltaSwap(i,j, solucao);
        d = custoTotal(solCopy) - fs;
        //cout <<"i:"<< i << "  j:"<< j << "  delta = " << d << endl;
        if(d <= menor || (i == 1 && j == 1)){
          menor = d;
          melhor = solCopy;
        }
        solCopy = solucao;
      }
    }
  }
  return melhor;

}

double calculaDeltaSwap(int i, int j, vector<int> s){
  double delta;
  if(i == 1 && j < 4){
    delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[i]] - matrizAdj[s[j]][s[j+1]];
  }
  else{
    if(i + 1 == j){
      delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[j-1]] - matrizAdj[s[j]][s[j+1]];
    }
    else{
    delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[j]][s[i-1]] + matrizAdj[s[j]][s[i+1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[j]][s[j+1]];
        }
  }
  //cout << "delta swap: " << delta <<endl; 
  return delta; 
}

vector<int> reIsertion(vector<int>solucao){
  vector<int> solCopy = solucao;
  //double fs = custoTotal(solucao);
  double menor = 0;
  vector<int> melhor;
  double d, d2; 
  for(int i = 1; i < solucao.size() - 1; i++){
    for(int j = 1; j < solucao.size() - 1; j++){
      if(i != j){
      solCopy.erase(solCopy.begin() + i);
      solCopy.insert(solCopy.begin() + j, solucao[i]);
       //d = custoTotal(solCopy) - fs;
       d2 = calculaDeltaReInsertion(i,j,solucao);
       //cout <<"i:"<< i << "  j:"<< j << "  delta = " << d2 << endl;
      if(d2 <= menor || (i == 1 && j == 1)){
        menor = d2;
        melhor = solCopy;
      }
      solCopy = solucao;
      }
    }
     
  }
  return melhor;
}

double calculaDeltaReInsertion(int i, int j, vector<int> s){
  double delta;
  if(i <= j){
    delta = matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i-1]][s[i+1]] - matrizAdj[s[j]][s[j+1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]];
            }
  else{
  delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i-1]][s[i+1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]];
      }
  //cout << "Delta Re: "<< delta << endl;
  return delta;

}

vector<int> TwoOptN(vector<int> solucao){
  vector<int> solCopy = solucao;
  vector<int> solInverted;
  double delta , d, menor = 0;
  double fs = custoTotal(solucao);
    for(int i = 1; i < solucao.size() - 2; i++){
      for(int j = i + 1; j < solucao.size() - 1; j++){
        solCopy = solucao;
        for(int k = i; k <= j; k++){
          solCopy[k] = solucao[j + i - k];
        }
        //d = custoTotal(solCopy) - fs;
        //cout << "i: "<<i<<"j: "<<j <<"delta = "<<d<<endl;
        delta = calculaDeltaTwoOpt(i, j, solucao);
        //cout << "i: "<<i<<"j: "<<j <<"d = "<<delta<<endl;
        if(delta <= menor){
          menor = delta;
          solInverted = solCopy;
        }
      }
    }
      
    return solInverted;
}

double calculaDeltaTwoOpt(int i, int j, vector<int> s){
  double delta;
  if(j == (i + 1)){
    delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[j-1]] - matrizAdj[s[j]][s[j+1]];
  }
  else{
  delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[i]] - matrizAdj[s[j]][s[j+1]];
  }
  return delta;
}

vector<int> orOpt2(vector<int> solucao){
  vector<int> solCopy = solucao;
  vector<int> melhor;
  double menor = 0;
  double d, delta;
  double fs = custoTotal(solucao);
  for(int i = 1; i < solucao.size() - 2; i++){
    for(int j = 1; j < solucao.size() - 3; j++){
      if(i != j){
        solCopy = solucao;
        solCopy.erase(solCopy.begin() + i, solCopy.begin() + i + 2);
        solCopy.insert(solCopy.begin() + j, &solucao[i], &solucao[i] + 2);
        
        delta = calculaDeltaOrOpt2(i,j,solucao);
        if(delta <= menor){
          menor = delta;
          melhor = solCopy;
        }
        
      }
      
    }
     
  }

  return melhor;
}

double calculaDeltaOrOpt2(int i, int j, vector<int> s){
  double delta;
  if(i < j){
    //delta = matrizAdj[s[i-1]][s[j-1]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i+1]][s[j+2]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+1]][s[i+2]] - matrizAdj[s[j+1]][s[j+2]];
    delta = matrizAdj[s[i-1]][s[i+2]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i+1]][s[j+2]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+1]][s[i+2]] - matrizAdj[s[j+1]][s[j+2]];
  }
  else { 
    delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i+1]][s[j]] + matrizAdj[s[i+2]][s[i-1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+1]][s[i+2]];
  }

  return delta;
}

double custoTotal(vector<int>solucao){
  double custo = 0;
  for(int i = 0, j = 1; i < solucao.size(); i++, j++){
     custo = custo + matrizAdj[solucao[i]][solucao[j]];
  }
  return custo;
}
