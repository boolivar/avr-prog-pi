#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include <cinttypes>

class Instruction;

class InstructionFactory {
public:
    Instruction programmingEnable() const;
    Instruction chipErase() const;
    Instruction pollReady(uint8_t dummy = 0) const;

    Instruction loadExtendedAddress(uint8_t addr) const;
    Instruction loadMemoryPageHigh(uint8_t addrLsb, uint8_t high) const;
    Instruction loadMemoryPageLow(uint8_t addrLsb, uint8_t low) const;
    Instruction loadEepromPage(uint8_t addr, uint8_t data) const;

    Instruction writeMemoryPage(uint16_t addr) const;
    Instruction writeEeprom(uint16_t addr, uint8_t data) const;
    Instruction writeEepromPage(uint16_t addr) const;
    Instruction writeLockBits(uint8_t lock) const;
    Instruction writeFuseBits(uint8_t fuse) const;
    Instruction writeFuseHighBits(uint8_t high) const;
    Instruction writeFuseExtendedBits(uint8_t extended) const;

    Instruction readMemoryHigh(uint16_t addr, uint8_t dummy = 0) const;
    Instruction readMemoryLow(uint16_t addr, uint8_t dummy = 0) const;
    Instruction readEeprom(uint16_t addr, uint8_t dummy = 0) const;
    Instruction readLockBits(uint8_t dummy = 0) const;
    Instruction readSignature(uint8_t addr, uint8_t dummy = 0) const;
    Instruction readFuseBits(uint8_t dummy = 0) const;
    Instruction readFuseHighBits(uint8_t dummy = 0) const;
    Instruction readFuseExtendedBits(uint8_t dummy = 0) const;
    Instruction readCalibrationByte(uint8_t dummy = 0) const;
};

#endif // INSTRUCTIONFACTORY_H
