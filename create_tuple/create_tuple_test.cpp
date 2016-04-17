/*
 * Filename: create_tuple_test.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iomanip>
#include <iostream>

#include "create_tuple.hpp"

using namespace std;

int main() {
  auto matrix_graph_helper_code_gps_map_tuple =
    create_matrix_graph_helper_code_gps_map_tuple();

  auto matrix_graph_helper =
    get<0>(matrix_graph_helper_code_gps_map_tuple);

  auto adjacency_matrix_associative_vector_tuple =
    matrix_graph_helper.get_adjacency_matrix_associative_vector_tuple();

  auto matrix =
    get<0>(adjacency_matrix_associative_vector_tuple);

  auto associative_vector =
    get<1>(adjacency_matrix_associative_vector_tuple);

  auto code_gps_map =
    get<1>(matrix_graph_helper_code_gps_map_tuple);

  cout << fixed << setprecision(8);
  unsigned long rows = 1;
  unsigned long size = matrix.size();
  for(unsigned long i = 0; i < size; ++i) {
    for(unsigned long j = 0; j < size; ++j) {
      if(matrix[i][j] > 0) {
        auto origin_gps = code_gps_map[associative_vector[i]];
        auto destin_gps = code_gps_map[associative_vector[j]];
        cout << fixed
             << associative_vector[i] << ": (" << setw(11) << origin_gps.first
             << ", " << setw(13) << origin_gps.second << ")   "
             << associative_vector[j] << ": (" << setw(11) << destin_gps.first
             << ", " << setw(13) << destin_gps.second << ")   "
             << defaultfloat << matrix[i][j] << '\n';
        ++rows;
      }
    }
  }
  cout << rows << " rows" << endl;
  return 0;
}
