#include "SoftmaxStrategy.hpp"

#include <cmath>
#include <iostream>

#include "mt.h"

SoftmaxStrategy::SoftmaxStrategy(unsigned int machines, double tau): Strategy(machines), tau(tau) {}

void SoftmaxStrategy::reset() {
  this->current_pick = 0;
  this->is_interacting = false;
  this->mu = std::vector<double>(this->machines, 0);
  this->trials = std::vector<unsigned int>(this->machines, 0);
  this->rho = std::vector<double>(this->machines, 0);
  this->calculate_rho();
}

unsigned int SoftmaxStrategy::pick() {
  if(this->is_interacting) {
    std::cerr << "Tried to pick before receiving result of previous choice" << std::endl;
    exit(-1);
  }
  this->is_interacting = true;

  double dice = genrand64_real1();

  double cdf = 0;
  for(unsigned int i = 0; i < this->machines; i++) {
    cdf += this->rho[i];
    if(dice <= cdf) {
      this->current_pick = i;
      break;
    }
  }

  return this->current_pick;
}

void SoftmaxStrategy::calculate_rho() {
  double denom = 0;
  for(unsigned int i = 0; i < this->machines; i++) {
    denom += exp(this->mu[i] / this->tau);
  }
  for(unsigned int i = 0; i < this->machines; i++) {
    this->rho[i] = exp(this->mu[i] / this->tau) / denom;
  }
}

void SoftmaxStrategy::accept_result(bool result) {
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
  this->calculate_rho();
}

unsigned int SoftmaxStrategy::current_best() {
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
