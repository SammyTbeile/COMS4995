/*
 * Filename: tester.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iostream>
#include "algorithms.hpp"
#include "graph.hpp"
#include "graph_helper.hpp"
#include "create_tuple.hpp"

using namespace std;

int main() {
  auto helper_map_tuple = create_matrix_graph_helper_code_gps_map_tuple();

  auto graph_helper = get<0>(helper_map_tuple);
  auto code_gps_map = get<1>(helper_map_tuple);
  auto matrix_vector_tuple = graph_helper.get_adjacency_matrix_associative_vector_tuple();
  auto adjacency_matrix   = get<0>(matrix_vector_tuple);
  auto associative_vector = get<1>(matrix_vector_tuple);

  auto graph = Graph(adjacency_matrix);
  auto res = Algorithms::BellFord(graph, 0, 1);

  for(auto& e : res) {
    auto code = associative_vector[e.first];
    auto gps_pair = code_gps_map[code];
    auto weight = e.second;
    cout << gps_pair.first << ',' << gps_pair.second << ',' << weight << ',' << code << '\n';
  }

  return 0; 
}
