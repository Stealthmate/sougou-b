#ifndef KADAI_HPP
#define KADAI_HPP

#include <memory>
#include <vector>
#include <optional>

#include "SlotMachine.hpp"
#include "Simulation.hpp"

extern const std::vector<SlotMachine> MACHINES;
extern const unsigned int N;
extern unsigned long long SEED;
extern const SimulationEnvironment DEFAULT_SIM_ENV;

enum Strat
  {
   RAND,
   EG,
   SM,
   UCB
  };

typedef SimulationHistory (*strat_f)(const SimulationEnvironment &senv, double, std::shared_ptr<Monitor>);

typedef std::pair<double, double> EvaluationEntry;
typedef std::vector<EvaluationEntry> EvaluationResults;

std::optional<Strat> strat_from_str(std::string s);
std::string strat_name(Strat s);
strat_f strat_func(Strat s);

#define STRAT_F(x) SimulationHistory x(const SimulationEnvironment &senv, double param, std::shared_ptr<Monitor> monitor)

STRAT_F(run_rand);
STRAT_F(run_eg);
STRAT_F(run_sm);
STRAT_F(run_ucb);

#undef STRAT_F

void test_strat(Strat s, double p, std::shared_ptr<MachineScoreMonitor> monitor, const SimulationEnvironment &senv = DEFAULT_SIM_ENV);

EvaluationResults evaluate_strat(Strat s, double param, unsigned int sets, const SimulationEnvironment &senv);

void init(unsigned long long seed = SEED);

unsigned int best_machine(const std::vector<SlotMachine> &machines);

void print_simulation_results(const SimulationHistory &hist, std::shared_ptr<MachineScoreMonitor> msm = nullptr);

#endif
