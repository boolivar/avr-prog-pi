#ifndef SPIFACTORY_H
#define SPIFACTORY_H

#include <memory>

class Spi;

class SpiFactory {
public:
    virtual std::unique_ptr<Spi> createSpi(uint8_t index, uint8_t csPin) = 0;
    virtual ~SpiFactory();
};

#endif // SPIFACTORY_H
