#include "instructionfactory.h"

#include "instruction.h"

Instruction InstructionFactory::loadMemoryPageHigh(uint8_t addrLsb, uint8_t high) const {
    return Instruction(0x48, 0x00, addrLsb, high);
}

Instruction InstructionFactory::loadMemoryPageLow(uint8_t addrLsb, uint8_t low) const {
    return Instruction(0x40, 0x00, addrLsb, low);
}

Instruction InstructionFactory::writeMemoryPage(uint8_t addrMsb, uint8_t addrLsb) const {
    return Instruction(0x4c, addrMsb, addrLsb, 00);
}
