#include "hexfilereader.h"

#include "IntelHexFileEntry.h"

#include <algorithm>
#include <list>

std::vector<uint8_t> HexFileReader::readData(std::istream& in) {
    std::list<IntelHexFileEntry> entries;
    while (in.good()) {
        std::string line;
        std::getline(in, line);
        IntelHexFileEntry entry(line);
        if ((entry.getRecordType() != 0x0) && (entry.getRecordType() != 0x1)) {
            stringstream o;
            o << "Unsupported record type: 0x";
            o << hex << static_cast<uint32_t>(entry.getRecordType());
            throw ios_base::failure(o.str());
        }
        entries.push_back(entry);
    }
    if (!in.eof()) {
        throw ios_base::failure("Error reading hex stream");
    }

    std::vector<uint8_t> data(entries.rbegin()->getEndAddress(), fillValue);
    for (std::list<IntelHexFileEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        std::vector<uint8_t> block = it->getData();
        std::copy(block.cbegin(), block.cend(), data.begin() + it->getAddress());
    }
    return data;
}

HexFileReader::HexFileReader(const std::string& fileName, uint8_t fillValue)
    : fileName(fileName), fillValue(fillValue) {
}
