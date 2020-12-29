#include "Simulation.hpp"

SimulationHistory run_single
(
 const std::vector<SlotMachine> &machines,
 Strategy &strat,
 unsigned int n,
 std::shared_ptr<Monitor> monitor
 ) {

  strat.reset();
  if(monitor) monitor->initialize(strat, n);

  SimulationHistory hist;
  hist.n = n;
  hist.machines = machines;

  for(unsigned int i = 0; i < n; i++) {
    Attempt a;
    a.machine = strat.pick();
    a.result = machines[a.machine].engage();
    strat.accept_result(a.result);
    hist.attempts.push_back(a);
    if(monitor) monitor->monitor_attempt(i, a);
  }

  return hist;
}

void Monitor::initialize(const Strategy &strat, unsigned int n) {
  (void) strat;
  (void) n;
}

void Monitor::monitor_attempt(unsigned int i, const Attempt &attempt) {
  (void) i;
  (void) attempt;
}

void MachineScoreMonitor::monitor_attempt(unsigned int i, const Attempt &a) {
  (void) i;
  (void) a;
  this->score.push_back(this->get_machine_score());
}
