#include "spi.h"
#include "printspi.h"
#include "instruction.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

int main() {
    unique_ptr<Spi> spi(new PrintSpi);

    char buf[10];

    sprintf(buf, "hello");

    spi->transfer(reinterpret_cast<unsigned char*>(buf), 10);

    Instruction ins(1, 2, 3, 4);

    cout << "ins.size: "  << Instruction::size << endl;
    cout << "ins.value: "  << ins.getValue() << endl;
    cout << "ins.bytes: ";
    memcpy(buf, ins.getBytes(), 4);
    spi->transfer(reinterpret_cast<unsigned char*>(buf), 4);

    return 0;
}
