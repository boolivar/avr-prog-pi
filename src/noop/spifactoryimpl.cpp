#include "spifactoryimpl.h"

#include "printchipselect.h"
#include "printspi.h"

std::unique_ptr<Spi> SpiFactoryImpl::createSpi() {
    return std::make_unique<PrintSpi>();
}

std::unique_ptr<ChipSelect> SpiFactoryImpl::createChipSelect() {
    return std::make_unique<PrintChipSelect>();
}
