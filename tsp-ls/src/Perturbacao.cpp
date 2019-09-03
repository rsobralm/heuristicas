
#include "Perturbacao.h"


vector<int> perturb(vector<int> &solution, int n, vector<int> &positionList)
{
  vector<int> s = solution;

  int maxSize = ceil(((double)n) / 10); // tamanho maximo das subsequencias
  int init1, end1, init2, end2;

  init1 = (rand() % ((n - (2 * maxSize)) - 1 + 1)) + 1;                    // posicao minima = 1, posicao maxima = final - 2*tmax
  end1 = (rand() % ((init1 + (maxSize - 1)) - (init1 + 1) + 1)) + (init1 + 1); // minima = inicio+1, maxima = init1 + tmax - 1;
  init2 = (rand() % ((n - maxSize) - (end1 + 1) + 1) + (end1 + 1));        // minima = end1 + 1, maxima = final - tmax;
  end2 = (rand() % ((init2 + (maxSize - 1)) - (init2 + 1) + 1) + (init2 + 1)); // minima = init2 + 1, maxima = init2 + tmax - 1;

  int d1 = end1 - init1; // tamanho da primeira subsequencia, usado para corrigir erros na inserção
  int d2 = end2 - init2; // tamanho da segunda subsequencia, usado pra corrigir erros na inserção

  //cout << "init1: " << ini1 << "end1: " << end1 << "init2: " << ini2 << "end2: " << end2 << endl;

  s.erase(s.begin() + init2, s.begin() + end2 + 1);                                      // apaga primeira subsequencia
  s.erase(s.begin() + init1, s.begin() + end1 + 1);                                      // apaga segunda subsequencia
  s.insert(s.begin() + init1, &solution[init2], &solution[end2] + 1);                    // inclui a segunda subsequencia na posicao da primeira
  s.insert(s.begin() + init2 + (-1 * (d1 - d2)), &solution[init1], &solution[end1] + 1); // inclui a segunda subsequencia na posicao da segunda

  for (int i = 0; i < positionList.size(); i++)
  {
    positionList[s[i]] = i;
  }

  return s;
}