#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

#include "RandomStrategy.hpp"
#include "EpsilonGreedyStrategy.hpp"
#include "SoftmaxStrategy.hpp"
#include "UCBStrategy.hpp"
#include "Simulation.hpp"

extern unsigned long long SEED;

void init(unsigned long long seed = SEED);

unsigned int best_machine(const std::vector<SlotMachine> &machines);

SimulationHistory run_random(const std::vector<SlotMachine> &machines, unsigned int N, std::shared_ptr<Monitor> monitor);

SimulationHistory run_epsilon_greedy(const std::vector<SlotMachine> &machines, unsigned int N, double epsilon, std::shared_ptr<Monitor> monitor);

SimulationHistory run_softmax(const std::vector<SlotMachine> &machines, unsigned int N, double tau, std::shared_ptr<Monitor> monitor);

SimulationHistory run_ucb(const std::vector<SlotMachine> &machines, unsigned int N, double alpha, std::shared_ptr<Monitor> monitor);

#endif
