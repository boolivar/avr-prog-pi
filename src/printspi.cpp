#include "printspi.h"

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

err_t PrintSpi::chipSelect(uint8_t level) {
    cout << "spi chip select: " << level << endl;
    return 0;
}

err_t PrintSpi::setMode(uint8_t mode) {
    cout << "spi set mode: " << mode << endl;
    return 0;
}

err_t PrintSpi::setSpeedHz(uint32_t hz) {
    cout << "spi set speed: " << hz << endl;
    return 0;
}

err_t PrintSpi::transfer(uint8_t *buf, uint32_t len) {
    cout << "spi transfer " << len << ": ";
    ostream hexcout(cout.rdbuf());
    hexcout << hex << showbase;
    copy(buf, buf + len, ostream_iterator<int>(hexcout, " "));
    cout << endl;
    return 0;
}

PrintSpi::PrintSpi(uint8_t index, uint8_t csPin) {
    cout << "spi " << index << " init, csPin " << csPin << endl;
}

PrintSpi::~PrintSpi() {
    cout << "spi destroy" << endl;
}
