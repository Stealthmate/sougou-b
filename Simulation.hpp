#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <memory>

#include "SlotMachine.hpp"
#include "Strategy.hpp"

class Simulation;

struct Attempt {
  bool result;
  unsigned int machine;
};

class Metric {
public:
  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n);
  virtual void update(unsigned int i, const Attempt &a) =0;
};

class Simulation {
public:

  Simulation(std::vector<SlotMachine> machines);

  virtual void run(Strategy &strat, unsigned int n, std::vector<std::shared_ptr<Metric>> metrics) final;

  virtual void on_attempt(const Strategy &start, unsigned int i, const Attempt &a);

  std::vector<SlotMachine> machines;
};

#endif
