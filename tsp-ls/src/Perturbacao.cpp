
#include "Perturbacao.h"


vector<int> perturb(vector<int> &solucao, int dimension, vector<int> &solucaoInvertida)
{
  vector<int> s = solucao;

  int tam_max = ceil(((double)dimension) / 10); // tamanho maximo das subsequencias
  int inicio1, fim1, inicio2, fim2;

  inicio1 = (rand() % ((dimension - (2 * tam_max)) - 1 + 1)) + 1;                    // posicao minima = 1, posicao maxima = final - 2*tmax
  fim1 = (rand() % ((inicio1 + (tam_max - 1)) - (inicio1 + 1) + 1)) + (inicio1 + 1); // minima = inicio+1, maxima = inicio1 + tmax - 1;
  inicio2 = (rand() % ((dimension - tam_max) - (fim1 + 1) + 1) + (fim1 + 1));        // minima = fim1 + 1, maxima = final - tmax;
  fim2 = (rand() % ((inicio2 + (tam_max - 1)) - (inicio2 + 1) + 1) + (inicio2 + 1)); // minima = inicio2 + 1, maxima = inicio2 + tmax - 1;

  int d1 = fim1 - inicio1; // tamanho da primeira subsequencia, usado para corrigir erros na inserção
  int d2 = fim2 - inicio2; // tamanho da segunda subsequencia, usado pra corrigir erros na inserção

  //cout << "inicio1: " << ini1 << "fim1: " << fim1 << "inicio2: " << ini2 << "fim2: " << fim2 << endl;

  s.erase(s.begin() + inicio2, s.begin() + fim2 + 1);                                      // apaga primeira subsequencia
  s.erase(s.begin() + inicio1, s.begin() + fim1 + 1);                                      // apaga segunda subsequencia
  s.insert(s.begin() + inicio1, &solucao[inicio2], &solucao[fim2] + 1);                    // inclui a segunda subsequencia na posicao da primeira
  s.insert(s.begin() + inicio2 + (-1 * (d1 - d2)), &solucao[inicio1], &solucao[fim1] + 1); // inclui a segunda subsequencia na posicao da segunda

  for (int i = 0; i < solucaoInvertida.size(); i++)
  {
    solucaoInvertida[s[i]] = i;
  }

  return s;
}