#ifndef HEXFILEREADER_H
#define HEXFILEREADER_H

#include "datareader.h"

#include <string>
#include <cstdint>

class HexFileReader : public DataReader {
public:
    virtual std::vector<uint8_t> readData(std::istream& in);

    HexFileReader(uint8_t fillValue = 0xff);

private:
    uint8_t fillValue;
};

#endif // HEXFILEREADER_H
