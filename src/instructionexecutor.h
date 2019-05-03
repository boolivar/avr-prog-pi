#ifndef INSTRUCTIONEXECUTOR_H
#define INSTRUCTIONEXECUTOR_H

#include <functional>

class Instruction;
class InstructionFactory;
class SerialController;

class InstructionExecutor {
public:
    Instruction exchange(const std::function<Instruction(const InstructionFactory&)>& factoryOperation);

    InstructionExecutor(const InstructionFactory& instructionFactory, SerialController& controller);

private:
    const InstructionFactory& instructionFactory;
    SerialController& controller;
};

#endif // INSTRUCTIONEXECUTOR_H
