#include "serialcontroller.h"

#include "spi.h"

void SerialController::enable() {
    spi.chipSelect(csLevel);
}

void SerialController::disable() {
    spi.chipSelect(!csLevel);
}

Instruction SerialController::send(const Instruction& instruction) {
    memcpy(buf, instruction.getBytes(), Instruction::size);
    spi.transfer(buf, Instruction::size);
    return Instruction(buf);
}

SerialController::SerialController(Spi& spi, uint8_t csLevel)
    : spi(spi), csLevel(csLevel) {
}
