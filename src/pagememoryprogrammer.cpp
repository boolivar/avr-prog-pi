#include "pagememoryprogrammer.h"

#include "instruction.h"
#include "instructionfactory.h"

#include <functional>

int PageMemoryProgrammer::write(const uint8_t* data, uint32_t size, uint32_t flashOffset) {
    for (uint32_t i = 0; i < size; ++i, ++flashOffset) {
        uint8_t pageAddr = flashOffset % pageSize;

        auto pLoadMemoryPage = (pageAddr & 0x01) ? &InstructionFactory::loadMemoryPageHigh : &InstructionFactory::loadMemoryPageLow;
        executor.exchange(std::bind(pLoadMemoryPage, std::placeholders::_1, pageAddr >> 1, data[i]));

        if (pageAddr == (pageSize - 1)) {
            executor.exchange(std::bind(&InstructionFactory::writeMemoryPage, std::placeholders::_1, (flashOffset >> 1) & 0xffff));
        }
    }

    if (flashOffset % pageSize) {
        executor.exchange(std::bind(&InstructionFactory::writeMemoryPage, std::placeholders::_1, (flashOffset >> 1) & 0xffff));
    }
    return 0;
}

PageMemoryProgrammer::PageMemoryProgrammer(OutputController& controller, uint8_t pageSize)
    : executor(controller), pageSize(pageSize) {
}
