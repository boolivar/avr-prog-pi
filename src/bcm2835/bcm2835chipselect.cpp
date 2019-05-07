#include "bcm2835chipselect.h"

#include <bcm2835.h>

void Bcm2835ChipSelect::enable() {
    setLevel(level, delayMs);
}

void Bcm2835ChipSelect::disable() {
    setLevel(!level, delayMs);
}

Bcm2835ChipSelect::Bcm2835ChipSelect(const std::shared_ptr<Bcm2835Allocator>& bcm, uint8_t pin, uint32_t delayMs, uint8_t level)
    : bcm(bcm), pin(pin), level(level), delayMs(delayMs) {
    if (bcm->isValid()) {
        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
        setLevel(!level, 0);
    }
}

Bcm2835ChipSelect::~Bcm2835ChipSelect() {
    if (bcm->isValid()) {
        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    }
}

void Bcm2835ChipSelect::setLevel(uint8_t value, uint32_t delay) {
    if (bcm->isValid()) {
        bcm2835_gpio_write(pin, value ? HIGH : LOW);
        if (delay > 0) {
            bcm2835_delay(delay);
        }
    }
}
