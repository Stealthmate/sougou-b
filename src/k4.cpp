#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"
#include "Experiment.hpp"

class FMonitor: public MachineScoreMonitor {
public:
  virtual void initialize(const Strategy &strat, unsigned int n) {
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
  auto hist = run_ucb(MACHINES, N, ALPHA, std::static_pointer_cast<Monitor>(mon));

  print_simulation_results(hist, mon);
}
