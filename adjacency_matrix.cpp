/*
 * Filename: adjacency_matrix.cpp
 * Authors:  Sean Garvey, Sammy Tbeile, Minh Truong
 * UNIs:     sjg2174,     st2918,       mt3077
 */

#include "adjacency_matrix.h"

/* init */
template <class Iterator>
void Adjacency_Matrix::init(Iterator begin, Iterator end) {
  matrix = std::vector<std::vector<double>>();
  for(auto it = begin; it != end; ++it) {
    matrix.push_back(std::vector<double>(it->begin(), it->end()));
  }
  if(!is_square()) {
    //struct Adjacency_Matrix_Exception ame;
    //throw ame;// throw exception
    throw Adjacency_Matrix_Exception("Graph representation is not square\n");
  }
}

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

/* Constructors */
Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<double>> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

template<unsigned LENGTH>
Adjacency_Matrix::Adjacency_Matrix(std::vector<std::array<double, LENGTH>> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::list<double>> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

template<unsigned LENGTH>
Adjacency_Matrix::Adjacency_Matrix(std::array<std::vector<double>, LENGTH> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

template<unsigned LENGTH>
Adjacency_Matrix::Adjacency_Matrix(std::array<std::array<double, LENGTH>, LENGTH> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

template<unsigned LENGTH>
Adjacency_Matrix::Adjacency_Matrix(std::array<std::list<double>, LENGTH> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

Adjacency_Matrix::Adjacency_Matrix(std::list<std::vector<double>> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

template<unsigned LENGTH>
Adjacency_Matrix::Adjacency_Matrix(std::list<std::array<double, LENGTH>> user_rep) {
  init(user_rep.begin(), user_rep.end());
}

Adjacency_Matrix::Adjacency_Matrix(std::list<std::list<double>> user_rep) {
  init(user_rep.begin(), user_rep.end());
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
