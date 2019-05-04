#ifndef INSTRUCTIONEXECUTOR_H
#define INSTRUCTIONEXECUTOR_H

#include "instructionfactory.h"

#include <functional>

class Instruction;
class InstructionFactory;
class SerialController;

class InstructionExecutor {
public:
    Instruction exchange(const std::function<Instruction(const InstructionFactory&)>& factoryOperation);

    InstructionExecutor(SerialController& controller);

private:
    const InstructionFactory instructionFactory;
    SerialController& controller;
};

#endif // INSTRUCTIONEXECUTOR_H
