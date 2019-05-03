#include "serialcontroller.h"

#include "spi.h"
#include "chipselect.h"

Instruction SerialController::send(const Instruction &instruction) {
    memcpy(buf, instruction.getBytes(), Instruction::size);
    spi.transfer(buf, Instruction::size);
    return Instruction(buf);
}

SerialController::SerialController(Spi& spi)
    : spi(spi) {
}
