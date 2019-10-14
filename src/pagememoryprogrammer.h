#ifndef PAGEMEMORYPROGRAMMER_H
#define PAGEMEMORYPROGRAMMER_H

#include "memoryprogrammer.h"
#include "instructionexecutor.h"

class OutputController;

class PageMemoryProgrammer: public MemoryProgrammer {
public:
    virtual int write(const uint8_t* data, uint32_t size, uint32_t flashOffset = 0);

    PageMemoryProgrammer(OutputController& controller, uint8_t pageSize);

private:
    OutputController& controller;
    const uint8_t pageSize;
    InstructionExecutor executor;

    void loadPageMemory(uint8_t addr, uint8_t data);
};

#endif // PAGEMEMORYPROGRAMMER_H
