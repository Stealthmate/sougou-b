#include <iostream>
#include <vector>
#include <memory>

#include "EpsilonGreedyStrategy.hpp"
#include "SlotMachine.hpp"
#include "Simulation.hpp"
#include "Metrics.hpp"

class MuMetric: public Metric {
public:

  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
    this->machines = sim.machines.size();
    this->mu = std::vector<std::vector<double>>(n, std::vector<double>(this->machines, 0));
    this->strat = dynamic_cast<const EpsilonGreedyStrategy*>(&strat);
  }

  virtual void update(unsigned int i, const Attempt &a) {
    this->mu[i] = std::vector<double>(this->strat->mu);
  }

  const EpsilonGreedyStrategy *strat;
  std::vector<std::vector<double>> mu;
  unsigned int machines;
};

int main() {
  std::vector<SlotMachine> machines =
    {
     SlotMachine(0.1),
     SlotMachine(0.3),
     SlotMachine(0.9),
     SlotMachine(0.7),
     SlotMachine(0.5)
    };


  const double EPSILON = 0.8;

  auto rs = EpsilonGreedyStrategy(machines.size(), EPSILON);
  auto sim = Simulation(machines);

  auto ah_m = std::make_shared<AttemptHistoryMetric>();
  auto ar_m = std::make_shared<AverageRewardMetric>();
  auto cdr_m = std::make_shared<CDRMetric>();
  auto mu_m = std::make_shared<MuMetric>();

  std::vector<std::shared_ptr<Metric>> metrics =
    {
     std::static_pointer_cast<Metric>(ah_m),
     std::static_pointer_cast<Metric>(ar_m),
     std::static_pointer_cast<Metric>(cdr_m),
     std::static_pointer_cast<Metric>(mu_m)
    };
  unsigned int N = 500;

  sim.run(rs, N, metrics);

  for(unsigned int i = 0; i < N; i++) {
    std::cout << i
              << ","
              << ah_m->attempts[i].machine + 1
              << ","
              << ar_m->avg_reward[i]
              << ","
              << cdr_m->cdr[i];
    for(double mu : mu_m->mu[i]) {
      std::cout << "," << mu;
    }
    std::cout << std::endl;
  }
}
