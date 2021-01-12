#include "RandomStrategy.hpp"

#include "mt.h"

RandomStrategy::RandomStrategy(unsigned int machines) : Strategy(machines) {}

void RandomStrategy::reset() {}

unsigned int RandomStrategy::pick() {
  return genrand64_int63() % this->machines;
};

unsigned int RandomStrategy::current_best() {
  return this->pick();
}
