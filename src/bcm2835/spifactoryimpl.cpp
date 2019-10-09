#include "spifactoryimpl.h"

#include "bcm2835chipselect.h"
#include "bcm2835spi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi(uint8_t index, uint8_t csPin) {
    return std::make_unique<Bcm2835Spi>(csPin);
}
