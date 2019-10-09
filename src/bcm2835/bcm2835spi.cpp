#include "bcm2835spi.h"

#include <bcm2835.h>

err_t Bcm2835Spi::chipSelect(uint8_t level) {
    if (isValid()) {
        bcm2835_gpio_write(csPin, level ? HIGH : LOW);
        if (delayMs > 0) {
            bcm2835_delay(delayMs);
        }
    }
    return 0;
}

err_t Bcm2835Spi::setMode(uint8_t mode) {
    if (isValid()) {
        bcm2835_spi_setDataMode(mode);
    }
    return 0;
}

err_t Bcm2835Spi::setSpeedHz(uint32_t hz) {
    if (isValid()) {
        bcm2835_spi_set_speed_hz(hz);
    }
    return 0;
}

err_t Bcm2835Spi::transfer(uint8_t* buf, uint32_t len) {
    if (isValid()) {
        bcm2835_spi_transfern(reinterpret_cast<char*>(buf), len);
    }
    return 0;
}

Bcm2835Spi::Bcm2835Spi(uint8_t csPin, uint32_t delayMs)
    : csPin(csPin), delayMs(delayMs), initValue(bcm2835_init()) {
    if (isValid()) {
        bcm2835_spi_begin();
        bcm2835_gpio_fsel(csPin, BCM2835_GPIO_FSEL_OUTP);
    }
}

Bcm2835Spi::~Bcm2835Spi() {
    if (isValid()) {
        bcm2835_gpio_fsel(csPin, BCM2835_GPIO_FSEL_INPT);
        bcm2835_spi_end();
    }
}
