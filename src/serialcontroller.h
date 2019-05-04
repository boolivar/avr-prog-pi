#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "instruction.h"
#include "outputcontroller.h"

class Spi;

class SerialController: public OutputController {
public:
    virtual Instruction send(const Instruction& instruction);

    SerialController(Spi& spi);

private:
    Spi& spi;

    uint8_t buf[Instruction::size];
};

#endif // SERIALCONTROLLER_H
