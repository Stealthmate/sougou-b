#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <memory>

#include "SlotMachine.hpp"
#include "Strategy.hpp"

struct Attempt {
  bool result;
  unsigned int machine;
};

struct SimulationHistory {
  std::vector<SlotMachine> machines;
  unsigned int n;
  std::vector<Attempt> attempts;
};

class Monitor {
public:
  virtual void initialize(const Strategy &strat, unsigned int n);
  virtual void monitor_attempt(unsigned int i, const Attempt &attempt);
};

class MachineScoreMonitor : public Monitor {
public:
  virtual void monitor_attempt(unsigned int i, const Attempt &attempt);

  virtual std::vector<double> get_machine_score() =0;

  std::vector<std::vector<double>> score;
};

SimulationHistory run_single
(
 const std::vector<SlotMachine> &machines,
 Strategy &strat,
 unsigned int n,
 std::shared_ptr<Monitor> monitor
 );

#endif
