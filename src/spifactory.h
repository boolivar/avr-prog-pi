#ifndef SPIFACTORY_H
#define SPIFACTORY_H

#include <memory>

class ChipSelect;
class Spi;

class SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi() = 0;
    virtual std::unique_ptr<ChipSelect> createChipSelect() = 0;

    virtual ~SpiFactory();
};

#endif // SPIFACTORY_H
