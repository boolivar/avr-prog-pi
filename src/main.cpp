#include "avrconfig.h"
#include "avrprogrammer.h"
#include "context.h"
#include "pagememoryprogrammer.h"
#include "printchipselect.h"
#include "printspi.h"
#include "rawdatareader.h"
#include "serialcontroller.h"
#include "spifactoryimpl.h"

#include <istream>
#include <sstream>
#include <string>
#include <vector>

Context createContext(const AvrConfig& config, SpiFactory& spiFactory) {
    Context ctx;
    ctx.setSpi(spiFactory.createSpi().release());
    ctx.setChipSelect(spiFactory.createChipSelect().release());
    ctx.setOutputController(new SerialController(*ctx.getSpi()));
    ctx.setMemoryProgrammer(new PageMemoryProgrammer(*ctx.getOutputController(), config.getPageSize()));
    return ctx;
}

int main() {
    AvrConfig atmega8Cfg(0x1000, 0x200, 64, 2);
    SpiFactoryImpl spiFactory;
    Context context = createContext(atmega8Cfg, spiFactory);
    AvrProgrammer programmer(atmega8Cfg, *context.getOutputController(), *context.getMemoryProgrammer(), *context.getChipSelect());
    RawDataReader rdr;

    std::istringstream in({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::vector<uint8_t> vector = rdr.readData(in);

    programmer.reset();
    programmer.erase();
    programmer.writeMemory(vector);

    return 0;
}
