#include "Simulation.hpp"

SimulationEnvironment::SimulationEnvironment(unsigned int n, const std::vector<SlotMachine> &machines): n(n), machines(machines) {}

SimulationHistory::SimulationHistory(const SimulationEnvironment &senv): senv(senv) {}

SimulationHistory run_single
(
 const SimulationEnvironment &senv,
 Strategy &strat,
 std::shared_ptr<Monitor> monitor
 ) {

  strat.reset();
  if(monitor) monitor->initialize(strat, senv);

  SimulationHistory hist(senv);
  hist.senv = senv;

  for(unsigned int i = 0; i < senv.n; i++) {
    Attempt a;
    a.machine = strat.pick();
    a.result = senv.machines[a.machine].engage();
    strat.accept_result(a.result);
    hist.attempts.push_back(a);
    if(monitor) monitor->monitor_attempt(i, a);
  }

  return hist;
}

void Monitor::initialize(const Strategy &strat, const SimulationEnvironment &senv) {
  (void) strat;
  (void) senv;
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
