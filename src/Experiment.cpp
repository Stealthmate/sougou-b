#include "RandomStrategy.hpp"
#include "EpsilonGreedyStrategy.hpp"
#include "SoftmaxStrategy.hpp"
#include "UCBStrategy.hpp"
#include "Experiment.hpp"
#include "Util.hpp"

unsigned int best_machine(const std::vector<SlotMachine> &machines) {
  return argmax(vecmap<SlotMachine, double>(machines, [](const SlotMachine &m) -> double { return m.probability(); }));
}

SimulationHistory run_random(const std::vector<SlotMachine> &machines, unsigned int N, std::shared_ptr<Monitor> monitor) {
  auto strat = RandomStrategy(machines.size());
  return run_single(machines, strat, N, monitor);
}

SimulationHistory run_epsilon_greedy(const std::vector<SlotMachine> &machines, unsigned int N, double epsilon, std::shared_ptr<Monitor> monitor) {
  auto strat = EpsilonGreedyStrategy(machines.size(), epsilon);
  return run_single(machines, strat, N, monitor);
}

SimulationHistory run_softmax(const std::vector<SlotMachine> &machines, unsigned int N, double tau, std::shared_ptr<Monitor> monitor) {
  auto strat = SoftmaxStrategy(machines.size(), tau);
  return run_single(machines, strat, N, monitor);
}

SimulationHistory run_ucb(const std::vector<SlotMachine> &machines, unsigned int N, double alpha, std::shared_ptr<Monitor> monitor) {
  auto strat = UCBStrategy(machines.size(), alpha);
  return run_single(machines, strat, N, monitor);
}
