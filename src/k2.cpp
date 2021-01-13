#include "EpsilonGreedyStrategy.hpp"
#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

class MuMonitor: public MachineScoreMonitor {
public:
  virtual void initialize(const Strategy &strat, const SimulationEnvironment &senv) {
    (void) senv;
    this->strat = dynamic_cast<const EpsilonGreedyStrategy*>(&strat);
  }

  virtual std::vector<double> get_machine_score() {
    return this->strat->mu;
  }

  const EpsilonGreedyStrategy *strat;
};

int main() {
  init();

  const double EPSILON = 0.8;
  std::shared_ptr<MuMonitor> mon = std::make_shared<MuMonitor>();
  test_strat(EG, EPSILON, std::static_pointer_cast<MachineScoreMonitor>(mon));
}
