#ifndef __ADJACENCY_LIST_EXCEPTION_HPP__
#define __ADJACENCY_LIST_EXCEPTION_HPP__
/*
 * Filename: adjacency_list_exception.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include <exception>

/* Adjacency_List_Exception ------------------------------------------------- */

class Adjacency_List_Exception : public std::exception {
private:
  const char* message;
public:
  Adjacency_List_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
