#include <iostream>
#include <vector>
#include <memory>

#include "SoftmaxStrategy.hpp"
#include "SlotMachine.hpp"
#include "Simulation.hpp"
#include "Metrics.hpp"
#include "mt.h"

class RhoMetric: public Metric {
public:

  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
    this->machines = sim.machines.size();
    this->rho = std::vector<std::vector<double>>(n + 1, std::vector<double>(this->machines, 0));
    this->strat = dynamic_cast<const SoftmaxStrategy*>(&strat);

    this->rho[0] = std::vector<double>(this->strat->rho);
  }

  virtual void update(unsigned int i, const Attempt &a) {
    this->rho[i + 1] = std::vector<double>(this->strat->rho);
  }

  const SoftmaxStrategy *strat;
  std::vector<std::vector<double>> rho;
  unsigned int machines;
};

int main() {
  init_genrand64(123);
  std::vector<SlotMachine> machines =
    {
     SlotMachine(0.1),
     SlotMachine(0.3),
     SlotMachine(0.9),
     SlotMachine(0.7),
     SlotMachine(0.5)
    };


  const double TAU = 0.5;

  auto rs = SoftmaxStrategy(machines.size(), TAU);
  auto sim = Simulation(machines);

  auto ah_m = std::make_shared<AttemptHistoryMetric>();
  auto ar_m = std::make_shared<AverageRewardMetric>();
  auto cdr_m = std::make_shared<CDRMetric>();
  auto rho_m = std::make_shared<RhoMetric>();

  std::vector<std::shared_ptr<Metric>> metrics =
    {
     std::static_pointer_cast<Metric>(ah_m),
     std::static_pointer_cast<Metric>(ar_m),
     std::static_pointer_cast<Metric>(cdr_m),
     std::static_pointer_cast<Metric>(rho_m)
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
    double sum = 0;

    for(double rho : rho_m->rho[i]) {
      std::cout << "," << rho;
      sum += rho;
    }
    std::cout << "," << sum;

    std::cout << std::endl;
  }
}
