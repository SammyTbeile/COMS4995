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

/* get_code_indexes */
unsigned long get_code_indexes(string& origin,
unordered_map<string, unsigned long> code_index_map) {
  bool bad_origin = false;
  unsigned long origin_index;

  try {
    origin_index = code_index_map.at(origin);
  } catch(out_of_range& e) {
    bad_origin = true;
  }

  if(bad_origin ) {
    cerr << "\nTerimating: The origin airport code provided was not found" << endl;
    exit(1);
  }
  return origin_index;
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
  auto index_code_vector = get<1>(matrix_tuple);
  auto code_index_map    = get<2>(matrix_tuple);
  auto graph             = Graph(matrix);

  // Get Index
  // auto code_indexes = get_code_indexes(origin, code_index_map);
  auto origin_index = get_code_indexes(origin,code_index_map);

  cerr << "Running Prim's..." << endl;

  // Stopwatch
  Stopwatch stopwatch = Stopwatch();
  stopwatch.start();

  // Algorithm
  auto res = Algorithms::Prims(graph, origin_index); 
  stopwatch.stop();
  cerr <<"Finished Prim's" <<endl;
  
  // Printing
  cout << setprecision(8);
  for(auto i=0;i<res.size();i++ ) {
      auto currentList = res[i];
      auto code     = index_code_vector[currentList[0].first];
      auto gps_pair = code_gps_map[code];
      auto lat      = gps_pair.first;
      auto lng      = gps_pair.second;
      auto weight   = currentList[0].second;
      // cout<<currentList[0].first<<endl;

      cout << fixed << setw(11) << lat << ", " << setw(11) << lng << ", "
        << 0.0 << setw(4) << weight << ", " << code << ", "; //underscore delimits different neighbors
      for(auto j =1; j<currentList.size();j++){
          auto in_code     = index_code_vector[currentList[j].first];
          auto in_gps_pair = code_gps_map[in_code];
          auto in_lat      = in_gps_pair.first;
          auto in_lng      = in_gps_pair.second;
          auto in_weight      = currentList[j].second;

          cout << fixed << setw(11) << in_lat << "; " <<setw(11) << in_lng << ";"
            << 0.0 << setw(4) << in_weight << "; " << in_code << "; " << "_ ";
      }
    cout << endl;
  }

  cerr << "\nElapsed Time: " << stopwatch.elapsed() << endl;

  return 0; 
}
