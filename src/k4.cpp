#include "UCBStrategy.hpp"
#include "Metrics.hpp"
#include "Util.hpp"
#include "Kadai.hpp"

class FMetric: public Metric {
public:

  virtual void initialize(const Simulation &sim, const Strategy &strat, unsigned int n) {
    this->machines = sim.machines.size();
    this->F = std::vector<std::vector<double>>(n + 1, std::vector<double>(this->machines, 0));
    this->strat = dynamic_cast<const UCBStrategy*>(&strat);

    this->F[0] = std::vector<double>(this->strat->F);
  }

  virtual void update(unsigned int i, const Attempt &a) {
    (void) a;
    this->F[i + 1] = std::vector<double>(this->strat->F);
  }

  virtual std::string print(unsigned int i) {
    return join(",", this->F[i]);
  }

  const UCBStrategy *strat;
  std::vector<std::vector<double>> F;
  unsigned int machines;
};

int main() {
  const double ALPHA = 1.0;
  auto ucbs = UCBStrategy(5, ALPHA);
  auto F_m = std::make_shared<FMetric>();
  run_kadai(ucbs, {F_m});
}
