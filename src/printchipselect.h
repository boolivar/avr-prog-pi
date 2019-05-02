#ifndef PRINTCHIPSELECT_H
#define PRINTCHIPSELECT_H

#include "chipselect.h"

class PrintChipSelect: public ChipSelect {
public:
    virtual void enable();
    virtual void disable();
};

#endif // PRINTCHIPSELECT_H
