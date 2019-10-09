#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "instruction.h"
#include "outputcontroller.h"

class Spi;

class SerialController: public OutputController {
public:
    virtual void enable();
    virtual void disable();
    virtual Instruction send(const Instruction& instruction);

    SerialController(Spi& spi, uint8_t csLevel = 1);

private:
    Spi& spi;
    uint8_t csLevel;

    uint8_t buf[Instruction::size];
};

#endif // SERIALCONTROLLER_H
