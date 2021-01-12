#ifndef EPSILON_GREEDY_STRATEGY_HPP
#define EPSILON_GREEDY_STRATEGY_HPP

#include "Strategy.hpp"

class EpsilonGreedyStrategy: public Strategy {
public:
  EpsilonGreedyStrategy(unsigned int machines, double epsilon);
  virtual void reset();
  virtual unsigned int pick();
  virtual void accept_result(bool result);

  virtual unsigned int current_best();

  double epsilon;
  std::vector<unsigned int> trials;
  std::vector<double> mu;
  bool is_interacting;
  unsigned int current_pick;
};

#endif
