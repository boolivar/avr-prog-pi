#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include <cinttypes>

class Instruction;

class InstructionFactory {
public:
    Instruction loadMemoryPageHigh(uint8_t addrLsb, uint8_t high) const;
    Instruction loadMemoryPageLow(uint8_t addrLsb, uint8_t low) const;
    Instruction writeMemoryPage(uint8_t addrMsb, uint8_t addrLsb) const;
};

#endif // INSTRUCTIONFACTORY_H
