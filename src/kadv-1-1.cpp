#include "KadaiAdvanced.hpp"

#include "UCBStrategy.hpp"

#include <iostream>

const unsigned int M = 10;

int main() {
  UCBStrategy strat = UCBStrategy(M, 0.18);
  double avg = runsim(10000, strat, slotMachine1);
  std::cout << "OPT: " << strat.current_best() + 1 << std::endl;
  std::cout << "AVG: " << avg << std:: endl;
  terminateSlotMachine1();
}
