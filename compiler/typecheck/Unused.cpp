#include "TypeChecker.h"

void TypeChecker::visitTypeReference(TypeReference *p) {}
void TypeChecker::visitStatement(Statement *p) {}
void TypeChecker::visitValue(Value *p) {}
void TypeChecker::visitListStatement(ListStatement *p) {}
void TypeChecker::visitInteger(Integer x) {}
void TypeChecker::visitChar(Char x) {}
void TypeChecker::visitDouble(Double x) {}
void TypeChecker::visitString(String x) {}
void TypeChecker::visitIdent(Ident x) {}
void TypeChecker::visitStatementIf_(StatementIf_ *p) {}
void TypeChecker::visitBody_(Body_ *p) {}
void TypeChecker::visitStatementReturnNone(StatementReturnNone *p) {}
void TypeChecker::visitListExpression(ListExpression *p) {}
void TypeChecker::visitExpression(Expression *p) {}
void TypeChecker::visitRangeBody_(RangeBody_ *p) {}
void TypeChecker::visitDecl(Decl *p) {}
void TypeChecker::visitFuncDecl(FuncDecl *p) {}
void TypeChecker::visitFuncDefn(FuncDefn *p) {}
void TypeChecker::visitFuncDomain(FuncDomain *p) {}
void TypeChecker::visitFuncRange(FuncRange *p) {}
void TypeChecker::visitFuncParam(FuncParam *p) {}
void TypeChecker::visitFuncRangeNamed(FuncRangeNamed *p) {}
void TypeChecker::visitListDecl(ListDecl *p) {}
void TypeChecker::visitListTypeReference(ListTypeReference *p) {}
void TypeChecker::visitListFuncParam(ListFuncParam *p) {}

/**
 * Ranges are not type-checked
 */

void TypeChecker::visitRangeExpr(RangeExpr *p) {}
void TypeChecker::visitUnsteppedRangeExpression(UnsteppedRangeExpression *p) {}
void TypeChecker::visitRangeExpressionTerm(RangeExpressionTerm *p) {}
void TypeChecker::visitRangeExpression(RangeExpression *p) {}
void TypeChecker::visitSteppedRangeExpression(SteppedRangeExpression *p) {}
void TypeChecker::visitOpenRange(OpenRange *p) {}
void TypeChecker::visitClosedRange(ClosedRange *p) {}
void TypeChecker::visitLeftClosedRightOpenedRange(LeftClosedRightOpenedRange *p) {}
void TypeChecker::visitLeftOpenedRightClosedRange(LeftOpenedRightClosedRange *p) {}
void TypeChecker::visitRangeBody(RangeBody *p) {}
