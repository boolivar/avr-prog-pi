#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "instruction.h"

#include <cstdint>

class Spi;
class ChipSelect;

class SerialController {
public:
    Instruction send(const Instruction& instruction);

    SerialController(Spi& spi, ChipSelect& chipSelect);

private:
    Spi& spi;
    ChipSelect& chipSelect;

    uint8_t buf[Instruction::size];
};

#endif // SERIALCONTROLLER_H
