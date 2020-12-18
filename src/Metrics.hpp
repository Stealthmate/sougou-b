#ifndef METRICS_HPP
#define METRICS_HPP

#include "Simulation.hpp"

class AttemptHistoryMetric: public Metric {
public:
  virtual void update(unsigned int i, const Attempt &a);
  virtual std::string print(unsigned int i);

  std::vector<Attempt> attempts;
};

class AverageRewardMetric : public Metric {
public:
  virtual void update(unsigned int i, const Attempt &a);
  virtual std::string print(unsigned int i);

  std::vector<double> avg_reward;
};

class CDRMetric : public Metric {
public:
  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n);
  virtual void update(unsigned int i, const Attempt &a);
  virtual std::string print(unsigned int i);

  unsigned int best_machine;
  std::vector<double> cdr;
};

#endif
