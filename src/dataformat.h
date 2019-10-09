#ifndef DATAFORMAT_H
#define DATAFORMAT_H

#include <istream>
#include <ostream>
#include <vector>

class DataFormat {
public:
    virtual std::vector<uint8_t> read(std::istream& in) = 0;
    virtual int write(const std::vector<uint8_t>& data, std::ostream& out) = 0;

    virtual ~DataFormat() {}
};

#endif // DATAFORMAT_H
