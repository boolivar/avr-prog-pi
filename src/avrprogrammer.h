#ifndef AVRPROGRAMMER_H
#define AVRPROGRAMMER_H

#include "instructionexecutor.h"

#include <cinttypes>
#include <vector>

class OutputController;
class ChipSelect;
class MemoryProgrammer;

class AvrProgrammer {
public:
    int reset();
    int erase();

    int writeMemory(const std::vector<uint8_t>& data, uint32_t flashOffset = 0);
    int writeEeprom(const std::vector<uint8_t>& data, uint32_t eepromOffset = 0);
    int writeFuse(uint32_t fuse, uint8_t size, int mode = 0);
    int writeLock(uint8_t lock, int mode = 0);

    std::vector<uint8_t> readMemory(uint32_t size, uint32_t flashOffset = 0);
    std::vector<uint8_t> readEeprom(uint32_t size, uint32_t eepromOffset = 0);
    uint32_t readFuse(uint8_t size, int mode = 0);
    uint8_t readLock(int mode = 0);

    AvrProgrammer(OutputController& controller, MemoryProgrammer& memProg);

private:
    OutputController& controller;
    MemoryProgrammer& memProg;
    InstructionExecutor executor;
};

#endif // AVRPROGRAMMER_H
