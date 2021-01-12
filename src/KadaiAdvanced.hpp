#ifndef KADAI_ADVANCED_HPP
#define KADAI_ADVANCED_HPP

#include "Strategy.hpp"

// スロットマシン1本体
extern "C" int slotMachine1( int id );
extern "C" int slotMachine2( int id );
extern "C" int slotMachine3( int id );

// スロットマシン1の後始末
extern "C" void terminateSlotMachine1(void);
extern "C" void terminateSlotMachine2(void);
extern "C" void terminateSlotMachine3(void);

typedef int (*engage_f)(int);
double runsim(unsigned int n, Strategy &strat, engage_f f);

#endif
