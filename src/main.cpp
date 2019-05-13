#include "avrconfig.h"
#include "avrprogrammer.h"
#include "context.h"
#include "pagememoryprogrammer.h"
#include "printchipselect.h"
#include "printspi.h"
#include "rawdatareader.h"
#include "serialcontroller.h"
#include "spifactoryimpl.h"
#include "options.h"

#include <algorithm>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

Context createContext(const AvrConfig& config, SpiFactory& spiFactory) {
    std::cout << "Create context" << std::endl;
    std::cout << "page size: " << static_cast<int>(config.getPageSize()) << std::endl;
    Context ctx;
    std::cout << "spi" << std::endl;
    ctx.setSpi(spiFactory.createSpi().release());
    std::cout << "cs" << std::endl;
    ctx.setChipSelect(spiFactory.createChipSelect().release());
    std::cout << "output controller" << std::endl;
    ctx.setOutputController(new SerialController(*ctx.getSpi()));
    std::cout << "page memory programmer" << std::endl;
    ctx.setMemoryProgrammer(new PageMemoryProgrammer(*ctx.getOutputController(), config.getPageSize()));
    std::cout << "Context done!" << std::endl;
    return ctx;
}

int main(int argc, char** argv) {
    std::unordered_map<std::string, std::string> props = properties(argc, argv);
    if (props.count("?")) {
        std::cout << "Error parsing command line arguments" << std::endl;
        return -1;
    }

    AvrConfig atmega8Cfg(0x1000, 0x200, 64, 2);
    SpiFactoryImpl spiFactory;
    Context context = createContext(atmega8Cfg, spiFactory);
    AvrProgrammer programmer(atmega8Cfg, *context.getOutputController(), *context.getMemoryProgrammer(), *context.getChipSelect());

    std::cout << "Reset" << std::endl;
    programmer.reset();

    std::cout << "Read memory" << std::endl;
    std::vector<uint8_t> data = programmer.readMemory();

    std::cout << "Write out.bin" << std::endl;
    std::ofstream ofs("out.bin", std::ofstream::out);
    std::copy(data.begin(), data.end(), std::ostream_iterator<uint8_t>(ofs));

    return 0;
}
