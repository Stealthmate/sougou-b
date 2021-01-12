#include "KadaiAdvanced.hpp"

#include "EpsilonGreedyStrategy.hpp"
#include "SoftmaxStrategy.hpp"
#include "UCBStrategy.hpp"

#include <iostream>

double runsim(unsigned int n, Strategy &strat, engage_f f) {
  strat.reset();
  double avg = 0;
  for(unsigned int i = 0; i < n; i++) {
    int result = f(strat.pick() + 1);
    avg += result;
    strat.accept_result(result);
  }

  return avg / n;
}
