#ifndef SPI_H
#define SPI_H

#include <cstdint>

typedef int err_t;

class Spi {
public:
    virtual err_t setMode(uint8_t mode) = 0;
    virtual err_t setSpeedHz(uint32_t hz) = 0;
    virtual err_t transfer(uint8_t *buf, uint32_t len) = 0;

    virtual ~Spi() {}
};

#endif // SPI_H
