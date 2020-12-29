#ifndef KADAI_HPP
#define KADAI_HPP

#include <memory>
#include <vector>

#include "SlotMachine.hpp"
#include "Simulation.hpp"

extern const std::vector<SlotMachine> MACHINES;
extern const unsigned int N;

void print_simulation_results(const SimulationHistory &hist, std::shared_ptr<MachineScoreMonitor> msm = nullptr);

#endif
