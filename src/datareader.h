#ifndef DATAREADER_H
#define DATAREADER_H

#include <cinttypes>
#include <istream>
#include <vector>

class DataReader {
public:
    virtual std::vector<uint8_t> readData(std::istream& in) = 0;

    virtual ~DataReader();
};

#endif // DATAREADER_H
