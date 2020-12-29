#include "Experiment.hpp"
#include "Kadai.hpp"
#include "Metrics.hpp"

#include <iostream>

int main() {
  auto hist = run_random(MACHINES, N, nullptr);
  print_simulation_results(hist);
}
