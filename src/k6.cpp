#include "Metrics.hpp"
#include "Experiment.hpp"
#include "Simulation.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

#include <fstream>

unsigned int L = 100;
double ALPHA = 0.12;

typedef SimulationHistory (*run_with_param_f)(const std::vector<SlotMachine>&, unsigned int, double, std::shared_ptr<Monitor>);

std::vector<std::pair<double, double>> evaluate(const std::vector<SlotMachine> &machines) {
  auto results = std::vector<std::pair<double, double>>(N);

  std::vector<SimulationHistory> hist(L);
  for(unsigned int i = 0; i < L; i++) {
    hist[i] = run_ucb(machines, N, ALPHA, nullptr);
  }

  double avg_rw = 0;
  auto best = best_machine(machines);
  for(unsigned int i = 0; i < N; i++) {
    double cdr = 0;
    for(unsigned int j = 0; j < L; j++) {
      avg_rw += hist[j].attempts[i].result ? 1.0 : 0.0;
      cdr += hist[j].attempts[i].machine == best ? 1.0 : 0.0;
    }

    results[i] = {avg_rw / ((i + 1) * L), cdr / L};
  }

  return results;
}

void print_stats(const std::vector<std::pair<double, double>> &stats, const std::string &filename) {
  std::ofstream f;
  f.open(filename);
  for(unsigned int i = 0; i < N; i++) {
    f << i + 1
      << ","
      << "," << std::get<0>(stats[i])
      << "," << std::get<1>(stats[i])
      << std::endl;
  }
  f.close();
}

int main() {
  init();

  std::vector<SlotMachine> machines1 =
    {
      SlotMachine(0.3),
      SlotMachine(0.1),
      SlotMachine(0.99),
      SlotMachine(0.7),
      SlotMachine(0.5)
    };
  std::vector<SlotMachine> machines2 =
    {
      SlotMachine(0.3),
      SlotMachine(0.1),
      SlotMachine(0.75),
      SlotMachine(0.7),
      SlotMachine(0.5)
    };
  std::vector<SlotMachine> machines3 =
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
  };

  auto results1 = evaluate(machines1);
  auto results2 = evaluate(machines2);
  auto results3 = evaluate(machines3);

  print_stats(results1, "data/k6-stats-1.csv");
  print_stats(results2, "data/k6-stats-2.csv");
  print_stats(results3, "data/k6-stats-3.csv");
}
