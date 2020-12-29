#include "RandomStrategy.hpp"
#include "Metrics.hpp"
#include "Experiment.hpp"
#include "Simulation.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

#include <fstream>

unsigned int STEPS = 100;
unsigned int L = 100;

double total_average_reward(const std::vector<SimulationHistory> &hist) {
  double avg = 0;
  for(unsigned int i = 0; i < hist.size(); i++) {
    for(unsigned int j = 0; j < hist[i].n; j++) {
      avg += hist[i].attempts[j].result ? 1.0 : 0.0;
    }
  }

  return avg / hist.size() / hist[0].n;
}

double total_cdr(const std::vector<SimulationHistory> &hist) {
  unsigned int best = best_machine(MACHINES);

  double cdr_ = 0;

  for(unsigned int i = 0; i < hist.size(); i++) {
    cdr_ += hist[i].attempts[hist[i].n - 1].machine == best ? 1.0 : 0.0;
  }

  return cdr_ / hist.size();
}

typedef SimulationHistory (*run_with_param_f)(const std::vector<SlotMachine>&, unsigned int, double, std::shared_ptr<Monitor>);

typedef std::vector<std::tuple<double, double, double>> AnalysisResults;

AnalysisResults analyze(run_with_param_f f, double low, double high) {
  double step = (high - low) / STEPS;
  auto results = std::vector<std::tuple<double, double, double>>(STEPS);

  for(unsigned int j = 0; j < STEPS; j += 1) {
    double x = low + j * step;
    std::vector<SimulationHistory> hist(L);
    for(unsigned int i = 0; i < L; i++) {
      hist[i] = f(MACHINES, N, x, nullptr);
    }
    results[j] = {x, total_average_reward(hist), total_cdr(hist)};
  }

  return results;
}

void print_results(const AnalysisResults &results, std::string fname) {
  std::ofstream f;
  f.open(fname);
  for(unsigned int i = 0; i < results.size(); i++) {
    f << i + 1
      << "," << std::get<0>(results[i])
      << "," << std::get<1>(results[i])
      << "," << std::get<2>(results[i])
      << std::endl;
  }
  f.close();
}

std::tuple<double, double, double> find_best(const AnalysisResults &results) {
  unsigned int imax = -1;
  double max_rw = -1;

  for(unsigned int i = 0; i < results.size(); i++) {
    if(max_rw < std::get<1>(results[i])) {
      max_rw = std::get<1>(results[i]);
      imax = i;
    }
  }

  return results[imax];
}

std::vector<std::pair<double, double>> evaluate(run_with_param_f f, double param) {
  auto results = std::vector<std::pair<double, double>>(N);

  std::vector<SimulationHistory> hist(L);
  for(unsigned int i = 0; i < L; i++) {
    hist[i] = f(MACHINES, N, param, nullptr);
  }

  double avg_rw = 0;
  auto best = best_machine(MACHINES);
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
  auto eg = analyze(run_epsilon_greedy, 0, 1);
  print_results(eg, "data/k5-eg.csv");
  auto best = find_best(eg);
  std::cout << "EG: BEST: "
            << std::get<0>(best) << " "
            << std::get<1>(best) << " "
            << std::get<2>(best) << std::endl;
  auto best_eps = std::get<0>(best);

  auto sm = analyze(run_softmax, 0, 1);
  print_results(sm, "data/k5-sm.csv");
  best = find_best(sm);
  std::cout << "SM: BEST: "
            << std::get<0>(best) << " "
            << std::get<1>(best) << " "
            << std::get<2>(best) << std::endl;
  auto best_tau = std::get<0>(best);

  auto ucb = analyze(run_ucb, 0, 1);
  print_results(ucb, "data/k5-ucb.csv");
  best = find_best(ucb);
  std::cout << "UCB: BEST: "
            << std::get<0>(best) << " "
            << std::get<1>(best) << " "
            << std::get<2>(best) << std::endl;
  auto best_alpha = std::get<0>(best);


  auto stats_eg = evaluate(run_epsilon_greedy, best_eps);
  auto stats_sm = evaluate(run_softmax, best_tau);
  auto stats_ucb = evaluate(run_ucb, best_alpha);

  print_stats(stats_eg, "data/k5-stats-eg.csv");
  print_stats(stats_sm, "data/k5-stats-sm.csv");
  print_stats(stats_ucb, "data/k5-stats-ucb.csv");
}
