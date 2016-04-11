#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__
/*
 * Filename: algorithms.h
 * Authors:  Sean Garvey
 * UNIs:     sjg2174
 */
#include <utility>

/* Instead of #include's, to handle circular dependencies */
class Adjacency_Matrix;
class Adjacency_List;

class Algorithms {
  private:
    bool range(unsigned long x, unsigned long y, unsigned long z);
    void validate_within_range(unsigned long n, std::pair<unsigned long, unsigned long> start_pair);
    
  public:
    static void Dijkstras(Adjacency_Matrix& am, std::pair<unsigned long, unsigned long> start_pair);
};

/* Exception */
class Algorithm_Exception : public std::exception {
private:
  const char* message;
public:
  Algorithm_Exception(const char* msg) { message = msg; }
  virtual const char* what() const throw() { return message; }
};

#endif
