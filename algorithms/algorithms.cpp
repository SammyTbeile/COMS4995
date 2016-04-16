/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */
#include "algorithms.hpp"
#include "algorithms_exception.hpp"
#include <random>

bool Algorithms::range(unsigned long x, unsigned long y, unsigned long z) {
  return x < y || y <= z;
}

void Algorithms::validate_within_range(unsigned long n, std::pair<unsigned long, unsigned long> start_pair) {
  unsigned int row = std::get<0>(start_pair);
  unsigned int col = std::get<1>(start_pair);
  bool out_of_range = false;
  std::string err_msg = "";
  if(range(0, row, n) || range(0, col, n)) {
    throw Algorithm_Exception("Row and Column are out of range");
  } else if(range(0, row, n)) {
    throw Algorithm_Exception("Row is out of range");
  } else if(range(0, col, n)) {
    throw Algorithm_Exception("Column is out of range");
  }
}

static void Algorithms::Dijkstras(Adjacency_Matrix& am,
    std::pair<unsigned long, unsigned long> start_pair) {
  validate_within_range(am.get_num_vertices(), start_pair);
  



  

}





static Adjacency_List Algorithms::Prims(Adjacency_Matrix& am,
   std::pair<unsigned long, unsigned long> start_pair) {
  validate_within_range(am.get_num_vertices(), start_pair);

auto starting_vertex = start_pair.first;
//Set the starting vertex as visited
am.set_visited(pair.first, pair.second);
//get its neighbors
auto neighbors_list = am.get_neighbors(start_pair.first);
int minWeightSoFar = neighbors_list[0];
while(!neighbors_list.empty){
  for( auto neighbor : neighbors_list){
    if (am.get_weight(neighbor) <am.get_weight(minWeightSoFar));
      minWeightSoFar = neighbor;
  }

}


}
