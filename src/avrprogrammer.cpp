#include "avrprogrammer.h"

#include "avrconfig.h"
#include "instructionexecutor.h"
#include "instructionfactory.h"
#include "instruction.h"
#include "memoryprogrammer.h"
#include "outputcontroller.h"

#include <functional>

int AvrProgrammer::reset() {
    controller.enable();
    controller.disable();

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
    for (std::vector<uint8_t>::const_iterator it = data.cbegin(); it != data.cend(); ++it, ++eepromOffset) {
        executor.exchange(std::bind(&InstructionFactory::writeEeprom, std::placeholders::_1, eepromOffset, *it));
    }
    return -1;
}

int AvrProgrammer::writeFuse(uint32_t fuse, uint8_t size, int mode) {
    executor.exchange(std::bind(&InstructionFactory::writeFuseBits, std::placeholders::_1, fuse));
    if (size > 1) {
        executor.exchange(std::bind(&InstructionFactory::writeFuseHighBits, std::placeholders::_1, fuse >> 8));
        if (size > 2) {
            executor.exchange(std::bind(&InstructionFactory::writeFuseExtendedBits, std::placeholders::_1, fuse >> 16));
        }
    }
}

int AvrProgrammer::writeLock(uint8_t lock, int mode) {
    executor.exchange(std::bind(&InstructionFactory::writeLockBits, std::placeholders::_1, lock));
    return 0;
}

std::vector<uint8_t> AvrProgrammer::readMemory(uint32_t size, uint32_t flashOffset) {
    std::vector<uint8_t> memory(size);
    for (uint32_t i = 0; i < size; ++i, ++flashOffset) {
        auto op = flashOffset & 0x01 ? &InstructionFactory::readMemoryHigh : &InstructionFactory::readMemoryLow;
        Instruction response = executor.exchange(std::bind(op, std::placeholders::_1, flashOffset >> 1, 0xaa));
        memory[i] = response.getBytes()[3];
    }
    return memory;
}

std::vector<uint8_t> AvrProgrammer::readEeprom(uint32_t size, uint32_t eepromOffset) {
    std::vector<uint8_t> data(size);
    for (uint32_t i = 0; i < size; ++i, ++eepromOffset) {
        Instruction response = executor.exchange(std::bind(&InstructionFactory::readEeprom, std::placeholders::_1, eepromOffset, 0xaa));
        data[i] = response.getBytes()[3];
    }
    return data;
}

uint32_t AvrProgrammer::readFuse(uint8_t size, int mode) {
    Instruction low = executor.exchange(std::bind(&InstructionFactory::readFuseBits, std::placeholders::_1, 0xaa));
    uint32_t fuse = low.getBytes()[3];
    if (size > 1) {
        Instruction high = executor.exchange(std::bind(&InstructionFactory::readFuseHighBits, std::placeholders::_1, 0xaa));
        fuse |= (static_cast<uint32_t>(high.getBytes()[3]) << 8);

        if (size > 2) {
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

AvrProgrammer::AvrProgrammer(OutputController& controller, MemoryProgrammer& memProg)
    : controller(controller), memProg(memProg), executor(controller) {
}
