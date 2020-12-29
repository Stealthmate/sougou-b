#include "EpsilonGreedyStrategy.hpp"

#include <iostream>

#include "mt.h"

#include "Util.hpp"

EpsilonGreedyStrategy::EpsilonGreedyStrategy(unsigned int machines, double epsilon): Strategy(machines), epsilon(epsilon) {}

void EpsilonGreedyStrategy::reset() {
  this->current_pick = 0;
  this->is_interacting = false;
  this->mu = std::vector<double>(this->machines, 0);
  this->trials = std::vector<unsigned int>(this->machines, 0);
}

unsigned int EpsilonGreedyStrategy::pick() {
  if(this->is_interacting) {
    std::cerr << "Tried to pick before receiving result of previous choice" << std::endl;
    exit(-1);
  }
  this->is_interacting = true;
  bool explore = genrand64_real1() < this->epsilon;

  if(explore) {
    this->current_pick = genrand64_int63() % this->machines;
  } else {
    this->current_pick = argmax(this->mu);
  }

  return this->current_pick;
}

void EpsilonGreedyStrategy::accept_result(bool result) {
  if(!this->is_interacting) {
    std::cerr << "Received result, without calling pick()" << std::endl;
    exit(-1);
  }
  this->is_interacting = false;

  double old_avg = this->mu[this->current_pick];
  unsigned int n = this->trials[this->current_pick];

  double new_avg = (old_avg * n + (result ? 1.0 : 0.0)) / (n + 1);

  this->mu[this->current_pick] = new_avg;
  this->trials[this->current_pick] += 1;
}
