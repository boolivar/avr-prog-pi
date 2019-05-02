#include "serialcontroller.h"

#include "spi.h"
#include "chipselect.h"
#include "instruction.h"

#include <cstring>

Instruction SerialController::send(const Instruction &instruction) {
    memcpy(buf, instruction.getBytes(), Instruction::size);
    spi.transfer(buf, Instruction::size);
    return Instruction(buf);
}

SerialController::SerialController(Spi& spi, ChipSelect& chipSelect)
    : spi(spi), chipSelect(chipSelect) {
}
