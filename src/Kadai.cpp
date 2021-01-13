#include "Kadai.hpp"
#include "RandomStrategy.hpp"
#include "EpsilonGreedyStrategy.hpp"
#include "SoftmaxStrategy.hpp"
#include "UCBStrategy.hpp"
#include "Simulation.hpp"
#include "Metrics.hpp"
#include "Util.hpp"

#include "mt.h"

#include <iostream>

const std::vector<SlotMachine> MACHINES =
  {
   SlotMachine(0.1),
   SlotMachine(0.3),
   SlotMachine(0.9),
   SlotMachine(0.7),
   SlotMachine(0.5)
  };

const unsigned int N = 500;
unsigned long long SEED = 1;
const SimulationEnvironment DEFAULT_SIM_ENV(N, MACHINES);

std::optional<Strat> strat_from_str(std::string s) {
  if(s == "rand") return RAND;
  if(s == "eg") return EG;
  if(s == "sm") return SM;
  if(s == "ucb") return UCB;
  return {};
}

std::string strat_name(Strat s) {
  switch(s) {
  case RAND: return "rand";
  case EG: return "eg";
  case SM: return "sm";
  case UCB: return "ucb";
  default: return "";
  }
}

strat_f strat_func(Strat s) {
  switch(s) {
  case RAND: return run_rand;
  case EG: return run_eg;
  case SM: return run_sm;
  case UCB: return run_ucb;
  default: return nullptr;
  }
}

SimulationHistory run_rand(const SimulationEnvironment &senv, double p, std::shared_ptr<Monitor> monitor) {
  (void) p;
  auto strat = RandomStrategy(senv.machines.size());
  return run_single(senv, strat, monitor);
}

SimulationHistory run_eg(const SimulationEnvironment &senv, double epsilon, std::shared_ptr<Monitor> monitor) {
  auto strat = EpsilonGreedyStrategy(senv.machines.size(), epsilon);
  return run_single(senv, strat, monitor);
}

SimulationHistory run_sm(const SimulationEnvironment &senv, double tau, std::shared_ptr<Monitor> monitor) {
  auto strat = SoftmaxStrategy(senv.machines.size(), tau);
  return run_single(senv, strat, monitor);
}

SimulationHistory run_ucb(const SimulationEnvironment &senv, double alpha, std::shared_ptr<Monitor> monitor) {
  auto strat = UCBStrategy(senv.machines.size(), alpha);
  return run_single(senv, strat, monitor);
}


void test_strat(Strat s, double p, std::shared_ptr<MachineScoreMonitor> monitor, const SimulationEnvironment &senv) {
  auto hist = strat_func(s)(senv, p, monitor);
  print_simulation_results(hist, monitor);
}

void init(unsigned long long seed) {
  init_genrand64(seed);
}

unsigned int best_machine(const std::vector<SlotMachine> &machines) {
  return argmax(vecmap<SlotMachine, double>(machines, [](const SlotMachine &m) -> double { return m.probability(); }));
}

EvaluationResults evaluate_strat(Strat s, double param, unsigned int sets, const SimulationEnvironment &senv) {
  auto results = EvaluationResults(senv.n);

  std::vector<SimulationHistory> hist(sets, SimulationHistory(senv));
  for(unsigned int i = 0; i < sets; i++) {
    hist[i] = strat_func(s)(senv, param, nullptr);
  }

  double avg_rw = 0;
  auto best = best_machine(senv.machines);
  for(unsigned int i = 0; i < N; i++) {
    double cdr = 0;
    for(unsigned int j = 0; j < sets; j++) {
      avg_rw += hist[j].attempts[i].result ? 1.0 : 0.0;
      cdr += hist[j].attempts[i].machine == best ? 1.0 : 0.0;
    }

    results[i] = {avg_rw / ((i + 1) * sets), cdr / sets};
  }

  return results;
}


void print_simulation_results(const SimulationHistory &hist, std::shared_ptr<MachineScoreMonitor> mon) {
  std::vector<unsigned int> an = attempt_numbers(hist);
  std::vector<unsigned int> em = engaged_machines(hist);
  std::vector<double> avg_rw = average_reward(hist);
  std::vector<double> cdr_ = cdr(hist);

  for(unsigned int i = 0; i < an.size(); i++) {
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
