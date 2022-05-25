#include "InterpretationVisitor.h"

RuntimeValue *InterpretationVisitor::stackPop() {
    auto *value = returnedValues.top();
    returnedValues.pop();
    return value;
}

void InterpretationVisitor::returnValue(RuntimeValue *v) { returnedValues.push(v); }

RuntimeValue *InterpretationVisitor::visit(Visitable *p) {
    p->accept(this);
    return stackPop();
}

void InterpretationVisitor::visitProgram_(Program_ *p) { p->accept(this); }

void InterpretationVisitor::visitProgram(Program *p) {
    for (auto *statement : *(p->liststatement_)) {
        statement->accept(this);
    }
}