#include "TypeChecker.h"

void TypeChecker::visitStatementAssignment(StatementAssignment *p) {

    auto *lhsType = visit(p->expression_);
    auto *rhsType = visit(p->value_);

    if (!rhsType->coercesTo(lhsType)) {
        error("Can not assign value of type " + rhsType->toString() + " to variable of type " +
              lhsType->toString(), p);
    }
}

void TypeChecker::visitStatementVarDecl(StatementVarDecl *p) {
    if (symbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error at variable definition " + p->ident_ + ". Variable already defined", p);
    }

    bool needToPopNames{false};

    if (dynamic_cast<FunctionDefType *>(p->typereference_)) {
        funcNames.push(p->ident_);
        needToPopNames = true;
    }

    StingrayType *type = visit(p->typereference_);

    if (type->equals(new SgBaseType(EBaseType::NOTHING))) {
        error("Variable can not have type NOTHING", p);
    }

    if (needToPopNames) {
        funcNames.pop();
        funcTypes.pop();
    }

    symbolTable.putAtCurrentLayer(p->ident_, type);

}

void TypeChecker::visitStatementVarDef(StatementVarDef *p) {
    if (symbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error at variable definition " + p->ident_ + ". Variable already defined", p);
    }

    StingrayType *valueType = visit(p->value_);
    if (valueType->equals(new SgBaseType(EBaseType::UNTYPED))) {
        error("Variable type should be specified, if value is empty", p);
    }

    symbolTable.putAtCurrentLayer(p->ident_, valueType);
}

void TypeChecker::visitStatementVarDefAsc(StatementVarDefAsc *p) {
    if (symbolTable.containsAtCurrentLayer(p->ident_)) {
        error("Error at variable definition " + p->ident_ + ". Variable already defined", p);
    }

    StingrayType *valueType = visit(p->value_);
    StingrayType *ascType = visit(p->typereference_);

    if (valueType->coercesTo(ascType)) {
        symbolTable.putAtCurrentLayer(p->ident_, ascType);
    } else {
        error("Error at variable definition " + p->ident_ + ". Variable type and value type are not the same.", p);
    }
}

void TypeChecker::visitValueArrowed(ValueArrowed *p) { returnValue(visit(p->expression_)); }

void TypeChecker::visitValueBraced(ValueBraced *p) { returnValue(visit(p->expression_)); }

void TypeChecker::visitStatementIf(StatementIf *p) { p->statementif__->accept(this); }

void TypeChecker::visitIfStatement(IfStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString(), p);
    }

    symbolTable.pushLayer();
    p->body__->accept(this);
    symbolTable.popLayer();
}

void TypeChecker::visitIfElseIfStatement(IfElseIfStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString(),p);
    }

    symbolTable.pushLayer();
    p->body__->accept(this);
    symbolTable.popLayer();

    p->statementif__->accept(this);
}

void TypeChecker::visitIfElseStatement(IfElseStatement *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in if statement should have type boolean, but has: " + exprType->toString(),p);
    }

    symbolTable.pushLayer();
    p->body__1->accept(this);
    symbolTable.popLayer();

    symbolTable.pushLayer();
    p->body__2->accept(this);
    symbolTable.popLayer();
}

void TypeChecker::visitStatementWhile(StatementWhile *p) {
    StingrayType *exprType = visit(p->expression_);

    if (!exprType->coercesTo(new SgBaseType(EBaseType::BOOLEAN))) { // todo
        error("Expression in while statement should have type boolean, but has: " + exprType->toString(),p);
    }

    symbolTable.pushLayer();
    p->body__->accept(this);
    symbolTable.popLayer();
}

void TypeChecker::visitStatementFor(StatementFor *p) {
    symbolTable.pushLayer();
    symbolTable.putAtCurrentLayer(p->ident_, new SgBaseType(EBaseType::INTEGER));
    p->body__->accept(this);
    symbolTable.popLayer();
}

void TypeChecker::visitStatementReturnValue(StatementReturnValue *p) {
    auto *returnedType = visit(p->expression_);
    if (!returnedType->coercesTo(funcTypes.top()->domain)) {
        printer->print(p);
        error("Returning " + returnedType->toString() + " which can not be coerced to " +
              funcTypes.top()->domain->toString(),p);
    }
}

void TypeChecker::visitStatementFunctionCall(StatementFunctionCall *p) { visit(p->funccall_); }

void TypeChecker::visitBody(Body *p) {
    for (auto *statement : *p->liststatement_) {
        statement->accept(this);
    }
}