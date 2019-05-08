#include "spifactoryimpl.h"

#include "bcm2835chipselect.h"
#include "bcm2835spi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi(uint8_t index) {
    return std::make_unique<Bcm2835Spi>(bcm.lock());
}

std::unique_ptr<ChipSelect> SpiFactoryImpl::createChipSelect(uint8_t pin) {
    return std::make_unique<Bcm2835ChipSelect>(bcm.lock(), pin);
}
