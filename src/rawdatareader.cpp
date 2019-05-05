#include "rawdatareader.h"

#include <algorithm>
#include <iterator>

std::vector<uint8_t> RawDataReader::readData(std::istream& in) {
    std::vector<uint8_t> data;
    std::copy(std::istream_iterator<uint8_t>(in), std::istream_iterator<uint8_t>(), std::back_inserter(data));
    return data;
}
