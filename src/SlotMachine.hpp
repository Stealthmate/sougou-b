#ifndef SLOT_MACHINE_HPP
#define SLOT_MACHINE_HPP

class SlotMachine {
 public:
  SlotMachine(double p);

  bool engage() const;

  double probability() const;

 private:
  double p;
};

#endif
