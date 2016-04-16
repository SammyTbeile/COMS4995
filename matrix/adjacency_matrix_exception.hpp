#ifndef __ADJACENCY_MATRIX_EXCEPTION_HPP__
#define __ADJACENCY_MATRIX_EXCEPTION_HPP__
/*
 * Filename: adjacency_matrix_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Adjacency_Matrix_Exception ------------------------------------------------- */

class Adjacency_Matrix_Exception : public std::exception {
private:
  const char* message;
public:
  Adjacency_Matrix_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
