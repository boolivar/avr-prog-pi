#ifndef INTELHEXFILEREADER_H
#define INTELHEXFILEREADER_H

#include "dataformat.h"

class IntelHexFileReader : public DataFormat {
public:
    virtual std::vector<uint8_t> read(std::istream& in);
    virtual int write(const std::vector<uint8_t>& data, std::ostream& out);

    IntelHexFileReader(uint8_t fillValue = 0xff);

private:
    uint8_t fillValue;
};

#endif // INTELHEXFILEREADER_H
