#include "SlotMachine.hpp"

#include "mt.h"

SlotMachine::SlotMachine(double p): p(p) {}

bool SlotMachine::engage() const {
  return genrand64_real1() < this->p;
}

double SlotMachine::probability() const {
  return this->p;
}
