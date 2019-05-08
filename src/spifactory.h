#ifndef SPIFACTORY_H
#define SPIFACTORY_H

#include <memory>

class ChipSelect;
class Spi;

class SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi(uint8_t index = 0) = 0;
    virtual std::unique_ptr<ChipSelect> createChipSelect(uint8_t pin = 25) = 0;

    virtual ~SpiFactory();
};

#endif // SPIFACTORY_H
