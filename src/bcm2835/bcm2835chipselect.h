#ifndef BCM2835CHIPSELECT_H
#define BCM2835CHIPSELECT_H

#include "chipselect.h"

#include <cinttypes>

class Bcm2835ChipSelect : public ChipSelect {
public:
    virtual void enable();
    virtual void disable();

    Bcm2835ChipSelect(uint8_t pin, uint8_t level);
    virtual ~Bcm2835ChipSelect();

private:
    uint8_t pin;
    uint8_t level;
};

#endif // BCM2835CHIPSELECT_H
