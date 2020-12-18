#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <vector>

#include "SlotMachine.hpp"

class Strategy {
public:
  Strategy(unsigned int machines);

  virtual void reset() =0;
  virtual unsigned int pick() =0;
  virtual void accept_result(bool result);

protected:
  unsigned int machines;
};


#endif
