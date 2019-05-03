#ifndef AVRCONFIG_H
#define AVRCONFIG_H

#include <cinttypes>

class AvrConfig {
public:
    uint32_t getMemorySize() const { return memorySize; }
    uint32_t getEepromSize() const { return eepromSize; }

    AvrConfig(uint32_t memorySize, uint32_t eepromSize)
        : memorySize(memorySize), eepromSize(eepromSize) {}
private:
    uint32_t memorySize;
    uint32_t eepromSize;
};

#endif // AVRCONFIG_H
