/*
 * Filename: adjacency_matrix.cpp
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

#include "adjacency_matrix.h"

bool check_nxn(std::vector<std::vector<double>> am) {
  int size = am.size();
  for(auto &row : am) {
    if(row.size() != size) {
      return false;
    }
  }
  return true;
}

/*
Adjacency_Matrix::Adjacency_Matrix(std::array<std::array<double, int>, int> array) {
  matrix = std::vector<std::vector<double>>();
  for(auto &row : array){
    std::vector<double> temp;
    for(auto &col : row){
	temp.push_back(col);
    }
     matrix.push_back(temp);
  }
  if(check_nxn(matrix) == false) {
    throw exception;
  }
  num_vertices = matrix.size();
}
*/

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<double>> vector) {
  matrix = std::vector<std::vector<double>>();
  for(auto &row : vector) {
    for(auto &col : row) {
      row.push_back(col);
    }
  }
  if(check_nxn(matrix) == false) {
    throw;
  }
  num_vertices = matrix.size();
}

Adjacency_Matrix& operator=(const Adjacency_Matrix& am) {
  if(this == am) {
    return *this;
  }
  for(auto i =0; i<am.get_n();i++) {
    for(auto j =0;j<am.get_n();j++) {
      this.matrix[i][j]= am.matrix[i][j];
    }
  }
  this.num_vertices = am.get_n();
  return *this;
}



int Adjacency_Matrix::get_num_vertices() {
  return num_vertices;
}

std::vector<double> Adjacency_Matrix::get_neighbors(int vertex){
  return matrix[vertex];
}

double Adjacency_Matrix::get_weight(int row, int col) {
  return matrix[row][col];
}

std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix& am) {
  for(auto &row : am.matrix) {
    for(auto &col : row) {
      os << col << " ";
    }
    os << '\n';
  }
  return os;
}
