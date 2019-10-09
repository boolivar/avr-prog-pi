#include "intelhexfilereader.h"
#include "catch.hpp"

#include <string>
#include <sstream>

using namespace Catch::Matchers;

TEST_CASE("read hex", "[intelhexfilereader]") {
    IntelHexFileReader reader;

    std::string hex(":0B0010006164647265737320676170A7");
    std::istringstream in(hex);
    std::vector<uint8_t> data = reader.read(in);

    CHECK(data.size() == (0x10 + 0x0B));
    REQUIRE_THAT(data, Equals(std::vector<uint8_t>({
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x20, 0x67, 0x61, 0x70 })));
}

TEST_CASE("write hex", "[intelhexfilereader]") {
    std::vector<uint8_t> data({ 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x20, 0x67, 0x61, 0x70 });

    IntelHexFileReader writer;
    std::ostringstream out;
    writer.write(data, out);

    std::ostringstream expected;
    expected << ":0B0000006164647265737320676170B7"
             << std::endl
             << ":00000001FF"
             << std::endl;
    REQUIRE_THAT(out.str(), Equals(expected.str()));
}
