#ifndef __ALGORITHM_EXCEPTION_HPP__
#define __ALGORITHM_EXCEPTION_HPP__
/*
 * Filename: algorithm_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Adjacency_Exception ------------------------------------------------- */

class Algorithm_Exception : public std::exception {
private:
  const char* message;
public:
  Algorithm_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
