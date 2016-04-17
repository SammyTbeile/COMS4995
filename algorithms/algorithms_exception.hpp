#ifndef __ALGORITHMS_EXCEPTION_HPP__
#define __ALGORITHMS_EXCEPTION_HPP__
/*
 * Filename: algorithms_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Algorithms_Exception ----------------------------------------------------- */

class Algorithms_Exception : public std::exception {
private:
  const char* message;
public:
  Algorithms_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
