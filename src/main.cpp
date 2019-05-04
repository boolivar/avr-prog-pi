#include "spi.h"
#include "printspi.h"
#include "instruction.h"
#include "instructionfactory.h"
#include "instructionexecutor.h"
#include "pagememoryprogrammer.h"
#include "serialcontroller.h"
#include "printchipselect.h"
#include "pagememoryprogrammer.h"
#include "context.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

Context createContext() {
    Context ctx;

    ctx.setSpi(new PrintSpi);
    ctx.setChipSelect(new PrintChipSelect);
//    ctx.setMemoryProgrammer(new PageMemoryProgrammer(InstructionExecutor(SerialController(*ctx.getSpi())), 4));

    return ctx;
}

int main() {
    Context context = createContext();

    SerialController serial(*context.getSpi());

    InstructionExecutor executor(serial);
    PageMemoryProgrammer memProg(executor, 4);

    uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    memProg.write(data, sizeof(data));

    return 0;
}
