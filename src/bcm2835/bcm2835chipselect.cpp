#include "bcm2835chipselect.h"

#include <bcm2835.h>

void Bcm2835ChipSelect::enable() {
    bcm2835_gpio_write(pin, level);
}

void Bcm2835ChipSelect::disable() {
    bcm2835_gpio_write(pin, !level);
}

Bcm2835ChipSelect::Bcm2835ChipSelect(uint8_t pin, uint8_t level)
    : pin(pin), level(level) {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    disable();
}

Bcm2835ChipSelect::~Bcm2835ChipSelect() {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
}
