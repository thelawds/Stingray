
#include "TypeChecker.h"

void TypeChecker::visitTrueTerm(TrueTerm *p) { returnValue(new SgBaseType(EBaseType::BOOLEAN)); }

void TypeChecker::visitFalseTerm(FalseTerm *p) { returnValue(new SgBaseType(EBaseType::BOOLEAN)); }

void TypeChecker::visitEmptyTerm(EmptyTerm *p) { returnValue(new SgBaseType(EBaseType::UNTYPED)); }

void TypeChecker::visitStringTerm(StringTerm *p) { returnValue(new SgBaseType(EBaseType::STRING)); }

void TypeChecker::visitIntegerTerm(IntegerTerm *p) { returnValue(new SgBaseType(EBaseType::INTEGER)); }

void TypeChecker::visitDoubleTerm(DoubleTerm *p) { returnValue(new SgBaseType(EBaseType::DOUBLE)); }

void TypeChecker::visitVariableReferenceTerm(VariableReferenceTerm *p) {
    if (symbolTable.contains(p->ident_)) {
        returnValue(symbolTable[p->ident_]);
    } else {
        error("Variable " + p->ident_ + " is not declared, but referenced", p);
    }
}

void TypeChecker::visitUserType(UserType *p) {
    if (symbolTable.contains(p->ident_)) {
        returnValue(symbolTable[p->ident_]);
    }else {
        error("User-defined type " + p->ident_ + " is not declared", p);
    }
}

void TypeChecker::visitNothingType(NothingType *p) { returnValue(new SgBaseType(EBaseType::NOTHING)); }

void TypeChecker::visitBoolType(BoolType *p) { returnValue(new SgBaseType(EBaseType::BOOLEAN)); }

void TypeChecker::visitIntegerType(IntegerType *p) { returnValue(new SgBaseType(EBaseType::INTEGER)); }

void TypeChecker::visitDoubleType(DoubleType *p) { returnValue(new SgBaseType(EBaseType::DOUBLE)); }

void TypeChecker::visitStringType(StringType *p) { returnValue(new SgBaseType(EBaseType::STRING)); }

void TypeChecker::visitArrayType(ArrayType *p) {
    auto *parentType = visit(p->typereference_);
    returnValue(new SgArrayType(parentType));
}
