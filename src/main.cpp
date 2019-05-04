#include "printspi.h"
#include "instructionexecutor.h"
#include "pagememoryprogrammer.h"
#include "serialcontroller.h"
#include "printchipselect.h"
#include "pagememoryprogrammer.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

int main() {
    PrintSpi spi;
    PrintChipSelect cs;
    SerialController serial(spi);
    InstructionExecutor executor(serial);

    PageMemoryProgrammer memProg(executor, 4);

    uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    memProg.write(data, sizeof(data));

    return 0;
}
