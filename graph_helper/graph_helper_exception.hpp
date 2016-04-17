#ifndef __GRAPH_HELPER_EXCEPTION_HPP__
#define __GRAPH_HELPER_EXCEPTION_HPP__
/*
 * Filename: graph_helper_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Graph_Helper_Exception --------------------------------------------------- */

class Graph_Helper_Exception : public std::exception {
private:
  const char* message;
public:
  Graph_Helper_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
