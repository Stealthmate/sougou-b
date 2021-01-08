#include "SoftmaxStrategy.hpp"
#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"
#include "Experiment.hpp"

class RhoMonitor: public MachineScoreMonitor {
public:
  virtual void initialize(const Strategy &strat, unsigned int n) {
    this->strat = dynamic_cast<const SoftmaxStrategy*>(&strat);
  }

  virtual std::vector<double> get_machine_score() {
    return this->strat->rho;
  }

  const SoftmaxStrategy *strat;
};

int main() {
  init();

  const double TAU = 0.5;
  std::shared_ptr<RhoMonitor> mon = std::make_shared<RhoMonitor>();
  auto hist = run_softmax(MACHINES, N, TAU, std::static_pointer_cast<Monitor>(mon));

  print_simulation_results(hist, mon);
}
