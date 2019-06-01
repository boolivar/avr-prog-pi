#ifndef INTELHEXFILEREADER_H
#define INTELHEXFILEREADER_H

#include <datareader.h>

class IntelHexFileReader : public DataReader {
public:
    virtual std::vector<uint8_t> readData(std::istream& in);
    virtual int writeData(const std::vector<uint8_t>& data, std::ostream& out);

    IntelHexFileReader(uint8_t fillValue = 0xff);

private:
    uint8_t fillValue;
};

#endif // INTELHEXFILEREADER_H
