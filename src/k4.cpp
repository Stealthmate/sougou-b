#include "UCBStrategy.hpp"
#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

class FMonitor: public MachineScoreMonitor {
public:
  virtual void initialize(const Strategy &strat, const SimulationEnvironment &senv) {
    (void) senv;
    this->strat = dynamic_cast<const UCBStrategy*>(&strat);
  }

  virtual std::vector<double> get_machine_score() {
    return this->strat->F;
  }

  const UCBStrategy *strat;
};

int main() {
  init();

  const double ALPHA = 1.0;
  std::shared_ptr<FMonitor> mon = std::make_shared<FMonitor>();
  test_strat(UCB, ALPHA, std::static_pointer_cast<MachineScoreMonitor>(mon));
}
