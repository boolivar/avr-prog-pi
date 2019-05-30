#include "rawdatareader.h"

#include <iterator>

std::vector<uint8_t> RawDataReader::readData(std::istream& in) {
    return std::vector<uint8_t>(std::istream_iterator<uint8_t>(in), std::istream_iterator<uint8_t>());
}
