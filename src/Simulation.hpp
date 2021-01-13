#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <memory>

#include "SlotMachine.hpp"
#include "Strategy.hpp"

struct SimulationEnvironment {
  unsigned int n;
  std::vector<SlotMachine> machines;

  SimulationEnvironment(unsigned int n, const std::vector<SlotMachine> &machines);
  SimulationEnvironment(const SimulationEnvironment &senv) =default;
};

struct Attempt {
  bool result;
  unsigned int machine;
};

struct SimulationHistory {
  SimulationEnvironment senv;
  std::vector<Attempt> attempts;
  SimulationHistory(const SimulationEnvironment &senv);
  SimulationHistory(const SimulationHistory &hist) =default;
};

class Monitor {
public:
  virtual void initialize(const Strategy &strat, const SimulationEnvironment &senv);
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
 const SimulationEnvironment &senv,
 Strategy &strat,
 std::shared_ptr<Monitor> monitor
 );

#endif
