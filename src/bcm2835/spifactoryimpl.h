#ifndef SPIFACTORYIMPL_H
#define SPIFACTORYIMPL_H

#include "bcm2835allocator.h"
#include "spifactory.h"

class SpiFactoryImpl : public SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi(uint8_t index);
    virtual std::unique_ptr<ChipSelect> createChipSelect(uint8_t pin);

private:
    std::weak_ptr<Bcm2835Allocator> bcm;

    std::shared_ptr<Bcm2835Allocator> lockBcm();
};

#endif // SPIFACTORYIMPL_H
