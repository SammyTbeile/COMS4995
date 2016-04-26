/*
 * Filename: stopwatch.hpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#ifndef __STOPWATCH_HPP__
#define __STOPWATCH_HPP__
#include <chrono>
#include <memory>

class Stopwatch {
public:
  void start();
  void stop();
  double elapsed();
  void reset();

private:
  std::unique_ptr<std::chrono::high_resolution_clock::time_point> start_time
    = nullptr;
  std::unique_ptr<std::chrono::high_resolution_clock::time_point> stop_time
    = nullptr;
  double elapsed_time = 0;
};

#endif
