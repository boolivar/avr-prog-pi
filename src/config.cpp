#include "config.h"

Config::Config(uint8_t cs, uint32_t clock, uint32_t size, uint32_t page, avr_mem_t memory, file_format_t format, bool verbose, bool write, const std::string &fileName)
    : cs(cs), clock(clock), size(size), page(page), memory(memory), format(format), verbose(verbose), write(write), fileName(fileName) {
}

uint8_t Config::getCs() const {
    return cs;
}

uint32_t Config::getClock() const {
    return clock;
}

uint32_t Config::getSize() const {
    return size;
}

uint32_t Config::getPage() const {
    return page;
}

avr_mem_t Config::getMemory() const {
    return memory;
}

file_format_t Config::getFormat() const {
    return format;
}

std::string Config::getFileName() const {
    return fileName;
}

bool Config::isVerbose() const {
    return verbose;
}

bool Config::isWrite() const {
    return write;
}
