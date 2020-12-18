#include "Simulation.hpp"

void Metric::initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
  (void) sim;
  (void) strat;
  (void) n;
}

Simulation::Simulation(std::vector<SlotMachine> machines): machines(machines) {}

void Simulation::run(Strategy &strat, unsigned int n, std::vector<std::shared_ptr<Metric>> metrics) {
  strat.reset();

  for(auto m : metrics) {
    m->initialize(*this, strat, n);
  }

  for(unsigned int i = 0; i < n; i++) {
    Attempt a;
    a.machine = strat.pick();
    a.result = this->machines[a.machine].engage();
    strat.accept_result(a.result);

    for(auto m : metrics) {
      m->update(i, a);
    }
  }
}

void Simulation::on_attempt(const Strategy &strat, unsigned int i, const Attempt &a) {}
