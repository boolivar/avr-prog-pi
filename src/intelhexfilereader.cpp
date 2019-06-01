#include "intelhexfilereader.h"

#include <intelhex.h>

#include <algorithm>

std::vector<uint8_t> IntelHexFileReader::readData(std::istream& in) {
    intelhex::hex_data hexData;

    hexData.read(in);

    std::vector<uint8_t> data(hexData.max_address() + 1, fillValue);
    for (intelhex::hex_data::iterator it = hexData.begin(); it != hexData.end(); ++it) {
        const std::vector<uint8_t>& block = it->second;
        std::copy(block.cbegin(), block.cend(), data.begin() + it->first);
    }
    return data;
}

int IntelHexFileReader::writeData(const std::vector<uint8_t>& data, std::ostream& out) {
    intelhex::hex_data hexData;
    std::copy(data.cbegin(), data.cend(), hexData.begin()->second.begin());
    hexData.write(out);
    return 0;
}

IntelHexFileReader::IntelHexFileReader(uint8_t fillValue)
    : fillValue(fillValue) {
}
