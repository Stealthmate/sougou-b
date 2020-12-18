#include "SoftmaxStrategy.hpp"
#include "Metrics.hpp"
#include "Util.hpp"
#include "Kadai.hpp"

class RhoMetric: public Metric {
public:

  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
    this->machines = sim.machines.size();
    this->rho = std::vector<std::vector<double>>(n + 1, std::vector<double>(this->machines, 0));
    this->strat = dynamic_cast<const SoftmaxStrategy*>(&strat);

    this->rho[0] = std::vector<double>(this->strat->rho);
  }

  virtual void update(unsigned int i, const Attempt &a) {
    (void) a;
    this->rho[i + 1] = std::vector<double>(this->strat->rho);
  }

  virtual std::string print(unsigned int i) {
    return join(",", this->rho[i]);
  }

  const SoftmaxStrategy *strat;
  std::vector<std::vector<double>> rho;
  unsigned int machines;
};

int main() {
  double TAU = 0.5;
  auto sms = SoftmaxStrategy(5, TAU);

  auto rho_m = std::make_shared<RhoMetric>();
  run_kadai(sms, {rho_m});
}
