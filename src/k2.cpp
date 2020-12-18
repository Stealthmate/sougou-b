#include "EpsilonGreedyStrategy.hpp"
#include "Metrics.hpp"
#include "Kadai.hpp"
#include "Util.hpp"

class MuMetric: public Metric {
public:

  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
    this->machines = sim.machines.size();
    this->mu = std::vector<std::vector<double>>(n, std::vector<double>(this->machines, 0));
    this->strat = dynamic_cast<const EpsilonGreedyStrategy*>(&strat);
  }

  virtual void update(unsigned int i, const Attempt &a) {
    (void) a;
    this->mu[i] = std::vector<double>(this->strat->mu);
  }

  virtual std::string print(unsigned int i) {
    return join(",", this->mu[i]);
  }

  const EpsilonGreedyStrategy *strat;
  std::vector<std::vector<double>> mu;
  unsigned int machines;
};

int main() {

  const double EPSILON = 0.8;

  auto egs = EpsilonGreedyStrategy(5, EPSILON);
  auto mu_m = std::make_shared<MuMetric>();
  run_kadai(egs, {mu_m});
}
