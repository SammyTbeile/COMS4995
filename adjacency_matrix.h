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
  template<class Iterator>
  void init(Iterator begin, Iterator end);
  bool is_square();

public:
  /* Constructors */
  Adjacency_Matrix(std::vector<std::vector<double>> user_rep);
  template<unsigned LENGTH>
  Adjacency_Matrix(std::vector<std::array<double, LENGTH>> user_rep);
  Adjacency_Matrix(std::vector<std::list<double>> user_rep);
  template<unsigned LENGTH>
  Adjacency_Matrix(std::array<std::vector<double>, LENGTH> user_rep);
  template<unsigned LENGTH>
  Adjacency_Matrix(std::array<std::array<double, LENGTH>, LENGTH> user_rep);
  template<unsigned LENGTH>
  Adjacency_Matrix(std::array<std::list<double>, LENGTH> user_rep);
  Adjacency_Matrix(std::list<std::vector<double>> user_rep);
  template<unsigned LENGTH>
  Adjacency_Matrix(std::list<std::array<double, LENGTH>> user_rep);
  Adjacency_Matrix(std::list<std::list<double>> user_rep);

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

#endif
