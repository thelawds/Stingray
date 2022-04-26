#include "TypeChecker.h"

void TypeChecker::visitStatementVarDecl(StatementVarDecl *p) {
    if (symbolTable.contains(p->ident_)) {
        error("Error at variable definition " + p->ident_ + ". Variable already defined");
    }

    StingrayType *type = visit(p->typereference_);

    if (type->equals(new SgBaseType(EBaseType::NOTHING))) {
        error("Variable can not have type NOTHING");
    }

    symbolTable[p->ident_] = type;

    printType(p->ident_, type);
}

void TypeChecker::visitStatementVarDef(StatementVarDef *p) {
    StingrayType *valueType = visit(p->value_);

    if (symbolTable.contains(p->ident_)) {
        if (!valueType->coercesTo(symbolTable[p->ident_])) {
            error("Error at variable definition " + p->ident_ + ". Variable type and value type are not the same.");
        }
        printType(p->ident_, symbolTable[p->ident_]);
    } else {
        if (valueType->equals(new SgBaseType(EBaseType::UNTYPED))) {
            error("Variable type should be specified, if value is empty");
        }

        symbolTable[p->ident_] = valueType;
        printType(p->ident_, valueType);
    }
}

void TypeChecker::visitStatementVarDefAsc(StatementVarDefAsc *p) {
    StingrayType *valueType = visit(p->value_);
    StingrayType *ascType = visit(p->typereference_);

    if (valueType->coercesTo(ascType)) {
        symbolTable[p->ident_] = ascType;
        printType(p->ident_, ascType);
    } else {
        error("Error at variable definition " + p->ident_ + ". Variable type and value type are not the same.");
    }
}

void TypeChecker::visitValueArrowed(ValueArrowed *p) { returnValue(visit(p->expression_)); }

void TypeChecker::visitValueBraced(ValueBraced *p) { returnValue(visit(p->expression_)); }

void TypeChecker::visitStatementIf(StatementIf *p) { p->statementif__->accept(this); }

void TypeChecker::visitIfStatement(IfStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString());
    }

    p->body__->accept(this);
}

void TypeChecker::visitIfElseIfStatement(IfElseIfStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString());
    }

    p->body__->accept(this);
    p->statementif__->accept(this);
}

void TypeChecker::visitIfElseStatement(IfElseStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString());
    }

    p->body__1->accept(this);
    p->body__2->accept(this);
}

void TypeChecker::visitStatementWhile(StatementWhile *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in while statement should have type boolean, but has: " + exprType->toString());
    }

    p->body__->accept(this);
}

void TypeChecker::visitStatementFor(StatementFor *p) {

    if (symbolTable.contains(p->ident_) && !symbolTable[p->ident_]->equals(new SgBaseType(EBaseType::INTEGER))) {
        error("Variable " + p->ident_ + " is already defined and is not of type Integer. The Type is " +
              symbolTable[p->ident_]->toString());
    }

    symbolTable[p->ident_] = new SgBaseType(EBaseType::INTEGER);
    p->body__->accept(this);
}

void TypeChecker::visitStatementReturnValue(StatementReturnValue *p) { p->expression_->accept(this); }

void TypeChecker::visitBody(Body *p) {
    for (auto *statement : *p->liststatement_) {
        statement->accept(this);
    }
}