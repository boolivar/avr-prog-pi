#include "spifactoryimpl.h"

#include "printchipselect.h"
#include "printspi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi(uint8_t index) {
    return std::make_unique<PrintSpi>();
}

std::unique_ptr<ChipSelect> SpiFactoryImpl::createChipSelect(uint8_t pin) {
    return std::make_unique<PrintChipSelect>();
}
