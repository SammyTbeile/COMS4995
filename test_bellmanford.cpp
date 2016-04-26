/*
 * Filename: test_dijkstras.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <iomanip>
#include <iostream>

#include "algorithms.hpp"
#include "stopwatch.hpp"
#include "test_helper.hpp"

using namespace std;

/* get_code_indexes */
pair<unsigned long, unsigned long> get_code_indexes(string& origin,
string& destin, unordered_map<string, unsigned long> code_index_map) {
  bool bad_origin = false;
  bool bad_destin = false;
  unsigned long origin_index;
  unsigned long destin_index;

  try {
    origin_index = code_index_map.at(origin);
  } catch(out_of_range& e) {
    bad_origin = true;
  }
  try {
    destin_index = code_index_map.at(destin);
  } catch(out_of_range& e) {
    bad_destin = true;
  }

  if(bad_origin && bad_destin) {
    cerr << "\nTerminating: The origin & destin airport codes provided were not found" << endl;
    exit(1);
  } else if(bad_origin) {
    cerr << "\nTerinating: The origin airport code provided was not found" << endl;
    exit(1);
  } else if(bad_destin) {
    cerr << "\nTerinating: The destin airport code provided was not found" << endl;
    exit(1);
  }

  return make_pair(origin_index, destin_index);
}

int main(int argc, char **argv) {

  // Handle Arguments
  if(argc != 3) {
    cerr << "usage: " << argv[0] << " <origin> <destin>" << endl;
    exit(1);
  }
  string origin = argv[1];
  string destin = argv[2];

  cerr << "Initializing..." << flush;

  // Database
  connect_database();
  auto code_gps_map = make_code_gps_map();
  auto graph_helper = make_graph_helper(MATRIX);
  disconnect_database();

  // Graph Data Structures
  auto matrix_tuple      = graph_helper.get_matrix_tuple();
  auto matrix            = get<0>(matrix_tuple);
  auto index_code_vector = get<1>(matrix_tuple);
  auto code_index_map    = get<2>(matrix_tuple);
  auto graph             = Graph(matrix);

  // Get Index
  auto code_indexes = get_code_indexes(origin, destin, code_index_map);
  auto origin_index = get<0>(code_indexes);
  auto destin_index = get<1>(code_indexes);

  cerr << "Running BellmanFord..." << endl;

  // Stopwatch
  Stopwatch stopwatch = Stopwatch();
  stopwatch.start();

  // Algorithm
  auto res = Algorithms::BellFord(graph, origin_index, destin_index);
  stopwatch.stop();

  // Printing
  cout << setprecision(8);
  for(auto& e : res) {
    auto code     = index_code_vector[e.first];
    auto gps_pair = code_gps_map[code];
    auto lat      = gps_pair.first;
    auto lng      = gps_pair.second;
    auto weight   = e.second;
    cout << fixed << setw(11) << lat << ", " << setw(11) << lng << ", "
      << defaultfloat << setw(4) << weight << ", " << code << '\n';
  }

  cerr << "\nElapsed Time: " << stopwatch.elapsed() << endl;

  return 0; 
}
