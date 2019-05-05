#include "avrconfig.h"
#include "avrprogrammer.h"
#include "context.h"
#include "pagememoryprogrammer.h"
#include "printchipselect.h"
#include "printspi.h"
#include "serialcontroller.h"

#include <vector>

Context createContext(const AvrConfig& config) {
    Context ctx;
    ctx.setSpi(new PrintSpi);
    ctx.setChipSelect(new PrintChipSelect);
    ctx.setOutputController(new SerialController(*ctx.getSpi()));
    ctx.setMemoryProgrammer(new PageMemoryProgrammer(*ctx.getOutputController(), config.getPageSize()));
    return ctx;
}

int main() {
    AvrConfig config(0x1000, 0x200, 64, 2);
    Context context = createContext(config);
    AvrProgrammer programmer(config, *context.getOutputController(), *context.getMemoryProgrammer(), *context.getChipSelect());

    uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<uint8_t> vector(data, data + sizeof (data));

    programmer.writeMemory(vector);

    return 0;
}
