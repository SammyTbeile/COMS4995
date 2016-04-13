/*
 * Filename: algorithms.cpp
 * Authors:  Sean Garvey
 * UNIs:     sjg2174
 */
#include "algorithms.hpp"

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
