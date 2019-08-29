
#include "GILSRVND.h"

vector<int> gils_rvnd(int i_max, int i_ils,  int dimension, double &tempo_construction , double &tempo_swap, double &tempo_reinsertion, double &tempo_2opt, double &tempo_orOpt2, double &tempo_orOpt3,
vector<int> &solucaoInvertida, double** matrizAdj, vector<vector<int>> &matrizOrg)
{

  double ff = numeric_limits<double>::infinity(); // custo final
  vector<int> s, s1, sf;                          // s, s', s*
  double fs, fs1;
  for (int i = 0; i < i_max; i++)
  {

    double alfa = (double)rand() / RAND_MAX; // gera aleatorio entre 0 e 1
    s = construction(alfa, fs, dimension, tempo_construction, solucaoInvertida, matrizAdj); // constroi solucao inicial
    s1 = s;
    fs1 = fs;
    int iter_ILS = 0;
    while (iter_ILS < i_ils)
    {
      //cout << "RVND " << i << endl;
      rvnd(s, fs, dimension, tempo_swap, tempo_reinsertion, tempo_2opt, tempo_orOpt2, tempo_orOpt3, solucaoInvertida, matrizAdj, matrizOrg); // explora as estruturas de vizinhança
      if (fs < fs1)
      {
        s1 = s;
        fs1 = fs;
        iter_ILS = 0;
      }
      s = perturb(s1, dimension, solucaoInvertida); // perturba a solução evitando resultado ótimo local
      fs = custoTotal(s, matrizAdj);
      iter_ILS++;
    }
    if (fs1 < ff)
    {

      sf = s1;
      ff = fs1;
    }
  }
  return sf; // retorna a melhor solucao
}
