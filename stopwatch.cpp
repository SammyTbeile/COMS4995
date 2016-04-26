/*
 * Filename: stopwatch.cpp
 * Author:   Sean Garvey
 * UNI:      sjg2174
 */

#include "stopwatch.hpp"

static const int elapsed_default = 0;

void Stopwatch::start() {
  if(start_time == nullptr) {
    start_time = std::unique_ptr<std::chrono::high_resolution_clock::time_point>
      (new std::chrono::high_resolution_clock::time_point(
        std::chrono::high_resolution_clock::now()));
  }
}

void Stopwatch::stop() {
  if(start_time != nullptr) {
    stop_time = std::unique_ptr<std::chrono::high_resolution_clock::time_point>
      (new std::chrono::high_resolution_clock::time_point(
        std::chrono::high_resolution_clock::now()));
    elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>
      (*stop_time - *start_time).count();
  }
}

double Stopwatch::elapsed() {
  if(elapsed_time == elapsed_default && start_time != nullptr) {
    std::chrono::high_resolution_clock::time_point now =
      std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>
      (now - *start_time).count();
  } else {
    return elapsed_time;
  }
}

void Stopwatch::reset() {
  start_time.reset();
  stop_time.reset();
  elapsed_time = elapsed_default;
}
