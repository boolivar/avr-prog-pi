#ifndef PAGEMEMORYPROGRAMMER_H
#define PAGEMEMORYPROGRAMMER_H

#include "cinttypes"

class SerialController;
class Instruction;
class InstructionFactory;

class PageMemoryProgrammer {
public:
    int write(const uint8_t* data, uint32_t size, uint32_t flashOffset = 0);

    PageMemoryProgrammer(const InstructionFactory& instructionFactory, SerialController& serial, uint8_t pageSize);

private:
    const InstructionFactory& instructionFactory;
    SerialController& serial;
    const uint8_t pageSize;
};

#endif // PAGEMEMORYPROGRAMMER_H
