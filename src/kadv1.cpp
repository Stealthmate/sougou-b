#include "UCBStrategy.hpp"

#include <iostream>
#include <tuple>


// スロットマシン1本体
extern "C" int slotMachine1( int id );
extern "C" int slotMachine2( int id );
extern "C" int slotMachine3( int id );

// スロットマシン1の後始末
extern "C" void terminateSlotMachine1(void);
extern "C" void terminateSlotMachine2(void);
extern "C" void terminateSlotMachine3(void);

typedef int (*sm_f)(int);
typedef void (*tm_f)(void);

#ifndef PATTERN
#error define pattern
#elif PATTERN == 1
unsigned int M = 10;
sm_f F = slotMachine1;
tm_f TF = terminateSlotMachine1;
#elif PATTERN == 2
unsigned int M = 20;
sm_f F = slotMachine2;
tm_f TF = terminateSlotMachine2;
#elif PATTERN == 3
unsigned int M = 10;
sm_f F = slotMachine3;
tm_f TF = terminateSlotMachine3;
#endif


typedef int (*engage_f)(int);
double runsim(unsigned int n, Strategy &strat, engage_f f) {
  strat.reset();
  double avg = 0;
  for(unsigned int i = 0; i < n; i++) {
    int result = f(strat.pick() + 1);
    avg += result;
    strat.accept_result(result);
  }

  return avg / n;
}

int main() {
  UCBStrategy strat = UCBStrategy(M, 0.12);
  double avg = runsim(10000, strat, F);
  std::cout << strat.current_best() + 1 << "," << avg << std::endl;
  TF();
}
