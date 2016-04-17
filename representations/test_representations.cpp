/*
 * Filename: test_representations.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iostream>

#include "graph_helper.hpp"
#include "create_representations.hpp"

using namespace std;

int main() {
  /*
  auto my_tuple = create_matrix_representation();

  vector<vector<double>> matrix = get<0>(my_tuple);
  unordered_map<unsigned long, string> vertex_code_map = get<1>(my_tuple);
  unordered_map<string, pair<double, double>> code_gps_map = get<2>(my_tuple);

  unsigned long rows = 1;
  unsigned long size = matrix.size();
  for(unsigned long i = 0; i < size; ++i) {
    for(unsigned long j = 0; j < size; ++j) {
      if(matrix[i][j] > 0) {
        cout << vertex_code_map[i] << ' ' << vertex_code_map[j] << ' ' << matrix[i][j] << '\n';
        rows++;
      }
    }
  }

  cout << rows << " rows" << endl;
  */
  cout << "hello world" << endl;
  return 0;
}
