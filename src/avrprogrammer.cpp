#include "avrprogrammer.h"

#include "avrconfig.h"
#include "chipselect.h"
#include "instructionexecutor.h"
#include "instructionfactory.h"
#include "instruction.h"
#include "memoryprogrammer.h"
#include "outputcontroller.h"

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
    executor.exchange(std::bind(&InstructionFactory::writeFuseBits, std::placeholders::_1, fuse));
    if (config.getFuseSize() > 1) {
        executor.exchange(std::bind(&InstructionFactory::writeFuseHighBits, std::placeholders::_1, fuse >> 8));
        if (config.getFuseSize() > 2) {
            executor.exchange(std::bind(&InstructionFactory::writeFuseExtendedBits, std::placeholders::_1, fuse >> 16));
        }
    }
}

int AvrProgrammer::writeLock(uint8_t lock, int mode) {
    executor.exchange(std::bind(&InstructionFactory::writeLockBits, std::placeholders::_1, lock));
    return 0;
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
    Instruction low = executor.exchange(std::bind(&InstructionFactory::readFuseBits, std::placeholders::_1, 0xaa));
    uint32_t fuse = low.getBytes()[3];
    if (config.getFuseSize() > 1) {
        Instruction high = executor.exchange(std::bind(&InstructionFactory::readFuseHighBits, std::placeholders::_1, 0xaa));
        fuse |= (static_cast<uint32_t>(high.getBytes()[3]) << 8);

        if (config.getFuseSize() > 2) {
            Instruction extended = executor.exchange(std::bind(&InstructionFactory::readFuseExtendedBits, std::placeholders::_1, 0xaa));
            fuse |= (static_cast<uint32_t>(extended.getBytes()[3]) << 16);
        }
    }
    return fuse;
}

uint8_t AvrProgrammer::readLock(int mode) {
    Instruction response = executor.exchange(std::bind(&InstructionFactory::readLockBits, std::placeholders::_1, 0xaa));
    return response.getBytes()[3];
}

AvrProgrammer::AvrProgrammer(const AvrConfig& config, OutputController& controller, MemoryProgrammer &memProg, ChipSelect &cs)
    : config(config), executor(controller), memProg(memProg), cs(cs) {
}
