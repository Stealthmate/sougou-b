#ifndef UCB_STRATEGY_HPP
#define UCB_STRATEGY_HPP

#include "Strategy.hpp"

class UCBStrategy: public Strategy {
public:
  UCBStrategy(unsigned int machines, double alpha);
  virtual void reset();
  virtual unsigned int pick();
  virtual void accept_result(bool result);
  virtual void calculate_F();

  double alpha;
  std::vector<unsigned int> trials;
  std::vector<double> mu;
  std::vector<double> F;
  bool is_interacting;
  unsigned int current_pick;
  unsigned int n;
};

#endif
