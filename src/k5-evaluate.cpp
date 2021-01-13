#include "RandomStrategy.hpp"
#include "Metrics.hpp"
#include "Simulation.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

#include <fstream>
#include <optional>

unsigned int L = 100;

void print_stats(const std::vector<std::pair<double, double>> &stats) {
  for(unsigned int i = 0; i < N; i++) {
    std::cout << i + 1
      << ","
      << "," << std::get<0>(stats[i])
      << "," << std::get<1>(stats[i])
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

double strat_best_param(Strat s) {
  switch(s) {
  case RAND: return 0.0;
  case EG: return 0.10;
  case SM: return 0.16;
  case UCB: return 0.12;
  default: return 0.0;
  }
}

void eval_strat(Strat s) {
  auto stats = evaluate_strat(s, strat_best_param(s), L, DEFAULT_SIM_ENV);
  print_stats(stats);
}

int main(int argc, char *argv[]) {
  auto strat_ = parseCmdln(argc, argv);
  if(strat_ == std::nullopt) {
    exit(-1);
  }

  init();
  eval_strat(*strat_);
}
