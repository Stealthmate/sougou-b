#include <iostream>
#include <vector>
#include <memory>

#include "RandomStrategy.hpp"
#include "SlotMachine.hpp"
#include "Simulation.hpp"
#include "Metrics.hpp"

int main() {
  std::vector<SlotMachine> machines =
    {
     SlotMachine(0.1),
     SlotMachine(0.3),
     SlotMachine(0.9),
     SlotMachine(0.7),
     SlotMachine(0.5)
    };

  auto rs = RandomStrategy(machines.size());
  auto sim = Simulation(machines);

  auto ah_m = std::make_shared<AttemptHistoryMetric>();
  auto ar_m = std::make_shared<AverageRewardMetric>();
  auto cdr_m = std::make_shared<CDRMetric>();

  std::vector<std::shared_ptr<Metric>> metrics =
    {
     std::static_pointer_cast<Metric>(ah_m),
     std::static_pointer_cast<Metric>(ar_m),
     std::static_pointer_cast<Metric>(cdr_m)
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
         << cdr_m->cdr[i]
         << std::endl;
  }
}
