#include "TypeChecker.h"
#include <iostream>

void TypeChecker::visitDeclaration(Declaration *p) {
    if (dynamic_cast<FunctionDefType *>(p->typereference_) || dynamic_cast<FunctionDeclType *>(p->typereference_)) {
        funcNames.push(p->ident_);
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

    funcTypes.pop();
    funcNames.pop();
}

void TypeChecker::visitFunctionDeclaration(FunctionDeclaration *p) {
    auto *range = p->funcrange_;
    auto *domain = p->funcdomain_;

    funcTypes.push(new SgFunctionType({}, visit(domain)));
    range->accept(this);

    std::cout << "At function " << funcNames.top() << ":" << std::endl;
    printType(funcNames.top(), funcTypes.top());
    std::cout << "------" << std::endl;

    returnValue(funcTypes.top());
}

void TypeChecker::visitFunctionDefinition(FunctionDefinition *p) {
    auto *range = p->funcrangenamed_;
    auto *domain = p->funcdomain_;

    symbolTable.pushLayer();
    symbolTable.putAtCurrentLayer(funcNames.top(), nullptr);

    funcTypes.push(new SgFunctionType({}, visit(domain)));
    range->accept(this);

    symbolTable[funcNames.top()] = funcTypes.top();

    p->body__->accept(this);

    size_t i = 0;
    for (auto *&var : funcTypes.top()->range) {
        if (auto *undecided = dynamic_cast<SgAutoType *>(var)) {
            var = undecided->decide();
            ++i;

            if (!var) {
                error("Variable at position " + std::to_string(i) + " can not be inferred in function " +
                          funcNames.top(),
                      p);
            }
        }
    }

    if (auto *undecided = dynamic_cast<SgAutoType *>(funcTypes.top()->domain)) {
        funcTypes.top()->domain = undecided->decide();

        if (!funcTypes.top()->domain) {
            error("Return type can not be inferred in function " + funcNames.top(), p);
        }
    }

    returnValue(funcTypes.top());

    std::cout << "At function " << funcNames.top() << ":" << std::endl;
    symbolTable.forEach(printType);
    std::cout << "------" << std::endl;

    symbolTable.popLayer();
}

void TypeChecker::visitFunctionDomain(FunctionDomain *p) { returnValue(visit(p->typereference_)); }

void TypeChecker::visitFunctionRangeSingle(FunctionRangeSingle *p) {
    auto *type = visit(p->typereference_);

    if (!type->equals(NOTHING_TYPE)) {
        funcTypes.top()->addRangeType(type);
    }
}

void TypeChecker::visitFunctionRangeMultiple(FunctionRangeMultiple *p) {
    funcTypes.top()->addRangeType(visit(p->typereference_));
    for (auto *ref : *p->listtypereference_) {
        funcTypes.top()->addRangeType(visit(ref));
    }
}

void TypeChecker::visitFunctionParameter(FunctionParameter *p) {
    if (symbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error in function declaration: variable " + p->ident_ + " is already defined", p);
    }

    auto *type = visit(p->typereference_);
    symbolTable.putAtCurrentLayer(p->ident_, type);
    returnValue(type);
}

void TypeChecker::visitFunctionRangeSingleNamed(FunctionRangeSingleNamed *p) {
    funcTypes.top()->addRangeType(visit(p->funcparam_));
}

void TypeChecker::visitFunctionRangeMultipleNamed(FunctionRangeMultipleNamed *p) {
    for (auto *ref : *p->listfuncparam_) {
        funcTypes.top()->addRangeType(visit(ref));
    }
}

void TypeChecker::visitFunctionDeclType(FunctionDeclType *p) { returnValue(visit(p->funcdecl_)); }

void TypeChecker::visitFunctionDefType(FunctionDefType *p) { returnValue(visit(p->funcdefn_)); }
