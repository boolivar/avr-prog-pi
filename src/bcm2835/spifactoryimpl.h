#ifndef SPIFACTORYIMPL_H
#define SPIFACTORYIMPL_H

#include "spifactory.h"

class SpiFactoryImpl : public SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi(uint8_t index, uint8_t csPin);
};

#endif // SPIFACTORYIMPL_H
