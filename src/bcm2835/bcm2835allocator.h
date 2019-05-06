#ifndef BCM2835ALLOCATOR_H
#define BCM2835ALLOCATOR_H

#include <bcm2835.h>

class Bcm2835Allocator {
public:
    bool isValid() { return value == 1; }
    int getValue() { return value; }

    Bcm2835Allocator()
        : value(bcm2835_init()) {}
    ~Bcm2835Allocator() {
        if (isValid()) {
            bcm2835_close();
        }
    }

private:
    int value;
};

#endif // BCM2835ALLOCATOR_H
