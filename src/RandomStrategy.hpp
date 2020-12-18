#ifndef RANDOM_STRATEGY_HPP
#define RANDOM_STRATEGY_HPP

#include "Strategy.hpp"

class RandomStrategy: public Strategy {
public:
  RandomStrategy(unsigned int machines);
  virtual void reset();
  virtual unsigned int pick();
};

#endif
