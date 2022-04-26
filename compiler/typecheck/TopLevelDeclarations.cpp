#include "TypeChecker.h"

void TypeChecker::visitDeclaration(Declaration *p) {
    if (dynamic_cast<FunctionDefType *>(p->typereference_)) {
        currentFunctionName = p->ident_;
    }

    if (symbolTable.contains(p->ident_)) {
        auto *type = visit(p->typereference_);

        if (!type->coercesTo(symbolTable[p->ident_])) {
            error("Redeclaration of " + p->ident_ + " failed. Expected type to be convertible to " +
                  symbolTable[p->ident_]->toString() + " but got: " + type->toString());
        }
    } else {
        auto *type = visit(p->typereference_);
        symbolTable[p->ident_] = type;
    }
}

void TypeChecker::visitFunctionDeclaration(FunctionDeclaration *p) {
    auto *range = p->funcrange_;
    auto *domain = p->funcdomain_;

    currentFunctionType = new SgFunctionType({}, visit(domain));
    range->accept(this);

    symbolTable[currentFunctionName] = currentFunctionType;
    returnValue(currentFunctionType);

    printType(currentFunctionName, currentFunctionType);

    currentFunctionName = "";
    currentFunctionType = nullptr;
}

void TypeChecker::visitFunctionDefinition(FunctionDefinition *p) {
    auto *range = p->funcrangenamed_;
    auto *domain = p->funcdomain_;

    symbolTable[currentFunctionName] = nullptr;

    currentFunctionType = new SgFunctionType({}, visit(domain));
    range->accept(this);

    symbolTable[currentFunctionName] = currentFunctionType;
    returnValue(currentFunctionType);

    printType(currentFunctionName, currentFunctionType);

    currentFunctionName = "";
    currentFunctionType = nullptr;

    p->body__->accept(this);
}

void TypeChecker::visitFunctionDomain(FunctionDomain *p) { returnValue(visit(p->typereference_)); }

void TypeChecker::visitFunctionRangeSingle(FunctionRangeSingle *p) {
    currentFunctionType->addRangeType(visit(p->typereference_));
}

void TypeChecker::visitFunctionRangeMultiple(FunctionRangeMultiple *p) {
    currentFunctionType->addRangeType(visit(p->typereference_));
    for (auto *ref : *p->listtypereference_) {
        currentFunctionType->addRangeType(visit(ref));
    }
}

void TypeChecker::visitFunctionParameter(FunctionParameter *p) {
    auto *type = visit(p->typereference_);
    symbolTable[p->ident_] = type;
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

void TypeChecker::visitFunctionDeclType(FunctionDeclType *p) { visit(p->funcdecl_); }

void TypeChecker::visitFunctionDefType(FunctionDefType *p) { visit(p->funcdefn_); }
