#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__
/*
 * Filename: algorithms.h
 * Authors:  Sean Garvey, Sammy Tbeile
 * UNIs:     sjg2174,     st2918
 */

#include <exception>
#include <utility>
#include <vector>

#include "graph.hpp"

/* Algorithms_Exception ----------------------------------------------------- */

class Algorithms_Exception : public std::exception {
private:
  const char* message;
public:
  Algorithms_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

/* Algorithms --------------------------------------------------------------- */

class Algorithms {
  private:
    /* Private Member Functions */
    static void validate_start_vertex(Graph graph, unsigned long start_vertex);
  public:
    /* Public Member Functions */
    static std::vector<std::pair<unsigned long, unsigned long>>
      Dijkstras(Graph graph, unsigned long start_vertex);
    static std::vector<std::pair<unsigned long, unsigned long>>
      Prims(Graph graph, unsigned long start_vertex);
};

#endif
