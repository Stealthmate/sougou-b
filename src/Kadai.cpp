#include "Kadai.hpp"

#include <iostream>

#include "Simulation.hpp"
#include "Metrics.hpp"

const std::vector<SlotMachine> MACHINES =
  {
   SlotMachine(0.1),
   SlotMachine(0.3),
   SlotMachine(0.9),
   SlotMachine(0.7),
   SlotMachine(0.5)
  };

const unsigned int N = 500;

void print_simulation_results(const SimulationHistory &hist, std::shared_ptr<MachineScoreMonitor> mon) {
  std::vector<unsigned int> an = attempt_numbers(hist);
  std::vector<unsigned int> em = engaged_machines(hist);
  std::vector<double> avg_rw = average_reward(hist);
  std::vector<double> cdr_ = cdr(hist);

  for(unsigned int i = 0; i < N; i++) {
    std::cout << an[i]
              << "," << em[i]
              << "," << avg_rw[i]
              << "," << cdr_[i];
    if(mon) {
      for(unsigned int j = 0; j < MACHINES.size(); j++) {
        std::cout << "," << mon->score[i][j];
      }
    }

    std::cout << std::endl;
  }
}
