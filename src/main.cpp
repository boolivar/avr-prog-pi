#include "avrprogrammer.h"
#include "context.h"
#include "intelhexfilereader.h"
#include "pagememoryprogrammer.h"
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

static Context createContext(const Config& cfg);
static std::vector<uint8_t> readMem(AvrProgrammer& programmer, avr_mem_t mem, size_t size);
static int writeMem(AvrProgrammer& programmer, const std::vector<uint8_t>& data, avr_mem_t mem, size_t size);

int main(int argc, char** argv) {
    std::unordered_map<std::string, std::string> props = properties(argc, argv);
    if (props.count("?")) {
        std::cout << "Error parsing command line arguments" << std::endl;
        return -1;
    }

    Config cfg = config(props);
    Context context = createContext(cfg);
    AvrProgrammer programmer(*context.getOutputController(), *context.getMemoryProgrammer());

    std::cout << "Reset" << std::endl;
    programmer.reset();

    if (cfg.isWrite()) {
        std::cout << "Memory write from " << cfg.getFileName() << std::endl;
        std::ifstream ifs(cfg.getFileName(), std::ifstream::binary);
        std::vector<uint8_t> data = context.getDataFormat()->read(ifs);
        writeMem(programmer, data, cfg.getMemory(), cfg.getSize());
    } else {
        std::cout << "Memory read to " << cfg.getFileName() << std::endl;
        std::ofstream ofs(cfg.getFileName(), std::ofstream::binary | std::ofstream::trunc);
        std::vector<uint8_t> data = readMem(programmer, cfg.getMemory(), cfg.getSize());
        context.getDataFormat()->write(data, ofs);
    }
    return 0;
}

Context createContext(const Config& cfg) {
    std::cout << "Create context" << std::endl;
    Context ctx;
    SpiFactoryImpl spiFactory;

    std::cout << "spi 0 " << cfg.getClock() << "Hz" << std::endl;
    ctx.setSpi(spiFactory.createSpi(0, cfg.getCs()).release());

    ctx.getSpi()->setMode(0);
    ctx.getSpi()->setSpeedHz(cfg.getClock());

    std::cout << "output controller" << std::endl;
    ctx.setOutputController(new SerialController(*ctx.getSpi()));

    std::cout << "page memory programmer " << cfg.getPage() << std::endl;
    ctx.setMemoryProgrammer(new PageMemoryProgrammer(*ctx.getOutputController(), cfg.getPage()));

    std::cout << "data reader " << cfg.getFormat() << std::endl;
    if (cfg.getFormat() == HEX) {
        ctx.setDataFormat(new IntelHexFileReader());
    } else {
        ctx.setDataFormat(new RawDataReader());
    }

    return ctx;
}

std::vector<uint8_t> readMem(AvrProgrammer& programmer, avr_mem_t mem, size_t size) {
    if (mem == LOCK) {
        std::cout << "Read lock" << std::endl;
        uint8_t lock = programmer.readLock();
        return std::vector<uint8_t>(1, lock);
    } else if (mem == FUSE) {
        std::cout << "Read fuse " << size << " bytes" << std::endl;
        uint32_t fuse = programmer.readFuse(size);
        return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(&fuse), reinterpret_cast<uint8_t*>(&fuse) + size);
    } else if (mem == EEPROM) {
        std::cout << "Read eeprom " << size << " bytes" << std::endl;
        return programmer.readEeprom(size);
    } else {
        std::cout << "Read memory " << size << " bytes" << std::endl;
        return programmer.readMemory(size);
    }
}

int writeMem(AvrProgrammer& programmer, const std::vector<uint8_t>& data, avr_mem_t mem, size_t size) {
    if (mem == LOCK) {
        std::cout << "Write lock" << std::endl;
        return programmer.writeLock(data[0]);
    } else if (mem == FUSE) {
        std::cout << "Write fuse " << data.size() << " bytes" << std::endl;
        uint32_t fuse = 0;
        std::copy(data.cbegin(), data.cend(), &fuse);
        return programmer.writeFuse(fuse, data.size());
    } else if (mem == EEPROM) {
        std::cout << "Write eeprom " << data.size() << " bytes" << std::endl;
        return programmer.writeEeprom(data);
    } else {
        std::cout << "Erase chip" << std::endl;
        programmer.erase();
        std::cout << "Reset" << std::endl;
        programmer.reset();
        std::cout << "Write memory " << data.size() << " bytes" << std::endl;
        return programmer.writeMemory(data);
    }
}
