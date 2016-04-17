#ifndef __GRAPH_EXCEPTION_HPP__
#define __GRAPH_EXCEPTION_HPP__
/*
 * Filename: graph_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Graph_Exception ---------------------------------------------------------- */

class Graph_Exception : public std::exception {
private:
  const char* message;
public:
  Graph_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
