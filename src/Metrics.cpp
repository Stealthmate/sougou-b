#include "Metrics.hpp"

#include <algorithm>

#include "Util.hpp"

std::vector<unsigned int> attempt_numbers(const SimulationHistory &hist) {
  std::vector<unsigned int> r(hist.senv.n);
  for(unsigned int i = 0; i < hist.senv.n; i++) {
    r[i] = (i + 1);
  }

  return r;
}

std::vector<unsigned int> engaged_machines(const SimulationHistory &hist) {
  return vecmap<Attempt, unsigned int>(hist.attempts, [](auto a) -> unsigned int { return a.machine + 1; });
}

std::vector<double> average_reward(const SimulationHistory &hist) {
  std::vector<double> r(hist.senv.n);

  double sum = 0;
  for(unsigned int i = 0; i < hist.senv.n; i++) {
    sum += hist.attempts[i].result ? 1.0 : 0.0;
    r[i] = (sum / (i + 1));
  }

  return r;
}

std::vector<double> cdr(const SimulationHistory &hist) {
  std::vector<double> r(hist.senv.n);

  unsigned int best_machine = argmax(vecmap<SlotMachine, double>(hist.senv.machines, [](const SlotMachine &m) -> double { return m.probability(); }));

  double sum = 0;
  for(unsigned int i = 0; i < hist.senv.n; i++) {
    sum += hist.attempts[i].machine == best_machine ? 1 : 0;
    r[i] = (sum / (i + 1));
  }

  return r;
}
