#include "RandomStrategy.hpp"
#include "Metrics.hpp"
#include "Simulation.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

#include <fstream>
#include <optional>

unsigned int STEPS = 100;
unsigned int L = 100;

typedef std::tuple<double, double, double> AnalysisEntry;
typedef std::vector<AnalysisEntry> AnalysisResults;

double total_average_reward(const std::vector<SimulationHistory> &hist) {
  double avg = 0;
  for(unsigned int i = 0; i < hist.size(); i++) {
    for(unsigned int j = 0; j < hist[i].senv.n; j++) {
      avg += hist[i].attempts[j].result ? 1.0 : 0.0;
    }
  }

  return avg / hist.size() / hist[0].senv.n;
}

double total_cdr(const std::vector<SimulationHistory> &hist) {
  unsigned int best = best_machine(MACHINES);

  double cdr_ = 0;

  for(unsigned int i = 0; i < hist.size(); i++) {
    cdr_ += hist[i].attempts[hist[i].senv.n - 1].machine == best ? 1.0 : 0.0;
  }

  return cdr_ / hist.size();
}

AnalysisResults analyze(strat_f f, double low, double high) {
  double step = (high - low) / STEPS;
  auto results = AnalysisResults(STEPS);

  for(unsigned int j = 0; j < STEPS; j += 1) {
    double x = low + j * step;
    std::vector<SimulationHistory> hist(L, SimulationHistory(DEFAULT_SIM_ENV));
    for(unsigned int i = 0; i < L; i++) {
      hist[i] = f(DEFAULT_SIM_ENV, x, nullptr);
    }
    results[j] = {x, total_average_reward(hist), total_cdr(hist)};
  }

  return results;
}

AnalysisEntry find_best(const AnalysisResults &results) {
  unsigned int i = argmax(vecmap<AnalysisEntry, double>(results, [](AnalysisEntry entry) -> double { return std::get<1>(entry); }));
  return results[i];
}

void print_results(const AnalysisResults &results) {
  for(unsigned int i = 0; i < results.size(); i++) {
    std::cout << i + 1
      << "," << std::get<0>(results[i])
      << "," << std::get<1>(results[i])
      << "," << std::get<2>(results[i])
      << std::endl;
  }
}

std::optional<Strat> parseCmdln(int argc, char *argv[]) {
  if(argc < 2) {
    std::cerr << "Specify eg, sm or ucb" << std::endl;
    return {};
  }
  return strat_from_str(argv[1]);
}

void analyze_strat(Strat s) {
  auto results = analyze(strat_func(s), 0, 1);
  print_results(results);
  auto best = find_best(results);
  std::cerr << strat_name(s) << ": BEST: "
            << std::get<0>(best) << " "
            << std::get<1>(best) << " "
            << std::get<2>(best) << std::endl;
}

int main(int argc, char *argv[]) {
  auto strat_ = parseCmdln(argc, argv);
  if(strat_ == std::nullopt) {
    exit(-1);
  }

  init();
  analyze_strat(*strat_);
}
