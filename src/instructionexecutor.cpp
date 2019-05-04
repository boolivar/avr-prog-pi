#include "instructionexecutor.h"

#include "instruction.h"
#include "instructionfactory.h"
#include "outputcontroller.h"

const InstructionFactory instructionFactory;

Instruction InstructionExecutor::exchange(const std::function<Instruction(const InstructionFactory&)>& factoryOperation) {
    Instruction instruction = factoryOperation(instructionFactory);
    return controller.send(instruction);
}

InstructionExecutor::InstructionExecutor(OutputController& controller)
    : controller(controller) {
}
