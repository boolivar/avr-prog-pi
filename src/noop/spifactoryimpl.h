#ifndef SPIFACTORYIMPL_H
#define SPIFACTORYIMPL_H

#include "spifactory.h"

class SpiFactoryImpl : public SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi();
    virtual std::unique_ptr<ChipSelect> createChipSelect();
};

#endif // SPIFACTORYIMPL_H
