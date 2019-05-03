#include "avrprogrammer.h"

#include "avrconfig.h"
#include "chipselect.h"
#include "instructionexecutor.h"
#include "instructionfactory.h"
#include "instruction.h"
#include "memoryprogrammer.h"

#include <functional>

int AvrProgrammer::reset() {
    cs.enable();
    cs.disable();

    executor.exchange(&InstructionFactory::programmingEnable);
    return 0;
}

int AvrProgrammer::erase() {
    executor.exchange(&InstructionFactory::chipErase);
    return 0;
}

int AvrProgrammer::writeMemory(const std::vector<uint8_t>& data, uint32_t flashOffset) {
    return memProg.write(data.data(), data.size(), flashOffset);
}

int AvrProgrammer::writeEeprom(const std::vector<uint8_t>& data, uint32_t eepromOffset) {
    return -1;
}

int AvrProgrammer::writeFuse(uint32_t fuse, int mode) {

}

int AvrProgrammer::writeLock(uint8_t lock, int mode) {

}

std::vector<uint8_t> AvrProgrammer::readMemory(uint32_t flashOffset) {
    std::vector<uint8_t> memory(config.getMemorySize());
    for (; flashOffset < config.getMemorySize(); ++flashOffset) {
        auto op = flashOffset & 0x01 ? &InstructionFactory::readMemoryHigh : &InstructionFactory::readMemoryLow;
        Instruction response = executor.exchange(std::bind(op, std::placeholders::_1, flashOffset >> 1, 0xaa));
        memory[flashOffset] = response.getBytes()[3];
    }
    return memory;
}

uint32_t AvrProgrammer::readFuse(int mode) {

}

uint8_t AvrProgrammer::readLock(int mode) {

}

AvrProgrammer::AvrProgrammer(const AvrConfig& config, InstructionExecutor &executor, MemoryProgrammer &memProg, ChipSelect &cs)
    : config(config), executor(executor), memProg(memProg), cs(cs) {
}
