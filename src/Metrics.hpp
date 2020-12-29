#ifndef METRICS_HPP
#define METRICS_HPP

#include "Simulation.hpp"

std::vector<unsigned int> attempt_numbers(const SimulationHistory &hist);
std::vector<unsigned int> engaged_machines(const SimulationHistory &hist);
std::vector<double> average_reward(const SimulationHistory &hist);
std::vector<double> cdr(const SimulationHistory &hist);



#endif
