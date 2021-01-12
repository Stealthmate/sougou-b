#include "UCBStrategy.hpp"

#include <cmath>
#include <iostream>

#include "mt.h"

#include "Util.hpp"

UCBStrategy::UCBStrategy(unsigned int machines, double alpha): Strategy(machines), alpha(alpha) {}

void UCBStrategy::reset() {
  this->current_pick = 0;
  this->is_interacting = false;
  this->mu = std::vector<double>(this->machines, 0);
  this->trials = std::vector<unsigned int>(this->machines, 0);
  this->F = std::vector<double>(this->machines, 0);
  this->n = 0;
  this->calculate_F();
}

unsigned int UCBStrategy::pick() {
  if(this->is_interacting) {
    std::cerr << "Tried to pick before receiving result of previous choice" << std::endl;
    exit(-1);
  }
  this->is_interacting = true;

  this->current_pick = argmax(this->F);

  return this->current_pick;
}

void UCBStrategy::calculate_F() {
  for(unsigned int i = 0; i < this->machines; i++) {
    this->F[i] = this->mu[i] + sqrt(this->alpha * log(this->n) / (1 + this->trials[i]));
  }
}

void UCBStrategy::accept_result(bool result) {
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
  this->calculate_F();
  this->n += 1;
}

unsigned int UCBStrategy::current_best() {
  unsigned int j = 0;
  double max_mu = -1;
  for(unsigned int i = 0; i < this->machines; i++) {
    if(this->mu[i] > max_mu) {
      max_mu = this->mu[i];
      j = i;
    }
  }

  return j;
}
