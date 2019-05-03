#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "instruction.h"

class Spi;

class SerialController {
public:
    Instruction send(const Instruction& instruction);

    SerialController(Spi& spi);

private:
    Spi& spi;

    uint8_t buf[Instruction::size];
};

#endif // SERIALCONTROLLER_H
