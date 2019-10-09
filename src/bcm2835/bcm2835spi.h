#ifndef BCM2835SPI_H
#define BCM2835SPI_H

#include "spi.h"

class Bcm2835Spi : public Spi {
public:
    bool isValid() { return initValue == 1; }
    int getInitValue() { return initValue; }

    virtual err_t chipSelect(uint8_t level);
    virtual err_t setMode(uint8_t mode);
    virtual err_t setSpeedHz(uint32_t hz);
    virtual err_t transfer(uint8_t *buf, uint32_t len);

    Bcm2835Spi(uint8_t csPin, uint32_t delayMs = 10);
    virtual ~Bcm2835Spi();

private:
    uint8_t csPin;
    uint32_t delayMs;
    int initValue;
};

#endif // BCM2835SPI_H
