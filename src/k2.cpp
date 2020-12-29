#include "EpsilonGreedyStrategy.hpp"
#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"
#include "Experiment.hpp"

class MuMonitor: public MachineScoreMonitor {
public:
  virtual void initialize(const Strategy &strat, unsigned int n) {
    this->strat = dynamic_cast<const EpsilonGreedyStrategy*>(&strat);
  }

  virtual std::vector<double> get_machine_score() {
    return this->strat->mu;
  }

  const EpsilonGreedyStrategy *strat;
};

int main() {

  const double EPSILON = 0.8;
  std::shared_ptr<MuMonitor> mon = std::make_shared<MuMonitor>();
  auto hist = run_epsilon_greedy(MACHINES, N, EPSILON, std::static_pointer_cast<Monitor>(mon));

  print_simulation_results(hist, mon);
}
