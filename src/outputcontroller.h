#ifndef OUTPUTCONTROLLER_H
#define OUTPUTCONTROLLER_H

class Instruction;

class OutputController {
public:
    virtual Instruction send(const Instruction& instruction) = 0;

    virtual ~OutputController() {}
};

#endif // OUTPUTCONTROLLER_H
