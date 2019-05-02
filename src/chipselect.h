#ifndef CHIPSELECT_H
#define CHIPSELECT_H

class ChipSelect {
public:
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual ~ChipSelect();
};

#endif // CHIPSELECT_H
