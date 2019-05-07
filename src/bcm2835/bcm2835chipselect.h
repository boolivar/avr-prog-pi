#ifndef BCM2835CHIPSELECT_H
#define BCM2835CHIPSELECT_H

#include "chipselect.h"
#include "bcm2835allocator.h"

#include <cinttypes>
#include <memory>

class Bcm2835ChipSelect : public ChipSelect {
public:
    virtual void enable();
    virtual void disable();

    Bcm2835ChipSelect(const std::shared_ptr<Bcm2835Allocator>& bcm, uint8_t pin, uint32_t delayMs = 10, uint8_t level = 1);
    virtual ~Bcm2835ChipSelect();

private:
    std::shared_ptr<Bcm2835Allocator> bcm;
    uint8_t pin;
    uint8_t level;
    uint32_t delayMs;

    void setLevel(uint8_t value, uint32_t delay);
};

#endif // BCM2835CHIPSELECT_H
