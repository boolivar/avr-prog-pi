#ifndef INSTRUCTIONEXECUTOR_H
#define INSTRUCTIONEXECUTOR_H

#include "instructionfactory.h"

#include <functional>

class Instruction;
class InstructionFactory;
class OutputController;

class InstructionExecutor {
public:
    Instruction exchange(const std::function<Instruction(const InstructionFactory&)>& factoryOperation);

    InstructionExecutor(OutputController& controller);

private:
    OutputController& controller;
};

#endif // INSTRUCTIONEXECUTOR_H
