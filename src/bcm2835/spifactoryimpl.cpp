#include "spifactoryimpl.h"

#include "bcm2835chipselect.h"
#include "bcm2835spi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi() {
    std::shared_ptr<Bcm2835Allocator> bcmLock = bcm.lock();
    if (bcmLock->isValid()) {
        return std::make_unique<Bcm2835Spi>(bcmLock);
    }
    return std::make_unique<Bcm2835Spi>();
}

std::unique_ptr<ChipSelect> SpiFactoryImpl::createChipSelect() {
    std::shared_ptr<Bcm2835Allocator> bcmLock = bcm.lock();
    if (bcmLock->isValid()) {
        return std::make_unique<Bcm2835ChipSelect>(bcmLock);
    }
    return std::make_unique<Bcm2835ChipSelect>();
}
