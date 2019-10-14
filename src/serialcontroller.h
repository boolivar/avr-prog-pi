#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "instruction.h"
#include "outputcontroller.h"

class Spi;

class SerialController: public OutputController {
public:
    virtual void enable();
    virtual void disable();
    virtual void delay();
    virtual Instruction send(const Instruction& instruction);

    SerialController(Spi& spi, uint8_t csLevel = 1, uint32_t delayMs = 20);

private:
    Spi& spi;
    uint8_t csLevel;
    uint32_t delayMs;
    uint8_t buf[Instruction::size];
};

#endif // SERIALCONTROLLER_H
