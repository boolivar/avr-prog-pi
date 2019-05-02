#include "instructionfactory.h"

#include "instruction.h"

Instruction InstructionFactory::programmingEnable() const {
    return Instruction(0xac, 0x53, 0x00, 0x00);
}

Instruction InstructionFactory::chipErase() const {
    return Instruction(0xac, 0x80, 0x00, 0x00);
}

Instruction InstructionFactory::pollReady(uint8_t dummy) const {
    return Instruction(0xf0, 0x00, 0x00, dummy);
}

Instruction InstructionFactory::loadExtendedAddress(uint8_t addr) const {
    return Instruction(0x4d, 0x00, addr, 0x00);
}

Instruction InstructionFactory::loadMemoryPageHigh(uint8_t addrLsb, uint8_t high) const {
    return Instruction(0x48, 0x00, addrLsb, high);
}

Instruction InstructionFactory::loadMemoryPageLow(uint8_t addrLsb, uint8_t low) const {
    return Instruction(0x40, 0x00, addrLsb, low);
}

Instruction InstructionFactory::loadEepromPage(uint8_t addr, uint8_t data) const {
    return Instruction(0xc1, 0x00, addr, data);
}

Instruction InstructionFactory::writeMemoryPage(uint16_t addr) const {
    return Instruction(0x4c, addr >> 8, addr & 0xff, 0x00);
}

Instruction InstructionFactory::writeEeprom(uint16_t addr, uint8_t data) const {
    return Instruction(0xc0, addr >> 8, addr & 0xff, data);
}

Instruction InstructionFactory::writeEepromPage(uint16_t addr) const {
    return Instruction(0xc2, addr >> 8, addr & 0xff, 0x00);
}

Instruction InstructionFactory::writeLockBits(uint8_t lock) const {
    return Instruction(0xac, 0xe0, 0x00, lock);
}

Instruction InstructionFactory::writeFuseBits(uint8_t fuse) const {
    return Instruction(0xac, 0xa0, 0x00, fuse);
}

Instruction InstructionFactory::writeFuseHighBits(uint8_t high) const {
    return Instruction(0xac, 0xa8, 0x00, high);
}

Instruction InstructionFactory::writeFuseExtendedBits(uint8_t extended) const {
    return Instruction(0xac, 0xa4, 0x00, extended);
}

Instruction InstructionFactory::readMemoryHigh(uint16_t addr, uint8_t dummy) const {
    return Instruction(0x28, addr >> 8, addr & 0xff, dummy);
}

Instruction InstructionFactory::readMemoryLow(uint16_t addr, uint8_t dummy) const {
    return Instruction(0x20, addr >> 8, addr & 0xff, dummy);
}

Instruction InstructionFactory::readEeprom(uint16_t addr, uint8_t dummy) const {
    return Instruction(0xa0, addr >> 8, addr & 0xff, dummy);
}

Instruction InstructionFactory::readLockBits(uint8_t dummy) const {
    return Instruction(0x58, 0x00, 0x00, dummy);
}

Instruction InstructionFactory::readSignature(uint8_t addr, uint8_t dummy) const {
    return Instruction(0x30, 0x00, addr, dummy);
}

Instruction InstructionFactory::readFuseBits(uint8_t dummy) const {
    return Instruction(0x50, 0x00, 0x00, dummy);
}

Instruction InstructionFactory::readFuseHighBits(uint8_t dummy) const {
    return Instruction(0x58, 0x08, 0x00, dummy);
}

Instruction InstructionFactory::readFuseExtendedBits(uint8_t dummy) const {
    return Instruction(0x50, 0x08, 0x00, dummy);
}

Instruction InstructionFactory::readCalibrationByte(uint8_t dummy) const {
    return Instruction(0x38, 0x00, 0x00, dummy);
}
