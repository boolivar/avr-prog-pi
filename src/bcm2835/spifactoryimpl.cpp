#include "spifactoryimpl.h"

#include "bcm2835chipselect.h"
#include "bcm2835spi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi(uint8_t index) {
    return std::make_unique<Bcm2835Spi>(25);
}

std::unique_ptr<ChipSelect> SpiFactoryImpl::createChipSelect(uint8_t pin) {
    return std::make_unique<Bcm2835ChipSelect>(lockBcm(), pin);
}

std::shared_ptr<Bcm2835Allocator> SpiFactoryImpl::lockBcm() {
    if (bcm.expired()) {
        std::shared_ptr<Bcm2835Allocator> allocator = std::make_shared<Bcm2835Allocator>();
        bcm = allocator;
        return allocator;
    }
    return bcm.lock();
}
