#include "TypeChecker.h"

void TypeChecker::visitDeclaration(Declaration *p) {
    if (dynamic_cast<FunctionDefType *>(p->typereference_) || dynamic_cast<FunctionDeclType *>(p->typereference_)) {
        currentFunctionName = p->ident_;
    } else if (dynamic_cast<ClassType *>(p->typereference_)) {
        currentClassName = p->ident_;
    }

    if (symbolTable.contains(p->ident_)) {
        auto *existingType = symbolTable[p->ident_];
        auto *type = visit(p->typereference_);

        if (!type->coercesTo(existingType)) {
            error("Redeclaration of " + p->ident_ + " failed. Expected type to be convertible to " +
                      symbolTable[p->ident_]->toString() + " but got: " + type->toString(),
                  p);
        }
    } else {
        auto *type = visit(p->typereference_);
        symbolTable.putAtCurrentLayer(p->ident_, type);
    }

    currentFunctionType = nullptr;
    currentFunctionName = "";
}

void TypeChecker::visitFunctionDeclaration(FunctionDeclaration *p) {
    auto *range = p->funcrange_;
    auto *domain = p->funcdomain_;

    currentFunctionType = new SgFunctionType({}, visit(domain));
    range->accept(this);

    returnValue(currentFunctionType);
    printType(currentFunctionName, currentFunctionType);
}

void TypeChecker::visitFunctionDefinition(FunctionDefinition *p) {
    auto *range = p->funcrangenamed_;
    auto *domain = p->funcdomain_;

    symbolTable.pushLayer();
    symbolTable.putAtCurrentLayer(currentFunctionName, nullptr);

    currentFunctionType = new SgFunctionType({}, visit(domain));
    range->accept(this);

    symbolTable[currentFunctionName] = currentFunctionType;
    returnValue(currentFunctionType);

    printType(currentFunctionName, currentFunctionType);

    p->body__->accept(this);
    symbolTable.popLayer();
}

void TypeChecker::visitFunctionDomain(FunctionDomain *p) { returnValue(visit(p->typereference_)); }

void TypeChecker::visitFunctionRangeSingle(FunctionRangeSingle *p) {
    auto *type = visit(p->typereference_);

    if (!type->equals(NOTHING_TYPE)) {
        currentFunctionType->addRangeType(type);
    }
}

void TypeChecker::visitFunctionRangeMultiple(FunctionRangeMultiple *p) {
    currentFunctionType->addRangeType(visit(p->typereference_));
    for (auto *ref : *p->listtypereference_) {
        currentFunctionType->addRangeType(visit(ref));
    }
}

void TypeChecker::visitFunctionParameter(FunctionParameter *p) {
    if (symbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error in function declaration: variable " + p->ident_ + " is already defined", p);
    }

    auto *type = visit(p->typereference_);
    symbolTable.putAtCurrentLayer(p->ident_, type);
    printType(p->ident_, type);
    returnValue(type);
}

void TypeChecker::visitFunctionRangeSingleNamed(FunctionRangeSingleNamed *p) {
    currentFunctionType->addRangeType(visit(p->funcparam_));
}

void TypeChecker::visitFunctionRangeMultipleNamed(FunctionRangeMultipleNamed *p) {
    for (auto *ref : *p->listfuncparam_) {
        currentFunctionType->addRangeType(visit(ref));
    }
}

void TypeChecker::visitFunctionDeclType(FunctionDeclType *p) { returnValue(visit(p->funcdecl_)); }

void TypeChecker::visitFunctionDefType(FunctionDefType *p) { returnValue(visit(p->funcdefn_)); }
