
#ifndef COMPILER_INTERPRETATIONVISITOR_H
#define COMPILER_INTERPRETATIONVISITOR_H

#include "intermediate/LayeredTable.h"
#include "intermediate/RuntimeValues.h"
#include "intermediate/StingrayTypes.h"
#include "syntax/Absyn.H"

#include <stack>

class InterpretationVisitor : Visitor {

  public:
    InterpretationVisitor() = default;

    void visitProgram(Program *p) override;
    void visitArithmeticSum(ArithmeticSum *p) override;
    void visitIntegerTerm(IntegerTerm *p) override;
    void visitDoubleTerm(DoubleTerm *p) override;
    void visitVariableReferenceTerm(VariableReferenceTerm *p) override;

    void visitStatementVarDecl(StatementVarDecl *p) override;
    void visitValueArrowed(ValueArrowed *p) override;
    void visitValueBraced(ValueBraced *p) override;

    void visitProgram_(Program_ *p) override;
    void visitDeclaration(Declaration *p) override;
    void visitFunctionDeclType(FunctionDeclType *p) override;
    void visitFunctionDefType(FunctionDefType *p) override;
    void visitFunctionDeclaration(FunctionDeclaration *p) override;
    void visitFunctionDefinition(FunctionDefinition *p) override;
    void visitFunctionDomain(FunctionDomain *p) override;
    void visitFunctionRangeSingle(FunctionRangeSingle *p) override;
    void visitFunctionRangeMultiple(FunctionRangeMultiple *p) override;
    void visitFunctionParameter(FunctionParameter *p) override;
    void visitFunctionRangeSingleNamed(FunctionRangeSingleNamed *p) override;
    void visitFunctionRangeMultipleNamed(FunctionRangeMultipleNamed *p) override;
    void visitStatementAssignment(StatementAssignment *p) override;

  private:
    virtual void visitDecl(Decl *p) override;
    virtual void visitTypeReference(TypeReference *p) override;
    virtual void visitExtends(Extends *p) override;
    virtual void visitFieldDef(FieldDef *p) override;
    virtual void visitStatics(Statics *p) override;
    virtual void visitCBody(CBody *p) override;
    virtual void visitFuncDecl(FuncDecl *p) override;
    virtual void visitFuncDefn(FuncDefn *p) override;
    virtual void visitFuncDomain(FuncDomain *p) override;
    virtual void visitFuncRange(FuncRange *p) override;
    virtual void visitFuncParam(FuncParam *p) override;
    virtual void visitFuncRangeNamed(FuncRangeNamed *p) override;
    virtual void visitStatement(Statement *p) override;
    virtual void visitStatementIf_(StatementIf_ *p) override;
    virtual void visitBody_(Body_ *p) override;
    virtual void visitValue(Value *p) override;
    virtual void visitExpression(Expression *p) override;
    virtual void visitFuncCall(FuncCall *p) override;
    virtual void visitRangeExpr(RangeExpr *p) override;
    virtual void visitUnsteppedRangeExpression(UnsteppedRangeExpression *p) override;
    virtual void visitRangeBody_(RangeBody_ *p) override;
    virtual void visitNothingType(NothingType *p) override;
    virtual void visitBoolType(BoolType *p) override;
    virtual void visitIntegerType(IntegerType *p) override;
    virtual void visitDoubleType(DoubleType *p) override;
    virtual void visitStringType(StringType *p) override;
    virtual void visitArrayType(ArrayType *p) override;
    virtual void visitClassType(ClassType *p) override;
    virtual void visitUserType(UserType *p) override;
    virtual void visitExtendsEmpty(ExtendsEmpty *p) override;
    virtual void visitExtendsList(ExtendsList *p) override;
    virtual void visitFieldDeclaration(FieldDeclaration *p) override;
    virtual void visitFieldDefinition(FieldDefinition *p) override;
    virtual void visitFieldDefinitionAsc(FieldDefinitionAsc *p) override;
    virtual void visitStaticsEmpty(StaticsEmpty *p) override;
    virtual void visitStaticsBody(StaticsBody *p) override;
    virtual void visitClassBody(ClassBody *p) override;
    virtual void visitStatementVarDef(StatementVarDef *p) override;
    virtual void visitStatementVarDefAsc(StatementVarDefAsc *p) override;
    virtual void visitStatementIf(StatementIf *p) override;
    virtual void visitStatementWhile(StatementWhile *p) override;
    virtual void visitStatementFor(StatementFor *p) override;
    virtual void visitStatementReturnNone(StatementReturnNone *p) override;
    virtual void visitStatementReturnValue(StatementReturnValue *p) override;
    virtual void visitStatementFunctionCall(StatementFunctionCall *p) override;
    virtual void visitIfStatement(IfStatement *p) override;
    virtual void visitIfElseIfStatement(IfElseIfStatement *p) override;
    virtual void visitIfElseStatement(IfElseStatement *p) override;
    virtual void visitBody(Body *p) override;
    virtual void visitMethodReference(MethodReference *p) override;
    virtual void visitRelationalEquals(RelationalEquals *p) override;
    virtual void visitRelationalNotEquals(RelationalNotEquals *p) override;
    virtual void visitRelationalLess(RelationalLess *p) override;
    virtual void visitRelationalGreater(RelationalGreater *p) override;
    virtual void visitRelationalLessOrEqual(RelationalLessOrEqual *p) override;
    virtual void visitRelationalGreaterOrEqual(RelationalGreaterOrEqual *p) override;
    virtual void visitArithmeticDifference(ArithmeticDifference *p) override;
    virtual void visitArithmeticProduct(ArithmeticProduct *p) override;
    virtual void visitArithmeticQuotient(ArithmeticQuotient *p) override;
    virtual void visitArithmeticModulus(ArithmeticModulus *p) override;
    virtual void visitArithmeticExponentiation(ArithmeticExponentiation *p) override;
    virtual void visitLogicalUnaryNot(LogicalUnaryNot *p) override;
    virtual void visitLogicalConjunction(LogicalConjunction *p) override;
    virtual void visitLogicalDisjunction(LogicalDisjunction *p) override;
    virtual void visitLogicalExclusiveDisjunction(LogicalExclusiveDisjunction *p) override;
    virtual void visitLogicalImplication(LogicalImplication *p) override;
    virtual void visitLogicalEquivalence(LogicalEquivalence *p) override;
    virtual void visitUnaryHashCode(UnaryHashCode *p) override;
    virtual void visitUnaryMinus(UnaryMinus *p) override;
    virtual void visitTrueTerm(TrueTerm *p) override;
    virtual void visitFalseTerm(FalseTerm *p) override;
    virtual void visitEmptyTerm(EmptyTerm *p) override;
    virtual void visitStringTerm(StringTerm *p) override;
    virtual void visitArrayReferenceTerm(ArrayReferenceTerm *p) override;
    virtual void visitFieldReferenceTerm(FieldReferenceTerm *p) override;
    virtual void visitFunctionCallExpr(FunctionCallExpr *p) override;
    virtual void visitFunctionCall(FunctionCall *p) override;
    virtual void visitArrayInitializer(ArrayInitializer *p) override;
    virtual void visitRangeExpressionTerm(RangeExpressionTerm *p) override;
    virtual void visitRangeExpression(RangeExpression *p) override;
    virtual void visitSteppedRangeExpression(SteppedRangeExpression *p) override;
    virtual void visitOpenRange(OpenRange *p) override;
    virtual void visitClosedRange(ClosedRange *p) override;
    virtual void visitLeftClosedRightOpenedRange(LeftClosedRightOpenedRange *p) override;
    virtual void visitLeftOpenedRightClosedRange(LeftOpenedRightClosedRange *p) override;
    virtual void visitRangeBody(RangeBody *p) override;
    virtual void visitListDecl(ListDecl *p) override;
    virtual void visitListIdent(ListIdent *p) override;
    virtual void visitListFieldDef(ListFieldDef *p) override;
    virtual void visitListTypeReference(ListTypeReference *p) override;
    virtual void visitListFuncParam(ListFuncParam *p) override;
    virtual void visitListStatement(ListStatement *p) override;
    virtual void visitListExpression(ListExpression *p) override;
    virtual void visitInteger(Integer x) override;
    virtual void visitChar(Char x) override;
    virtual void visitDouble(Double x) override;
    virtual void visitString(String x) override;
    virtual void visitIdent(Ident x) override;

  private:
    LayeredTable<RuntimeValue> stackFrame;
    std::stack<RuntimeValue *> returnedValues;

    RuntimeValue *stackPop();
    void returnValue(RuntimeValue *);
    RuntimeValue *visit(Visitable *);
};

#endif // COMPILER_INTERPRETATIONVISITOR_H
