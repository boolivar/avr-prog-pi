#include "avrconfig.h"
#include "avrprogrammer.h"
#include "context.h"
#include "pagememoryprogrammer.h"
#include "printchipselect.h"
#include "printspi.h"
#include "rawdatareader.h"
#include "serialcontroller.h"

#include <istream>
#include <sstream>
#include <string>
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
    AvrConfig atmega8Cfg(0x1000, 0x200, 64, 2);
    Context context = createContext(atmega8Cfg);
    AvrProgrammer programmer(atmega8Cfg, *context.getOutputController(), *context.getMemoryProgrammer(), *context.getChipSelect());
    RawDataReader rdr;

    std::istringstream in({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::vector<uint8_t> vector = rdr.readData(in);

    programmer.reset();
    programmer.erase();
    programmer.writeMemory(vector);

    return 0;
}
