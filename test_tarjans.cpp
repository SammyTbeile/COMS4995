
#include <iomanip>
#include <iostream>

#include "algorithms.hpp"
#include "stopwatch.hpp"
#include "test_helper.hpp"

using namespace std;


int main(int argc, char **argv) {

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
 // auto code_indexes = get_code_indexes(code_index_map);

  cerr << "Running Tarjans..." << endl;

  // Stopwatch
  Stopwatch stopwatch = Stopwatch();
  stopwatch.start();

  // Algorithm
  auto res = Algorithms::Tarjans(graph); 
  stopwatch.stop();

  // Printing
  cout << setprecision(8);
  for(auto& e : res) {
    auto code     = index_code_vector[e];
    auto gps_pair = code_gps_map[code];
    auto lat      = gps_pair.first;
    auto lng      = gps_pair.second;
    cout << fixed << setw(11) << lat << ", " << setw(11) << lng << ", "
      << 0.0 << setw(4) << ", " << code << '\n';
  }

  cerr << "\nElapsed Time: " << stopwatch.elapsed() << endl;

  return 0; 
}
