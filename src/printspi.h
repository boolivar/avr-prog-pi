#ifndef PRINTSPI_H
#define PRINTSPI_H

#include "spi.h"

class PrintSpi : public Spi {
public:
    virtual err_t chipSelect(uint8_t level);
    virtual err_t setMode(uint8_t mode);
    virtual err_t setSpeedHz(uint32_t hz);
    virtual err_t transfer(uint8_t* buf, uint32_t len);
    virtual err_t wait(uint32_t ms);

    PrintSpi(uint8_t index, uint8_t csPin);
    virtual ~PrintSpi();
};

#endif // PRINTSPI_H
