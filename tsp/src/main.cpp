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

int main(int argc, char** argv) {

    srand((unsigned)time(0));

    readData(argc, argv, &dimension, &matrizAdj);
    //printData();
    cidades = construction(7);
    
    //candidates();
    printSolution(cidades);
  
    
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