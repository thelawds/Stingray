#include "TypeChecker.h"

void TypeChecker::visitDeclaration(Declaration *p) {
    if (dynamic_cast<FunctionDefType *>(p->typereference_)) {
        currentFunctionName = p->ident_;
    }

    if (newSymbolTable.contains(p->ident_)) {
        auto *existingType = newSymbolTable[p->ident_];
        auto *type = visit(p->typereference_);

        if (!type->coercesTo(existingType)) {
            error("Redeclaration of " + p->ident_ + " failed. Expected type to be convertible to " +
                  newSymbolTable[p->ident_]->toString() + " but got: " + type->toString());
        }
    } else {
        auto *type = visit(p->typereference_);
        newSymbolTable.putAtCurrentLayer(p->ident_, type);
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

    newSymbolTable.pushLayer();
    newSymbolTable.putAtCurrentLayer(currentFunctionName, nullptr);

    currentFunctionType = new SgFunctionType({}, visit(domain));
    range->accept(this);

    newSymbolTable[currentFunctionName] = currentFunctionType;
    returnValue(currentFunctionType);

    printType(currentFunctionName, currentFunctionType);

    p->body__->accept(this);
    newSymbolTable.popLayer();
}

void TypeChecker::visitFunctionDomain(FunctionDomain *p) { returnValue(visit(p->typereference_)); }

void TypeChecker::visitFunctionRangeSingle(FunctionRangeSingle *p) {
    auto *type = visit(p->typereference_);

    if (!type->equals(new SgBaseType(EBaseType::NOTHING))) { // todo
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
    if (newSymbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error in function declaration: variable " + p->ident_ + " is already defined");
    }

    auto *type = visit(p->typereference_);
    newSymbolTable.putAtCurrentLayer(p->ident_, type);
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
