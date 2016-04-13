#ifndef __ADJACENCY_MATRIX_HPP__
#define __ADJACENCY_MATRIX_HPP__
/*
 * Filename: adjacency_matrix.hpp
 * Authors:  Sean Garvey
 * UNIs:     sjg2174
 */

#include <exception>
#include <vector>
#include <iostream>
#include "algorithms.hpp"

/* Exception */
class Adjacency_Matrix_Exception : public std::exception {
private:
  const char* message;
public:
  Adjacency_Matrix_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

class Adjacency_Matrix {
  friend class Algorithms;
  private:
    /* Variables */
    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<bool>> visited;
    unsigned long num_edges;
    unsigned long num_vertices;

    /* Methods */
    void count_edges();
    bool has_non_negative_edges();
    bool is_square();
    void set_visited(unsigned long row, unsigned long col, bool b);

  public:
    /* Constructors */
    template<typename Container>
    Adjacency_Matrix(Container container);
    Adjacency_Matrix(const Adjacency_Matrix& am);

    /* Methods */
    std::vector<double>& get_neighbors(unsigned long row);
    unsigned long get_num_edges();
    unsigned long get_num_vertices();
    bool get_visited(unsigned long row, unsigned long col);
    double get_weight(unsigned long row, unsigned long col);

    /* Operators */
    Adjacency_Matrix& operator=(const Adjacency_Matrix& am);
    friend std::ostream& operator<<(std::ostream& os, const Adjacency_Matrix& am);
};

/* count_edges */
void Adjacency_Matrix::count_edges() {
  for(auto &row : matrix) {
    for(auto &col : row) {
      if(col > 0) {
        ++num_edges;
      }
    }
  }
}

/* has_non_negative_edges */
bool Adjacency_Matrix::has_non_negative_edges() {
  for(auto &row : matrix) {
    for(auto &col : row) {
      if(col < 0) {
        return false;
      }
    }
  }
  return true;
}

/* is_square */
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
  matrix.reserve(container.size());
  for(auto it = container.begin(); it != container.end(); ++it) {
    matrix.push_back(std::vector<double>(it->begin(), it->end()));
  }
  if(!is_square()) {
    throw Adjacency_Matrix_Exception("Graph representation is not square\n");
  } else if(!has_non_negative_edges()) {
    throw Adjacency_Matrix_Exception("Graph representation has non-negative edges\n");
  } else {
    count_edges();
    num_vertices = matrix.size();
    visited = std::vector<std::vector<bool>>();
    for(int i = 0; i < num_edges; ++i) {
      visited.push_back(std::vector<bool>());
    }
  }
}

/* Copy Constructor */
Adjacency_Matrix::Adjacency_Matrix(const Adjacency_Matrix& am) {
  matrix = am.matrix;
  num_edges = am.num_edges;
  num_vertices = am.num_vertices;

}

/* get neighbors */
std::vector<double>& Adjacency_Matrix::get_neighbors(unsigned long row) {
  return matrix[row];
}

/* get_num_edges */
unsigned long Adjacency_Matrix::get_num_edges() {
  return num_edges;
}

/* get_num_vertices */
unsigned long Adjacency_Matrix::get_num_vertices() {
  return num_vertices;
}

/* get_visited */
bool Adjacency_Matrix::get_visited(unsigned long row, unsigned long col) {
  return visited[row][col];
}

/* get weight */
double Adjacency_Matrix::get_weight(unsigned long row, unsigned long col) {
  return matrix[row][col];
}

/* set visited */
void Adjacency_Matrix::set_visited(unsigned long row, unsigned long col, bool b) {
  visited[row][col] = b;
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
