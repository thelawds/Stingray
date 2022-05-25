#include "TypeChecker.h"

void TypeChecker::visitClassDeclaration(ClassDeclaration *p) {
    currentClassType = new SgClassType(currentClassName);
    auto *extends = visit(p->extends_);

    if (extends) {
        currentClassType->parentClass = extends;
    }

    symbolTable.pushLayer();

    p->statics_->accept(this);
    p->cbody_->accept(this);

    symbolTable.popLayer();
    returnValue(currentClassType);
    printType(currentClassType->className, currentClassType);
}

void TypeChecker::visitClassType(ClassType *p) { returnValue(visit(p->classdecl_)); }

void TypeChecker::visitExtendsList(ExtendsList *p) {
    if (symbolTable.contains(p->ident_)) {
        if (symbolTable[p->ident_]->typeCategory == TypeCategory::CLASS) {
            returnValue(symbolTable[p->ident_]);
        } else {
            error(p->ident_ + " is not a class and can not be extended from.", p);
        }
    } else {
        error(p->ident_ + " is not defined", p);
    }
}

void TypeChecker::visitExtendsEmpty(ExtendsEmpty *p) { returnValue(nullptr); }

void TypeChecker::visitStaticsEmpty(StaticsEmpty *p) {
    // pass
}

void TypeChecker::visitStaticsBody(StaticsBody *p) {
    for (auto *fieldDefinition : *p->listfielddef_) {
        auto *type = visit(fieldDefinition);
        auto name = returnedFieldNames.top();
        returnedFieldNames.pop();

        currentClassType->classVariables[name] = type;
        symbolTable.putAtCurrentLayer(name, type);
    }
}

void TypeChecker::visitClassBody(ClassBody *p) {
    for (auto *fieldDefinition : *p->listfielddef_) {
        auto *type = visit(fieldDefinition);
        auto name = returnedFieldNames.top();
        returnedFieldNames.pop();

        currentClassType->objectVariables[name] = type;
        symbolTable.putAtCurrentLayer(name, type);
    }
}

void TypeChecker::visitFieldDeclaration(FieldDeclaration *p) {
    if (dynamic_cast<FunctionDefType *>(p->typereference_) || dynamic_cast<FunctionDeclType *>(p->typereference_)) {
        currentFunctionName = p->ident_;
    }

    if (currentClassType->contains(p->ident_)) {
        error("Class " + currentClassType->className + " already contains field named " + p->ident_, p);
    }

    auto *type = visit(p->typereference_);
    returnedFieldNames.push(p->ident_);
    returnValue(type);
}

void TypeChecker::visitFieldDefinition(FieldDefinition *p) {
    if (currentClassType->contains(p->ident_)) {
        error("Class " + currentClassType->className + " already contains field named " + p->ident_, p);
    }

    auto *type = visit(p->value_);
    returnedFieldNames.push(p->ident_);
    returnValue(type);
}

void TypeChecker::visitFieldDefinitionAsc(FieldDefinitionAsc *p) {
    if (currentClassType->contains(p->ident_)) {
        error("Class " + currentClassType->className + " already contains field named " + p->ident_, p);
    }

    auto *type = visit(p->typereference_);
    returnedFieldNames.push(p->ident_);
    returnValue(type);
}
