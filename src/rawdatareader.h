#ifndef RAWDATAREADER_H
#define RAWDATAREADER_H

#include "dataformat.h"

class RawDataReader : public DataFormat {
public:
    virtual std::vector<uint8_t> read(std::istream& in);
    virtual int write(const std::vector<uint8_t>& data, std::ostream& out);
};

#endif // RAWDATAREADER_H
