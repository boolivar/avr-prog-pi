#ifndef RAWDATAREADER_H
#define RAWDATAREADER_H

#include "datareader.h"

class RawDataReader : public DataReader {
public:
    virtual std::vector<uint8_t> readData(std::istream& in);
};

#endif // RAWDATAREADER_H
