#include "TypeChecker.h"
#include <iostream>

TypeChecker::~TypeChecker() = default;

void TypeChecker::visitProgram_(Program_ *p) { p->accept(this); }

void TypeChecker::visitProgram(Program *p) {
    for (auto *statement : *(p->listdecl_)) {
        statement->accept(this);
    }
}

StingrayType *TypeChecker::stackPop() {
    StingrayType *value = returnedTypes.top();
    returnedTypes.pop();
    return value;
}

void TypeChecker::returnValue(StingrayType *v) { returnedTypes.push(v); }
void TypeChecker::returnValue(EBaseType baseType) { returnedTypes.push(new SgBaseType(baseType)); }

StingrayType *TypeChecker::visit(Visitable *v) {
    v->accept(this);
    return stackPop();
}

void TypeChecker::error(const std::string &error) {
    std::cerr << error << std::endl;
    exit(1);
}
void TypeChecker::printType(const std::string &variableName, const StingrayType *type) {
    std::cout << "Variable " << variableName << " is of type " << type->toString() << std::endl;
}

