#ifndef __ADJACENCY_MATRIX_H__
#define __ADJACENCY_MATRIX_H__
/*
 * Filename: adjacency_matrix.h
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

#include <array>
#include <exception>
#include <list>
#include <vector>
#include <iostream>

/* Exception */
class Adjacency_Matrix_Exception : public std::exception {
private:
  const char* message;
public:
  Adjacency_Matrix_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

class Adjacency_Matrix {
private:
  /* Variables */
  std::vector<std::vector<double>> matrix;
  std::vector<std::vector<bool>> visited;
  unsigned long num_edges;
  unsigned long num_vertices;

  /* Methods */
  bool is_square();

public:
  /* Constructors */
  template<typename Container>
  Adjacency_Matrix(Container container);
  Adjacency_Matrix(const Adjacency_Matrix& am);

  /* Methods */
  unsigned long get_num_edges();
  unsigned long get_num_vertices();
  double get_weight(unsigned long row, unsigned long col);
  std::vector<double>& get_neighbors(unsigned long row);

  /* Operators */
  Adjacency_Matrix& operator=(const Adjacency_Matrix& am);
  friend std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix& am);
};

/* valid */
bool Adjacency_Matrix::is_square() {
  unsigned int rowSize = matrix.size();
  for(auto &row : matrix) {
    if(row.size() != rowSize) {
      return false;
    }
  }
  return true;
}

/* Constructor */
template<typename Container>
Adjacency_Matrix::Adjacency_Matrix(Container container) {
  matrix = std::vector<std::vector<double>>();
  for(auto it = container.begin(); it != container.end(); ++it) {
    matrix.push_back(std::vector<double>(it->begin(), it->end()));
  }
  if(!is_square()) {
    throw Adjacency_Matrix_Exception("Graph representation is not square\n");
  }
}

/* Copy Constructor */
Adjacency_Matrix::Adjacency_Matrix(const Adjacency_Matrix& am) {
  matrix = am.matrix;
  num_edges = am.num_edges;
  num_vertices = am.num_vertices;

}

/* get_num_edges */
unsigned long Adjacency_Matrix::get_num_edges() {
  return num_edges;
}

/* get_num_vertices */
unsigned long Adjacency_Matrix::get_num_vertices() {
  return num_vertices;
}

/* get weight */
double Adjacency_Matrix::get_weight(unsigned long row, unsigned long col) {
  return matrix[row][col];
}

/* get neighbors */
std::vector<double>& Adjacency_Matrix::get_neighbors(unsigned long row) {
  return matrix[row];
}

/* = */
Adjacency_Matrix& Adjacency_Matrix::operator=(const Adjacency_Matrix& am) {
  if(this == &am) {
    return *this;
  }
  matrix = am.matrix;
  num_edges = am.num_edges;
  num_vertices = am.num_vertices;
  return *this;
}

/* << */
std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix& am) { 
  for(auto &row : am.matrix) {
    for(auto &col : row) {
      os << col << " ";
    }
    os << '\n';
  }
  
  return os;
}

#endif
