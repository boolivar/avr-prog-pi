#include "instructionexecutor.h"

#include "instruction.h"
#include "instructionfactory.h"
#include "serialcontroller.h"

Instruction InstructionExecutor::exchange(const std::function<Instruction(const InstructionFactory&)>& factoryOperation) {
    Instruction instruction = factoryOperation(instructionFactory);
    return controller.send(instruction);
}

InstructionExecutor::InstructionExecutor(SerialController& controller)
    : controller(controller) {
}
