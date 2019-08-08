#include "readData.h"
#include <fstream>
#include <iostream>

using namespace std;

int *OptimalRoute; // vetor de solucão
int dimension; // quantidade total de vertices
double ** matrizAdj; // matriz de adjacencia
double ** matrizDist; // matriz reorganizada;


void printData();
void printBestSolution();

int main(int argc, char** argv) {
    readData(argc, argv, &dimension, &matrizAdj);
    readSolution(argc, argv, &dimension, &OptimalRoute);
    printData();
    printBestSolution();



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


void printBestSolution() {
  cout << "dimension: " << dimension << endl;
  for (int i = 0; i < dimension + 1; i++) {
      cout << OptimalRoute[i] << endl;
    }
    //cout << endl;
  }
