#ifndef SPIFACTORYIMPL_H
#define SPIFACTORYIMPL_H

#include "spifactory.h"

class SpiFactoryImpl : public SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi(uint8_t index);
    virtual std::unique_ptr<ChipSelect> createChipSelect(uint8_t pin);
};

#endif // SPIFACTORYIMPL_H
