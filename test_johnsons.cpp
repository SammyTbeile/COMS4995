/*
 * Filename: test_johnsons.cpp
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
    cerr << "\nTerminating: The origin airport code provided was not found" << endl;
    exit(1);
  } else if(bad_destin) {
    cerr << "\nTerminating: The destin airport code provided was not found" << endl;
    exit(1);
  }

  return make_pair(origin_index, destin_index);
}

int main(int argc, char **argv) {

  // Handle Arguments
	if(argc != 2) {
    cerr << "usage: " << argv[0] << " <origin> " << endl;
    exit(1);
  }
  string origin = argv[1];

  cerr << "Initializing..." << flush;

  // Database
  connect_database();
  auto code_gps_map = make_code_gps_map();
  auto graph_helper = make_graph_helper(MATRIX);
  disconnect_database();

  // Graph Data Structures
  auto matrix_tuple      = graph_helper.get_matrix_tuple();
  auto matrix            = get<0>(matrix_tuple);
  auto code_index_map    = get<1>(matrix_tuple);
  auto index_code_vector = get<2>(matrix_tuple);
  auto graph             = Graph(matrix);

  cerr << "Running Johnsons..." << endl;

	auto code_indexes = get_code_indexes(origin,origin,code_index_map);
	auto origin_index = get<0>(code_indexes);

  // Stopwatch
  Stopwatch stopwatch = Stopwatch();
  stopwatch.start();

  // Algorithm

  auto res = Algorithms::Johnsons(graph);
	stopwatch.stop();

  // Printing
  cout << fixed;
	for(auto& path: res[origin_index]) {
    for(auto& e: path) {		
      auto code     = index_code_vector[e.first];
      auto gps_pair = code_gps_map[code];
      auto lat      = gps_pair.first;
      auto lng      = gps_pair.second;
      auto weight   = e.second;
      cout << setprecision(8) << setw(12) << lat << ", " << setw(13) << lng << ", "
        << setprecision(0) << setw(6) << weight << ", " << code << '\n';
		}
		cout << "done" << endl;
	}

  cerr << "\nElapsed Time: " << stopwatch.elapsed() << endl;

  return 0; 
}
