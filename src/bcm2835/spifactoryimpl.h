#ifndef SPIFACTORYIMPL_H
#define SPIFACTORYIMPL_H

#include "bcm2835allocator.h"
#include "spifactory.h"

class SpiFactoryImpl : public SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi();
    virtual std::unique_ptr<ChipSelect> createChipSelect();

private:
    std::weak_ptr<Bcm2835Allocator> bcm;
};

#endif // SPIFACTORYIMPL_H
