#include "Metrics.hpp"
#include "Simulation.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

#include <fstream>

unsigned int L = 100;
double ALPHA = 0.12;

void print_stats(const std::vector<std::pair<double, double>> &stats) {
  for(unsigned int i = 0; i < N; i++) {
    std::cout << i + 1
      << ","
      << "," << std::get<0>(stats[i])
      << "," << std::get<1>(stats[i])
      << std::endl;
  }
}

int main() {
  init();

  std::vector<std::vector<SlotMachine>> machines =
    {
     {
      SlotMachine(0.3),
      SlotMachine(0.1),
      SlotMachine(0.99),
      SlotMachine(0.7),
      SlotMachine(0.5)
     },
     {
      SlotMachine(0.3),
      SlotMachine(0.1),
      SlotMachine(0.75),
      SlotMachine(0.7),
      SlotMachine(0.5)
     },
     {
      SlotMachine(0.2),
      SlotMachine(0.1),
      SlotMachine(0.9),
      SlotMachine(0.7),
      SlotMachine(0.5),

      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),

      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),

      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5),
      SlotMachine(0.5)
     }
  };

  std::vector<std::vector<std::pair<double, double>>> stats;

  for(unsigned int i = 0; i < machines.size(); i++) {
    stats.push_back(evaluate_strat(UCB, ALPHA, L, SimulationEnvironment(N, machines[i])));
  }

  for(unsigned int i = 0; i < N; i++) {
    std::cout << i + 1;
    for(unsigned int j = 0; j < machines.size(); j++) {
      std::cout << "," << std::get<0>(stats[j][i])
                << "," << std::get<1>(stats[j][i]);
    }
    std::cout << std::endl;
  }
}
