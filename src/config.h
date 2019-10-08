#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

typedef enum {
    LOCK,
    FUSE,
    FLASH,
    EEPROM
} avr_mem_t;

typedef enum {
    BIN,
    HEX
} file_format_t;

class Config {
public:
    Config(uint8_t cs,
        uint32_t clock,
        uint32_t size,
        uint32_t page,
        avr_mem_t memory,
        file_format_t format,
        bool verbose,
        bool write,
        const std::string& fileName);

    uint8_t getCs() const;
    uint32_t getClock() const;
    uint32_t getSize() const;
    uint32_t getPage() const;
    avr_mem_t getMemory() const;
    file_format_t getFormat() const;
    bool isVerbose() const;
    bool isWrite() const;
    std::string getFileName() const;

private:
    uint8_t cs;
    uint32_t clock;
    uint32_t size;
    uint32_t page;
    avr_mem_t memory;
    file_format_t format;
    bool verbose;
    bool write;
    std::string fileName;
};

#endif // CONFIG_H
