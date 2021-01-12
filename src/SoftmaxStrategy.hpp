#ifndef SOFTMAX_STRATEGY_HPP
#define SOFTMAX_STRATEGY_HPP

#include "Strategy.hpp"

class SoftmaxStrategy: public Strategy {
public:
  SoftmaxStrategy(unsigned int machines, double tau);
  virtual void reset();
  virtual unsigned int pick();
  virtual void accept_result(bool result);
  virtual void calculate_rho();

  virtual unsigned int current_best();

  double tau;
  std::vector<unsigned int> trials;
  std::vector<double> mu;
  std::vector<double> rho;
  bool is_interacting;
  unsigned int current_pick;
};

#endif
