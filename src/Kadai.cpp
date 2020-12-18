#include "Kadai.hpp"

#include <iostream>

#include "Simulation.hpp"
#include "Metrics.hpp"

void run_kadai
(
 Strategy &strat,
 const std::vector<std::shared_ptr<Metric>> &additional_metrics
 ) {

  std::vector<SlotMachine> machines =
    {
     SlotMachine(0.1),
     SlotMachine(0.3),
     SlotMachine(0.9),
     SlotMachine(0.7),
     SlotMachine(0.5)
    };
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
  metrics.reserve(metrics.size() + additional_metrics.size());
  metrics.insert(metrics.end(), additional_metrics.begin(), additional_metrics.end());

  unsigned int N = 500;

  sim.run(strat, N, metrics);

  for(unsigned int i = 0; i < N; i++) {
    std::cout << i
              << ","
              << ah_m->attempts[i].machine + 1
              << ","
              << ar_m->avg_reward[i]
              << ","
              << cdr_m->cdr[i];

    for(auto m : additional_metrics) {
      std::cout << "," << m->print(i);
    }
    std::cout << std::endl;
  }
}
