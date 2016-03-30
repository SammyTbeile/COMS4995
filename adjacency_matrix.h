#ifndef __ADJACENCY_MATRIX_H__
#define __ADJACENCY_MATRIX_H__
/*
 * Filename: adjacency_matrix.h
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

#include <vector>
#include <iostream>

class Adjacency_Matrix {
public:
  Adjacency_Matrix(std::vector<std::vector<double>> vector);
  Adjacency_Matrix(const Adjacency_Matrix& am);
  Adjacency_Matrix& operator=(const Adjacency_Matrix& am);
  int get_num_vertices() const;
  double get_weight(int row, int col);
  std::vector<double> get_neighbors(int vertex);
  friend std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix& am);
  
private:
  std::vector<std::vector<double>> matrix;
  std::vector<std::vector<bool>>   visited;
  int num_edges;
  int num_vertices;
};

#endif
