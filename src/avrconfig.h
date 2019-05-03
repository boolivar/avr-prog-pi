#ifndef AVRCONFIG_H
#define AVRCONFIG_H

#include <cinttypes>

class AvrConfig {
public:
    uint32_t getMemorySize() const { return memorySize; }
    uint32_t getEepromSize() const { return eepromSize; }
    uint8_t getFuseSize() const { return fuseSize; }

    AvrConfig(uint32_t memorySize, uint32_t eepromSize, uint8_t fuseSize = 0)
        : memorySize(memorySize), eepromSize(eepromSize), fuseSize(fuseSize) {}
private:
    uint32_t memorySize;
    uint32_t eepromSize;
    uint8_t fuseSize;
};

#endif // AVRCONFIG_H
