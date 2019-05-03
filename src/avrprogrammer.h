#ifndef AVRPROGRAMMER_H
#define AVRPROGRAMMER_H

#include <cinttypes>
#include <vector>

class AvrConfig;
class ChipSelect;
class InstructionExecutor;
class MemoryProgrammer;

class AvrProgrammer {
public:
    int reset();
    int erase();

    int writeMemory(const std::vector<uint8_t>& data, uint32_t flashOffset = 0);
    int writeEeprom(const std::vector<uint8_t>& data, uint32_t eepromOffset = 0);
    int writeFuse(uint32_t fuse, int mode = 0);
    int writeLock(uint8_t lock, int mode = 0);

    std::vector<uint8_t> readMemory(uint32_t flashOffset = 0);
    std::vector<uint8_t> readEeprom(uint32_t flashOffset = 0);
    uint32_t readFuse(int mode = 0);
    uint8_t readLock(int mode = 0);

    AvrProgrammer(const AvrConfig& config, InstructionExecutor& executor, MemoryProgrammer& memProg, ChipSelect& cs);

private:
    const AvrConfig& config;
    InstructionExecutor& executor;
    MemoryProgrammer& memProg;
    ChipSelect& cs;
};

#endif // AVRPROGRAMMER_H
