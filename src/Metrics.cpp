#include "Metrics.hpp"

void AttemptHistoryMetric::update(unsigned int i, const Attempt &a) {
  (void) i;
  this->attempts.push_back(a);
}

std::string AttemptHistoryMetric::print(unsigned int i) {
  return std::to_string(this->attempts[i].machine);
}

void AverageRewardMetric::update(unsigned int i, const Attempt &a) {
  double old_avg = i > 0 ? this->avg_reward[i - 1] : 0;
  double new_avg = ((old_avg * i) + (a.result ? 1.0 : 0.0)) / (i + 1);
  this->avg_reward.push_back(new_avg);
}

std::string AverageRewardMetric::print(unsigned int i) {
  return std::to_string(this->avg_reward[i]);
}

void CDRMetric::initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
  (void) strat;
  (void) n;

  unsigned int mi = 0;
  double mp = -1.0;

  for(unsigned int i = 0; i <= sim.machines.size(); i++) {
    double p = sim.machines[i].probability();
    if(mp < p) {
      mi = i;
      mp = p;
    }
  }

  this->best_machine = mi;
}

void CDRMetric::update(unsigned int i, const Attempt &a) {
  double old_cdr = i > 0 ? this->cdr[i - 1] : 0;
  double new_cdr = ((old_cdr * i) + ((a.machine == this->best_machine) ? 1.0 : 0.0)) / (i + 1);
  this->cdr.push_back(new_cdr);
}

std::string CDRMetric::print(unsigned int i) {
  return std::to_string(this->cdr[i]);
}
