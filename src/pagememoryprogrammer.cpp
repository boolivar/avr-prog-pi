#include "pagememoryprogrammer.h"

#include "instruction.h"
#include "instructionfactory.h"
#include "outputcontroller.h"

#include <functional>

int PageMemoryProgrammer::write(const uint8_t* data, uint32_t size, uint32_t flashOffset) {
    for (uint32_t i = 0; i < size; ++i, ++flashOffset) {
        uint8_t pageAddr = flashOffset % pageSize;

        loadPageMemory(pageAddr, data[i]);

        if (pageAddr == (pageSize - 1)) {
            executor.exchange(std::bind(&InstructionFactory::writeMemoryPage, std::placeholders::_1, (flashOffset >> 1) & 0xffff));
            controller.wait();
        }
    }

    if (flashOffset % pageSize) {
        executor.exchange(std::bind(&InstructionFactory::writeMemoryPage, std::placeholders::_1, (flashOffset >> 1) & 0xffff));
        controller.wait();
    }
    return 0;
}

PageMemoryProgrammer::PageMemoryProgrammer(OutputController& controller, uint8_t pageSize)
    : controller(controller), pageSize(pageSize * 2), executor(controller) {
}

void PageMemoryProgrammer::loadPageMemory(uint8_t addr, uint8_t data) {
    auto pLoadMemoryPage = (addr & 0x01) ? &InstructionFactory::loadMemoryPageHigh : &InstructionFactory::loadMemoryPageLow;
    executor.exchange(std::bind(pLoadMemoryPage, std::placeholders::_1, addr >> 1, data));
}
