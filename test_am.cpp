#include <array>
#include <iostream>
#include <vector>
#include "adjacency_matrix.h"

using namespace std;

int main() {
  vector<vector<double>> vvd = vector<vector<double>>();
  int n = 10;
  for(int i = 0; i < n; ++i) {
    vvd.push_back(vector<double>());
    for(int j = 0; j < n; ++j) {
      vvd[i].push_back(j);
    }
  }

  Adjacency_Matrix am = Adjacency_Matrix(vvd);
  cout << am;
  return 0;
}
