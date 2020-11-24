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
#include <sys/timeb.h>
#include <sys/resource.h>


using namespace std;

double ** matrizAdj; // matriz de adjacencia
double ** matrizDist; // matriz reorganizada;
int dimension; // quantidade total de vertices
vector<int> cidades;
vector<int> solucaum;
vector<int> candidatos;

double tempo_construction = 0;
double tempo_swap = 0;
double tempo_reinsertion = 0;
double tempo_2opt = 0;
double tempo_orOpt2 = 0;
double tempo_orOpt3 = 0;
double tempo_4opt = 0;

int melhorasSwap = 0;
int melhoras2opt = 0;
int melhorasReinsert = 0;
int melhorasOrOpt2 = 0;
int melhorasOrOpt3 = 0;
int melhoras4opt = 0;

struct FourOptMoveData
{
  int x1, x2;
  int i1, j1;
  int i2, j2;
  double costVar;
};

struct phiData
{
  int i, j;
  double cost;
};

phiData ***phi;
phiData ***phiSub;

void printData();
vector<int> construction(double alfa, double &valor);
void printSolution(vector<int> anyVector);
void candidates();
bool comp(const CustoIn& a, const CustoIn& b);
vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> &s);
void swap(vector<int> &solucao, double &custo);
double calculaDeltaSwap(int i, int j, vector<int> &s);
void reInsertion(vector<int> &solucao, double &custo);
double custoTotal(vector<int> &solucao);
double calculaDeltaReInsertion(int i, int j, vector<int> &s);
void twoOptN(vector<int> &solucao, double &custo);
double calculaDeltaTwoOpt(int i, int j, vector<int> &s);
void orOpt2(vector<int> &solucao, double &custo);
double calculaDeltaOrOpt2(int i, int j, vector<int> &s);
void orOpt3(vector<int> &solucao, double &custo);
double calculaDeltaOrOpt3(int i, int j, vector<int> &s);
void rvnd(vector<int> &solucao, double &valor_obj);
vector<int> perturb(vector<int> &solucao);
vector<int> gils_rvnd(int i_max, int i_ils);
double cpuTime();
void printTime();

void initializePhiMatrix(int n);
void movefourOpt(vector<int> &s, double &cost, FourOptMoveData d);
void fourOpt(vector<int> &s, double &cost);
double deltaX(vector<int> &s, int x, int i, int j);

/*void readDataSch(int argc, char** argv, int &n, double ***mSetupTimes){
   int N, nMachines;
    string arquivo, ewt;

    char *instancia;
    instancia = argv[1];

    ifstream in( instancia, ios::in);

    in >> N;
    n = N;
    //cout << N << endl;

     double **setupTimes = new double*[N+1];

    for ( int i = 0; i <= N; i++){
        setupTimes [i] = new double [N+1];
    }

    for(int i = 0; i <= N; i++){
        setupTimes[i][0] = 0; // sem erro, ainda suspeito
        for(int j = 1; j <= N; j++){
            in >> setupTimes[i][j];
        }
    }

       *mSetupTimes = setupTimes;
}*/

int main(int argc, char** argv) {

    double somaTempos;
    double somaValores;
    std::string arg1(argv[1]);
    cout << arg1 << endl;
    
    
   // for(int i = 0; i < 10;i++){
      double valor;
      int i_max = 50;
      int i_ils;
      readData(argc, argv, &dimension, &matrizAdj);
     // readDataSch(argc, argv, &dimension, &matrizAdj);
      //printData();

      srand((unsigned)time(0));

      if(dimension >= 150){
        i_ils = dimension/2;
      }
      else{
        i_ils = dimension;
      }

      double before = cpuTime();
      //candidatos = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
      //printSolution(candidatos);
      //rvnd(cidades);
      //printSolution(cidades);
      //printSolution(candidatos);
      //perturb(candidatos);
     // vector<int> sol = construction(0.5, valor);
      //vector<int> sol = {1, 7, 12, 6, 3, 4, 14, 5, 8, 13, 10, 9, 11, 2, 1};
      //vector<int> sol = {1,5,12,7,14,4,6,9,13,8,2,3,10,11,1};
      //vector<int> sol = {1, 11, 9, 10, 2, 13, 6, 8, 14, 3, 4, 5, 7, 12, 1};
      initializePhiMatrix(dimension);
      cidades = gils_rvnd(i_max, i_ils);
      //printSolution(cidades);
      valor = custoTotal(cidades);
      /*cout << "custo: " << valor << endl;
      double menor = std::numeric_limits<double>::infinity();
      initializePhiMatrix(dimension);

     while(fourOpt(sol, valor)){
        cout << "custo: " << valor << endl;
        cout << "custo: " << custoTotal(sol) << endl;
        printSolution(sol);
     }*/
    
  

      /*cout << "custo: " << valor << endl;
      cout << "custo: " << custoTotal(sol) << endl;
      printSolution(sol);*/
      /*vector<int> pi1;
      vector<int> pi2;
      vector<int> pi3;
      vector<int> pi4;
      vector<int> pi5;*/

       //cout << delta_best.i1 <<" " <<delta_best.j1<<" " << delta_best.i2<<" " << delta_best.j2 << " " << delta_best.costVar << endl;
  // 4,8, 12 14
      /*int i1 = 0, i2 = 6, j1 = 8, j2 = 11;
      pi1.assign(&sol[0], &sol[i1+1]);
      pi2.assign(&sol[i1+1], &sol[i2+1]);
      pi3.assign(&sol[i2+1], &sol[j1+1]);
      pi4.assign(&sol[j1+1], &sol[j2+1]);
      pi5.assign(&sol[j2+1], &sol[dimension+1]);


      for(int i = 0;  i < pi1.size(); i++){
        cout << pi1[i] << " ";
      }
      cout << "\n";
       for(int i = 0;  i < pi2.size(); i++){
        cout << pi2[i] << " ";
      }
      cout << "\n";
       for(int i = 0;  i < pi3.size(); i++){
        cout << pi3[i] << " ";
      }
      cout << "\n";
       for(int i = 0;  i < pi4.size(); i++){
        cout << pi4[i] << " ";
      }
      cout << "\n";
       for(int i = 0;  i < pi5.size(); i++){
        cout << pi5[i] << " ";
      }*/
     
      //sol = {1,5,12,7,14,4,3,10,2,6,9,13,8,2,1};
      // cout << "custo: " << custoTotal(sol) << endl;
      
      double after = cpuTime();
      //cidades = construction(0.5);
      //swap(cidades);
      //printData();
      double tempo_total = after - before;
      //cout << "\nTempo de Execucao: "<< tempo_total << endl;
      somaTempos += tempo_total;
      somaValores += valor;
    printTime();
  //}
    cout << "Valor Medio da Solucao: " << (somaValores/10) << endl;
    cout << "Tempo Medio de Execucao: " << (somaTempos/10) << " (s)" << endl;
    cout << "swap: " << melhorasSwap << " reinsert: " << melhorasReinsert << " 2-opt: " << melhoras2opt << " or-opt2: " << melhorasOrOpt2 <<" or-opt3: " <<melhorasOrOpt3 << " 4-opt: " << melhoras4opt << endl;
    //printTime();
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

vector<int> construction(double alfa, double &custo){

  double inicioconstruction = cpuTime();

  vector<int> s = {1,1};// lista de cidades da solução inicial
  vector<int> listaCandidatos;
  for(int i = 2; i <= dimension; i++){
    listaCandidatos.push_back(i); // insere todos os nós na lista de candidatos
  }

  for(int j = 0; j < 3; j++){ // tamamho subsequqncia inicial
    int k = rand() % listaCandidatos.size();
    s.insert(s.begin() + 1, listaCandidatos[k]); // adiciona cidade aleatoria a solução
    listaCandidatos.erase(listaCandidatos.begin() + k); // apaga da lista de candidatos oq ja foi pra solução
  }

  vector<CustoIn> custoInsertion = calculaCusto(listaCandidatos, s); // calcula os custo de inserção dos candidatos
  std::sort(custoInsertion.begin(), custoInsertion.end(), comp); // ordena de forma crescente de acordo com os custos

  int sel;
  while(!listaCandidatos.empty()){
    if(alfa == 0){
      sel = 0;
    }
    else{
      sel = rand() % ((int)std::floor(alfa * (custoInsertion.size() - 1)) + 1); // escolhe um nó dentro de uma faixa definida por alfa
    }

    //cout << "sel: " << sel << endl;

    s.insert(s.begin() + custoInsertion[sel].arestaOut + 1, custoInsertion[sel].noIn); // insere o nó na solucao

    for(int i = 0; i < listaCandidatos.size(); i++){
      if(listaCandidatos[i]==custoInsertion[sel].noIn)
        listaCandidatos.erase(listaCandidatos.begin() + i); // exclui o nó da lista de candidatos
    }

    custoInsertion.erase(custoInsertion.begin(), custoInsertion.begin() + custoInsertion.size()); // exclui o nó da lista de custos
    custoInsertion = calculaCusto(listaCandidatos, s); // calcula os novos custos de inserção
    std::sort(custoInsertion.begin(), custoInsertion.end(), comp); // ordena os custos

  }

  double fimConstruction = cpuTime();
  tempo_construction += (fimConstruction - inicioconstruction);

  custo = custoTotal(s);
  return s;
}

void printSolution(vector<int> anyVector){ // printa um vetor qualquer
   vector<int>::iterator v = anyVector.begin();
   while( v != anyVector.end()) {
      cout << *v << ", ";
      v++;
   }
   cout << "\n";
}

 bool comp(const CustoIn& a, const CustoIn& b) // comparação dos custos utilizada para ordenar os objetos
  {
    return a.custo < b.custo;
  }

vector<CustoIn> calculaCusto(vector<int> listaCandidatos, vector<int> &s){
  vector<CustoIn> custoInsertion ((s.size() - 1) * listaCandidatos.size());
  for(int i = 0, j = 1, l = 0; i < s.size()-1; i++, j++){
    for(auto k : listaCandidatos){
      custoInsertion[l].custo = matrizAdj[s[i]][k] +  matrizAdj[s[j]][k] - matrizAdj[s[i]][s[j]]; // custo
      custoInsertion[l].noIn = k; // nó inserido
      custoInsertion[l].arestaOut = i; // posicao de inserção;
      l++;
    }
  }


  return custoInsertion;

}

void swap(vector<int> &solucao, double &custo){ // faz a troca de posição entre dois nós

  double inicioSwap = cpuTime();
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
    melhorasSwap++;
  }
  double fimSwap = cpuTime();
  tempo_swap += (fimSwap - inicioSwap);

}

 inline double calculaDeltaSwap(int i, int j, vector<int> &s){
  double delta;
    if(i + 1 == j){
      delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[j-1]] - matrizAdj[s[i+1]][s[j+1]];
    }
    else{
    delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[j]][s[i-1]] + matrizAdj[s[j]][s[i+1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[j]][s[j+1]];
        }
  //cout << "delta swap: " << delta <<endl;
  return delta;
}

void reInsertion(vector<int> &solucao, double &custo){ // reinsere um nó em posição diferente
  double inicioreinsertion = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j = -1;
  for(int i = 1; i < solucao.size() - 1; i++){ // varre a solução exceto o 0 e o final
    for(int j = 1; j < solucao.size() - 1; j++){
      if(i != j){ // exclui a posição inicial do nó
         delta = calculaDeltaReInsertion(i,j,s);
        if(delta < 0){
          if(delta < menor){
              menor = delta;
              pos_i = i;
              pos_j = j;
          }
        }
      }
    }
  }
  if(pos_i > 0){
    solucao.erase(solucao.begin() + pos_i);
    solucao.insert(solucao.begin() + pos_j, s[pos_i]);
    custo = custo + menor;
    melhorasReinsert++;
  }
  double fimReinsertion =  cpuTime();
  tempo_reinsertion += (fimReinsertion - inicioreinsertion);
}

inline double calculaDeltaReInsertion(int i, int j, vector<int> &s){
  double delta;
  if(i <= j){
    delta = matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i-1]][s[i+1]] - matrizAdj[s[j]][s[j+1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]];
            }
  else{
  delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i]][s[j]] + matrizAdj[s[i-1]][s[i+1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i]][s[i+1]];
      }
  return delta;

}

void twoOptN(vector<int> &solucao, double &custo){ // inverte uma subsequencia da solução
  double inicio2opt = cpuTime();
  vector<int> s = solucao;
  double delta , menor = 0;
  int pos_i = -1, pos_j;
    for(int i = 1; i < solucao.size() - 2; i++){
      for(int j = i + 1; j < solucao.size() - 1; j++){
        delta = calculaDeltaTwoOpt(i,j,s);
        if(delta < 0){
          if(delta < menor){
            menor = delta;
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
    if(pos_i > 0){
      for(int k = pos_i; k <= pos_j; k++){ // invertendo as posições
        solucao[k] = s[pos_j + pos_i - k];
      }
      custo = custo + menor;
      melhoras2opt++;
    }
    double fim2opt = cpuTime();
    tempo_2opt += (fim2opt - inicio2opt);
}

inline double calculaDeltaTwoOpt(int i, int j, vector<int> &s){
  double delta;
  if(j == (i + 1)){
    delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[j-1]] - matrizAdj[s[j]][s[j+1]];
  }
  else{
  delta = matrizAdj[s[i-1]][s[j]] + matrizAdj[s[i]][s[j+1]] - matrizAdj[s[i-1]][s[i]] - matrizAdj[s[j]][s[j+1]];
  }
  return delta;
}

void orOpt2(vector<int> &solucao, double &custo){ // reinsere subsequencia de dois nós em posição diferente
  double inicioOropt2 = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j;
  for(int i = 1; i < solucao.size() - 2; i++){
    for(int j = 1; j < solucao.size() - 3; j++){
      if(i != j){
        delta = calculaDeltaOrOpt2(i,j,s);
        if(delta < 0){
          if(delta < menor){
            menor = delta;
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if(pos_i > 0){
    solucao.erase(solucao.begin() + pos_i, solucao.begin() + pos_i + 2);
    solucao.insert(solucao.begin() + pos_j, &s[pos_i], &s[pos_i] + 2);
    custo = custo + menor;
    melhorasOrOpt2++;
  }
  double fimOropt2 = cpuTime();
  tempo_orOpt2 += (fimOropt2 - inicioOropt2);
}

inline double calculaDeltaOrOpt2(int i, int j, vector<int> &s){
  double delta;
  if(i < j){
    delta = matrizAdj[s[i-1]][s[i+2]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i+1]][s[j+2]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+1]][s[i+2]] - matrizAdj[s[j+1]][s[j+2]];
  }
  else {
    delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i+1]][s[j]] + matrizAdj[s[i+2]][s[i-1]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+1]][s[i+2]];
  }

  return delta;
}

void orOpt3(vector<int> &solucao, double &custo){ // reinsere subsequencia de tres nós em posição diferente
  double inicioOropt3 = cpuTime();
  vector<int> s = solucao;
  double menor = 0;
  double delta;
  int pos_i = -1, pos_j;

  for(int i = 1; i < solucao.size() - 3; i++){
    for(int j = 1; j < solucao.size() - 4; j++){
      if(i != j){
       delta = calculaDeltaOrOpt3(i,j,s);
        if(delta < 0){
          if(delta < menor){
            menor = delta;
            pos_i = i;
            pos_j = j;
          }
        }
      }
    }
  }
  if(pos_i > 0){
    solucao.erase(solucao.begin() + pos_i, solucao.begin() + pos_i + 3);
    solucao.insert(solucao.begin() + pos_j, &s[pos_i], &s[pos_i] + 3);
    custo = custo + menor;
    melhorasOrOpt3++;
  }
  double fimOropt3 = cpuTime();
  tempo_orOpt3 += (fimOropt3 - inicioOropt3);
}


inline double calculaDeltaOrOpt3(int i, int j, vector<int> &s){
  double delta;
  if(i < j){
    delta = matrizAdj[s[i-1]][s[i+3]] + matrizAdj[s[i]][s[j+2]] + matrizAdj[s[i+2]][s[j+3]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+2]][s[i+3]] - matrizAdj[s[j+2]][s[j+3]];
  }
  else {
    delta = matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i+2]][s[j]] + matrizAdj[s[i-1]][s[i+3]] - matrizAdj[s[j]][s[j-1]] - matrizAdj[s[i]][s[i-1]] - matrizAdj[s[i+2]][s[i+3]];
  }

  return delta;
}

void rvnd(vector<int> &solucao, double &custo){
  vector<int> s = solucao;
  vector<int> nLista = {0,1,2,3,4}; // lista de estruturas
  double custoMod =  custo;
  int sel, pos;

  while(!nLista.empty()){ // roda enquanto existirem estruturas de vizinhança na lista

    int k = rand() % nLista.size();

    switch(nLista[k]){
      case 0:
        swap(solucao, custoMod);
        break;

      case 1:
        reInsertion(solucao, custoMod);
        break;

      case 2:
        twoOptN(solucao, custoMod);
        break;

      case 3:
        orOpt2(solucao, custoMod);
        break;

      case 4:
        orOpt3(solucao, custoMod);
        break;

      /*case 5:
        fourOpt(solucao, custoMod);
        break;*/
    }

    //custoMod = custoTotal(solucao); // calcula o custo do Movimento

    if(custo > custoMod){ // movimento melhorou o custo
      custo = custoMod;
      s = solucao;
    }
    else { // nao melhorou, exclui o movimento da lista
      solucao = s;
      nLista.erase(nLista.begin() + k);
      custoMod = custo;
    }

  }
  while(1){
    fourOpt(solucao, custoMod);
    if(custo > custoMod){ // movimento melhorou o custo
      custo = custoMod;
      s = solucao;
    }
    else{
      solucao = s;
      custoMod = custo;
      break;
    }

  }

}

vector<int> perturb(vector<int> &solucao){
  vector<int> s = solucao;

  int tam_max = ceil(((double)dimension)/10); // tamanho maximo das subsequencias
  int inicio1, fim1, inicio2, fim2;

  inicio1 = (rand() % ((dimension - (2 * tam_max)) - 1 + 1)) + 1; // posicao minima = 1, posicao maxima = final - 2*tmax
  fim1 = (rand() % ((inicio1 + (tam_max - 1)) - (inicio1 + 1) + 1)) + (inicio1 + 1); // minima = inicio+1, maxima = inicio1 + tmax - 1;
  inicio2 = (rand() % ((dimension - tam_max) - (fim1 + 1) + 1) + (fim1 + 1)); // minima = fim1 + 1, maxima = final - tmax;
  fim2 = (rand() % ((inicio2 + (tam_max - 1)) - (inicio2 + 1) + 1) + (inicio2 + 1)); // minima = inicio2 + 1, maxima = inicio2 + tmax - 1;


  int d1 = fim1 - inicio1; // tamanho da primeira subsequencia, usado para corrigir erros na inserção
  int d2 = fim2 - inicio2; // tamanho da segunda subsequencia, usado pra corrigir erros na inserção


  //cout << "inicio1: " << ini1 << "fim1: " << fim1 << "inicio2: " << ini2 << "fim2: " << fim2 << endl;

  s.erase(s.begin() + inicio2, s.begin() + fim2 + 1); // apaga primeira subsequencia
  s.erase(s.begin() + inicio1, s.begin() + fim1 + 1); // apaga segunda subsequencia
  s.insert(s.begin() + inicio1, &solucao[inicio2], &solucao[fim2] + 1);  // inclui a segunda subsequencia na posicao da primeira
  s.insert(s.begin() + inicio2 + (-1*(d1 - d2)) , &solucao[inicio1], &solucao[fim1] + 1); // inclui a segunda subsequencia na posicao da segunda



  return s;

}

vector<int> gils_rvnd(int i_max, int i_ils){
  double ff = numeric_limits<double>::infinity(); // custo final
  vector<int> s, s1, sf; // s, s', s*
  double fs, fs1;
  for (int i = 0; i < i_max; i++){
    cout << "ILS: "<< i << endl;
    double alfa = (double)rand() / RAND_MAX; // gera aleatorio entre 0 e 1
    s = construction(alfa, fs); // constroi solucao inicial
    s1 = s;
    fs1 = fs;
    int iter_ILS = 0;
    while (iter_ILS < i_ils){
      rvnd(s, fs); // explora as estruturas de vizinhança
      if (fs < fs1){
        s1 = s;
        fs1 = fs;
        iter_ILS = 0;
      }
      s = perturb(s1); // perturba a solução evitando resultado ótimo local
      fs = custoTotal(s);
      iter_ILS++;
    }
    if (fs1 < ff){
      sf = s1;
      ff = fs1;
    }
  }
  return sf; // retorna a melhor solucao
}

inline double custoTotal(vector<int> &solucao){ // explora a matriz e retorna o custo de uma solucao
  double custo = 0;
  for(int i = 0, j = 1; i < solucao.size() - 1; i++, j++){
     custo = custo + matrizAdj[solucao[i]][solucao[j]];
  }
  return custo;
}

double cpuTime() {
	static struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	return ((double)usage.ru_utime.tv_sec)+(((double)usage.ru_utime.tv_usec)/((double)1000000));
}

void printTime(){
  cout << "Tempo medio de execucao da SI: " << (tempo_construction/10) << " (s)";
  cout << "\n" << "Tempo medio de execucao da troca: " << (tempo_swap/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt: " << (tempo_reinsertion/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt2: " << (tempo_orOpt2/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do Or-opt3: " << (tempo_orOpt3/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do 2-opt: " << (tempo_2opt/10)<< " (s)";
  cout << "\n" << "Tempo medio de execucao do 4-opt: " << (tempo_4opt/10)<< " (s)";

  cout << "\n\n";
}


double deltaX(vector<int> &s, int x, int i, int j){

  /*if x == 'c'
        cost_add = D.cost[r[i], r[j]] + D.cost[r[i + 1], r[j + 1]] # Cost of a connecting 2-opt.
    else
        cost_add = D.cost[r[i], r[j + 1]] + D.cost[r[i + 1], r[j]] # Cost of a disconnecting 2-opt.
    end

    return cost_add - D.cost[r[i], r[i + 1]] - D.cost[r[j], r[j + 1]]*/

  double delta;
  if(x == 0)
    delta = matrizAdj[s[i]][s[j]] + matrizAdj[s[i+1]][s[j+1]];
  else
    delta = matrizAdj[s[i]][s[j+1]] + matrizAdj[s[i+1]][s[j]];

  return delta - matrizAdj[s[i]][s[i+1]] - matrizAdj[s[j]][s[j+1]];
}

void movefourOpt(vector<int> &s, double &cost, FourOptMoveData d){

  vector<int> newSolution;

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

void fourOpt(vector<int> &s, double &cost){

  int n = s.size();
  double inicio4opt = cpuTime();
  double fim4opt;

  /*for(int i2 = 0; i2 < n-1; i2++){
    for(int j2 = 0; j2 < n; j2++){
      for(int x = 0; x <= 1; x++){
        cout << phi[x][i2][j2].cost << endl;
      }
    }
  }*/

  //cout << "phi " <<phi[1][14][14].cost << endl; 

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
            phiSub[x][i2][j1].cost = deltaX(s,x,0,j1);
          }
          else{
            if(phiSub[x][i2 - 1][j1].cost < deltaX(s,x,i2-1,j1))
              phiSub[x][i2][j1] = phiSub[x][i2-1][j1];
            else{
              phiSub[x][i2][j1].i = i2-1;
              phiSub[x][i2][j1].j = j1;
              phiSub[x][i2][j1].cost = deltaX(s,x,i2-1,j1);
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
      delta_type1 = deltaX(s, 1, i2, j2) + phi[1][i2][j2].cost; // Two disconnecting 2-opts.
      delta_type2A = deltaX(s, 1, i2, j2) + phi[0][i2][j2].cost; // A connecting and a disconnecting 2-opt;
      delta_type2B = deltaX(s, 0, i2, j2) + phi[1][i2][j2].cost; // A connecting and a disconnecting 2-opt.

      
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
    tempo_4opt += (fim4opt - inicio4opt);
    melhoras4opt++;
    return;
  }
  fim4opt = cpuTime();
  tempo_4opt += (fim4opt - inicio4opt);


  /*for(int j1 = 2; j1 <= n-1; j1++){
    for(int i2 = 1; i2 <= j1-1; i2++){
      for(int x = 0; x <= 1; x++){
        if(i2 == 1){
          phiSub[x][i2][j1].cost = deltaX(s,x,0,j1);
        }
        else{
          phiSub[x][i2][j1].cost = min(phiSub[x][i2-1][j1].cost, deltaX(s, x, i2-1, j1));
        }
      }
    }
  }

  for(int i2 = 1; j1 < n-1; i2++){
    for(int j2 = i2+2; i2 <= n; j2++){
      for(int x = 0; x <= 1; x++){
        if(j2 == i2+2){
          phi[x][i2][j2].cost = phiSub[x][i2][i2+1].cost;
        }
        else{
          phi[x][i2][j1].cost = min(phi[x][i2][j2-1].cost, phiSub[x][i2][j2-1].cost);
        }
      }
    }
  }*/

 /* double delta_type1 = deltaX(s, 1, i2, j2) + phi[1][i2][j2].cost; // Two disconnecting 2-opts.
  double delta_type2A = deltaX(s, 1, i2, j2) + phi[0][i2][j2].cost; // A connecting and a disconnecting 2-opt;
  double delta_type2B = deltaX(s, 0, i2, j2) + phi[1][i2][j2].cost; // A connecting and a disconnecting 2-opt.

  FourOptMoveData delta_best = {0, 0, -1, -1, -1, -1, 0.0};
  //cout << "i: " << i2 << " j: " << j2 << " phi: " << phi[1][i2][j2].cost << endl;
  //cout << delta_type1 << " " << delta_type2A << " " << delta_type2B << endl;

  double best_cost_var = min({ delta_best.costVar, delta_type1, delta_type2A, delta_type2B });
  //cout << "best " << best_cost_var << endl;
  if (best_cost_var == delta_type1)
      delta_best = (FourOptMoveData){1, 1, phi[1][i2][j2].i, phi[1][i2][j2].j, i2, j2, delta_type1};
  else if (best_cost_var == delta_type2A)
      delta_best = (FourOptMoveData){0, 1, phi[0][i2][j2].i, phi[0][i2][j2].j, i2, j2, delta_type2A};
  else if (best_cost_var == delta_type2B)
      delta_best = (FourOptMoveData){1, 0, phi[1][i2][j2].i, phi[1][i2][j2].j, i2, j2, delta_type2B};*/
   
 // cout << phi[1][i2][j2].i << endl;
  //cout << delta_best.i1 <<" " <<delta_best.j1<<" " << delta_best.i2<<" " << delta_best.j2 << endl;
  //movefourOpt(s,cost,delta_best);
}