#ifndef MEMORYPROGRAMMER_H
#define MEMORYPROGRAMMER_H

#include <cstdint>

class MemoryProgrammer {
public:
    virtual int write(const uint8_t* data, uint32_t size, uint32_t flashOffset = 0) = 0;

    virtual ~MemoryProgrammer();
};

#endif // MEMORYPROGRAMMER_H
