#include "pagememoryprogrammer.h"

#include "serialcontroller.h"
#include "instructionfactory.h"

int PageMemoryProgrammer::write(const uint8_t* data, uint32_t size, uint32_t flashOffset) {
    for (uint32_t i = 0; i < size; ++i, ++flashOffset) {
        uint8_t pageAddr = flashOffset % pageSize;

        auto pLoadMemoryPage = (pageAddr & 0x01) ? &InstructionFactory::loadMemoryPageHigh : &InstructionFactory::loadMemoryPageLow;
        Instruction loadMemoryPage = (instructionFactory.*pLoadMemoryPage)(pageAddr >> 1, data[i]);
        serial.send(loadMemoryPage);

        if (pageAddr == (pageSize - 1)) {
            Instruction writeMemoryPage = instructionFactory.writeMemoryPage((flashOffset >> 1) & 0xffff);
            serial.send(writeMemoryPage);
        }
    }

    if (flashOffset % pageSize) {
        Instruction writeMemoryPage = instructionFactory.writeMemoryPage((flashOffset >> 1) & 0xffff);
        serial.send(writeMemoryPage);
    }

    return size;
}

PageMemoryProgrammer::PageMemoryProgrammer(const InstructionFactory& instructionFacotry, SerialController& serial, uint8_t pageSize)
    : instructionFactory(instructionFacotry), serial(serial), pageSize(pageSize) {
}
