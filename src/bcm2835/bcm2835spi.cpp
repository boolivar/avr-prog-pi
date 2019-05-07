#include "bcm2835spi.h"

#include <bcm2835.h>

err_t Bcm2835Spi::setMode(uint8_t mode) {
    if (bcm->isValid()) {
        bcm2835_spi_setDataMode(mode);
    }
    return 0;
}

err_t Bcm2835Spi::setSpeedHz(uint32_t hz) {
    if (bcm->isValid()) {
        bcm2835_spi_set_speed_hz(hz);
    }
    return 0;
}

err_t Bcm2835Spi::transfer(uint8_t* buf, uint32_t len) {
    if (bcm->isValid()) {
        bcm2835_spi_transfern(reinterpret_cast<char*>(buf), len);
    }
    return 0;
}

Bcm2835Spi::Bcm2835Spi(const std::shared_ptr<Bcm2835Allocator>& bcm)
    : bcm(bcm) {
    if (bcm->isValid()) {
        bcm2835_spi_begin();
    }
}

Bcm2835Spi::~Bcm2835Spi() {
    if (bcm->isValid()) {
        bcm2835_spi_end();
    }
}