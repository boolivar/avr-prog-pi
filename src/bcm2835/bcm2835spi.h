#ifndef BCM2835SPI_H
#define BCM2835SPI_H

#include "spi.h"
#include "bcm2835allocator.h"

#include <memory>

class Bcm2835Spi : public Spi {
public:
    virtual err_t setMode(uint8_t mode);
    virtual err_t setSpeedHz(uint32_t hz);
    virtual err_t transfer(uint8_t *buf, uint32_t len);

    Bcm2835Spi(const std::shared_ptr<Bcm2835Allocator> &bcm);
    virtual ~Bcm2835Spi();

private:
    std::shared_ptr<Bcm2835Allocator> bcm;
};

#endif // BCM2835SPI_H
