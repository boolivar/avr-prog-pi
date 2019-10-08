#include "options.h"

#include <exception>
#include <getopt.h>

static std::string makeOptsString();
static std::string defaultIfAbsent(const std::unordered_map<std::string, std::string>& properties, const std::string& key, const std::string& fallback);
static uint32_t parseClock(const std::string& s);
static avr_mem_t parseMemory(const std::string& s);
static file_format_t parseFormat(const std::string& s);
static uint32_t parseMemSize(const std::string& s);

static struct option options[] = {
    {"clock", required_argument, nullptr, 'c'},
    {"format", required_argument, nullptr, 'f'},
    {"memory", required_argument, nullptr, 'm'},
    {"page", required_argument, nullptr, 'p'},
    {"reset", required_argument, nullptr, 'r'},
    {"size", required_argument, nullptr, 's'},
    {"verbose", no_argument, nullptr, 'v'},
    {"write", no_argument, nullptr, 'w'},
    {nullptr, 0, nullptr, 0}
};

std::unordered_map<std::string, std::string> properties(int argc, char** argv) {
    std::unordered_map<std::string, std::string> props;
    int opt;
    int option_index;
    std::string opts = makeOptsString();
    while ((opt = getopt_long(argc, argv, opts.c_str(), options, &option_index)) != -1) {
        props.emplace(std::string(1, static_cast<char>(opt)), optarg != nullptr ? optarg : "true");
    }
    if (optind < argc) {
        if (argc - optind > 1) {
            throw std::invalid_argument("Too many non-option arguments");
        }
        props.emplace("filename", argv[optind]);
    }
    return props;
}

std::string makeOptsString() {
    std::string opts;
    for (int i = 0; options[i].name != nullptr; ++i) {
        opts += static_cast<char>(options[i].val);
        if (options[i].has_arg != no_argument) {
            opts += ":";
        }
    }
    return opts;
}

Config config(const std::unordered_map<std::string, std::string>& properties) {
    std::string clock = defaultIfAbsent(properties, "c", "1");
    std::string format = defaultIfAbsent(properties, "f", "bin");
    std::string mem = defaultIfAbsent(properties, "m", "flash");
    std::string page = defaultIfAbsent(properties, "p", "64");
    std::string reset = defaultIfAbsent(properties, "r", "25");
    std::string size = defaultIfAbsent(properties, "s", "32K");
    std::string verbose = defaultIfAbsent(properties, "v", "false");
    std::string write = defaultIfAbsent(properties, "w", "false");
    std::string fileName = defaultIfAbsent(properties, "filename", "out." + format);
    return Config(static_cast<uint8_t>(std::stoi(reset)), parseClock(clock), parseMemSize(size), std::stoul(page), parseMemory(mem), parseFormat(format), verbose == "true", write == "true", fileName);
}

std::string defaultIfAbsent(const std::unordered_map<std::string, std::string>& properties, const std::string& key, const std::string& fallback) {
    std::unordered_map<std::string, std::string>::const_iterator it = properties.find(key);
    return it != properties.end() ? it->second : fallback;
}

uint32_t parseClock(const std::string& s) {
    size_t idx;
    uint32_t value = std::stoul(s, &idx);

    if (idx == s.length()) {
        return value * 1000000L;
    }

    std::string suffix = s.substr(idx);

    if (suffix == "K" || suffix == "KHz") {
        return value * 1000L;
    }

    if (suffix == "M" || suffix == "MHz") {
        return value * 1000000L;
    }

    throw std::invalid_argument("Invalid freq param: " + s + ", supported units: [KHz, MHz]");
}

avr_mem_t parseMemory(const std::string& s) {
    if (s == "eeprom") {
        return EEPROM;
    }
    if (s == "fuse") {
        return FUSE;
    }
    if (s == "lock") {
        return LOCK;
    }
    return FLASH;
}

file_format_t parseFormat(const std::string& s) {
    if (s == "hex") {
        return HEX;
    }
    if (s == "bin") {
        return BIN;
    }
    throw std::invalid_argument("Invalid file format: " + s + ", supported: [hex, bin]");
}

uint32_t parseMemSize(const std::string& s) {
    size_t idx;
    uint32_t value = std::stoul(s, &idx);

    if (idx == s.length()) {
        return value;
    }

    if ((idx == s.length() - 1) && (s.back() == 'K' || s.back() == 'k')) {
        return value * 1024;
    }

    throw std::invalid_argument("Invalid mem size param " + s);
}
