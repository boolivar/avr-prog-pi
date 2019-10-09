#include "rawdatareader.h"

#include <algorithm>
#include <iterator>

std::vector<uint8_t> RawDataReader::read(std::istream& in) {
    return std::vector<uint8_t>(std::istream_iterator<uint8_t>(in), std::istream_iterator<uint8_t>());
}

int RawDataReader::write(const std::vector<uint8_t>& data, std::ostream& out) {
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<uint8_t>(out));
    return data.size();
}
