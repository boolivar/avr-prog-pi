#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>
#include <cstring>

class Instruction {
public:
    static const int size = 4;

    const uint8_t* getBytes() const { return reinterpret_cast<const uint8_t*>(&payload); }
    uint32_t getValue() const { return payload; }

    Instruction(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
        : payload((byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1) {
    }
    Instruction(const uint8_t* bytes)
        : payload((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]) {
    }

    Instruction& operator=(const Instruction&) = delete;

private:
    uint32_t payload;
};

#endif // INSTRUCTION_H
