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

Context createContext(const Config& cfg) {
    std::cout << "Create context" << std::endl;

    Context ctx;
    SpiFactoryImpl spiFactory;
    std::cout << "spi" << std::endl;
    ctx.setSpi(spiFactory.createSpi(0).release());
    std::cout << "cs" << std::endl;
    ctx.setChipSelect(spiFactory.createChipSelect(cfg.getCs()).release());
    std::cout << "output controller" << std::endl;
    ctx.setOutputController(new SerialController(*ctx.getSpi()));
    std::cout << "page memory programmer" << std::endl;
    ctx.setMemoryProgrammer(new PageMemoryProgrammer(*ctx.getOutputController(), cfg.getPage()));
    std::cout << "Context done!" << std::endl;
    return ctx;
}

int main(int argc, char** argv) {
    std::unordered_map<std::string, std::string> props = properties(argc, argv);
    if (props.count("?")) {
        std::cout << "Error parsing command line arguments" << std::endl;
        return -1;
    }

    Config cfg = config(props);
    Context context = createContext(cfg);
    AvrProgrammer programmer(*context.getOutputController(), *context.getMemoryProgrammer(), *context.getChipSelect());

    std::cout << "Reset" << std::endl;
    programmer.reset();

    std::cout << "Read memory" << std::endl;
    std::vector<uint8_t> data = programmer.readMemory(cfg.getSize());

    std::cout << "Write " << cfg.getFileName() << std::endl;
    std::ofstream ofs(cfg.getFileName(), std::ofstream::out);
    std::copy(data.begin(), data.end(), std::ostream_iterator<uint8_t>(ofs));

    return 0;
}
