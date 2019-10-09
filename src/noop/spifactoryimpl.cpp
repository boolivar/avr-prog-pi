#include "spifactoryimpl.h"

#include "printspi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi(uint8_t index, uint8_t csPin) {
    return std::make_unique<PrintSpi>(index, csPin);
}
