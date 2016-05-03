/*
 * Filename: test_prims.cpp
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */

#include <iomanip>
#include <iostream>

#include "algorithms.hpp"
#include "stopwatch.hpp"
#include "test_helper.hpp"

using namespace std;

int main(int argc, char **argv) {

  // Handle Arguments
  if(argc != 1) {
    cerr << "usage: " << argv[0] << endl;
    exit(1);
  }

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

  cerr << "Running Prim's..." << endl;

  // Stopwatch
  Stopwatch stopwatch = Stopwatch();
  stopwatch.start();

  // Algorithm
  auto res = Algorithms::Prims(graph); 
  stopwatch.stop();
  cerr <<"Finished Prim's" <<endl;
  
  // Printing
  cout << fixed;
  auto len = res.size();
  for(auto i = 0; i < len; ++i) {
      auto currentList = res[i];
      auto code     = index_code_vector[currentList[0].first];
      auto gps_pair = code_gps_map[code];
      auto lat      = gps_pair.first;
      auto lng      = gps_pair.second;
      auto weight   = currentList[0].second;
      cout << setprecision(8) << setw(12) << lat << ", " << setw(13) << lng << ", "
        << setprecision(0) << setw(6) << weight << ", " << code << ", ";
      if(currentList.size() > 1) {
        auto in_code     = index_code_vector[currentList[1].first];
        auto in_gps_pair = code_gps_map[in_code];
        auto in_lat      = in_gps_pair.first;
        auto in_lng      = in_gps_pair.second;
        auto in_weight   = currentList[1].second;

        cout << setprecision(8) << setw(12) << in_lat << "; " << setw(13) << in_lng << "; "
          << setprecision(0) << setw(6) << in_weight << "; " << in_code;
      }
    cout << endl;
  }

  cerr << "\nElapsed Time: " << stopwatch.elapsed() << endl;

  return 0; 
}
