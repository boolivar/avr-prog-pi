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
    InstructionExecutor executor;
    const uint8_t pageSize;
};

#endif // PAGEMEMORYPROGRAMMER_H
