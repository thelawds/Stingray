
#ifndef COMPILER_TYPECHECKER_H
#define COMPILER_TYPECHECKER_H

#include "intermediate/LayeredTable.h"
#include "intermediate/StingrayTypes.h"
#include "syntax/Absyn.H"
#include "syntax/Printer.H"
#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>

class TypeChecker : public Visitor {

  public:
    ~TypeChecker() override;
    void visitExpression(Expression *p) override;
    void visitUnsteppedRangeExpression(UnsteppedRangeExpression *p) override;
    void visitRangeBody_(RangeBody_ *p) override;
    void visitProgram(Program *p) override;
    void visitMethodReference(MethodReference *p) override;
    void visitRelationalEquals(RelationalEquals *p) override;
    void visitRelationalNotEquals(RelationalNotEquals *p) override;
    void visitRelationalLess(RelationalLess *p) override;
    void visitRelationalGreater(RelationalGreater *p) override;
    void visitRelationalLessOrEqual(RelationalLessOrEqual *p) override;
    void visitRelationalGreaterOrEqual(RelationalGreaterOrEqual *p) override;
    void visitArithmeticSum(ArithmeticSum *p) override;
    void visitArithmeticDifference(ArithmeticDifference *p) override;
    void visitArithmeticProduct(ArithmeticProduct *p) override;
    void visitArithmeticQuotient(ArithmeticQuotient *p) override;
    void visitArithmeticModulus(ArithmeticModulus *p) override;
    void visitArithmeticExponentiation(ArithmeticExponentiation *p) override;
    void visitLogicalUnaryNot(LogicalUnaryNot *p) override;
    void visitLogicalConjunction(LogicalConjunction *p) override;
    void visitLogicalDisjunction(LogicalDisjunction *p) override;
    void visitLogicalExclusiveDisjunction(LogicalExclusiveDisjunction *p) override;
    void visitLogicalImplication(LogicalImplication *p) override;
    void visitLogicalEquivalence(LogicalEquivalence *p) override;
    void visitUnaryHashCode(UnaryHashCode *p) override;
    void visitUnaryMinus(UnaryMinus *p) override;
    void visitTrueTerm(TrueTerm *p) override;
    void visitFalseTerm(FalseTerm *p) override;
    void visitEmptyTerm(EmptyTerm *p) override;
    void visitStringTerm(StringTerm *p) override;
    void visitIntegerTerm(IntegerTerm *p) override;
    void visitDoubleTerm(DoubleTerm *p) override;
    void visitVariableReferenceTerm(VariableReferenceTerm *p) override;
    void visitArrayReferenceTerm(ArrayReferenceTerm *p) override;
    void visitFieldReferenceTerm(FieldReferenceTerm *p) override;
    void visitFunctionCall(FunctionCall *p) override;
    void visitArrayInitializer(ArrayInitializer *p) override;
    void visitRangeExpression(RangeExpression *p) override;
    void visitSteppedRangeExpression(SteppedRangeExpression *p) override;
    void visitOpenRange(OpenRange *p) override;
    void visitClosedRange(ClosedRange *p) override;
    void visitLeftClosedRightOpenedRange(LeftClosedRightOpenedRange *p) override;
    void visitLeftOpenedRightClosedRange(LeftOpenedRightClosedRange *p) override;
    void visitRangeBody(RangeBody *p) override;
    void visitListExpression(ListExpression *p) override;
    void visitUserType(UserType *p) override;
    void visitNothingType(NothingType *p) override;
    void visitBoolType(BoolType *p) override;
    void visitAutoType(AutoType *p) override;
    void visitIntegerType(IntegerType *p) override;
    void visitDoubleType(DoubleType *p) override;
    void visitStringType(StringType *p) override;
    void visitStatementVarDecl(StatementVarDecl *p) override;
    void visitStatementVarDef(StatementVarDef *p) override;
    void visitStatementVarDefAsc(StatementVarDefAsc *p) override;
    void visitValueArrowed(ValueArrowed *p) override;
    void visitValueBraced(ValueBraced *p) override;

    void visitProgram_(Program_ *p) override;
    void visitTypeReference(TypeReference *p) override;
    void visitStatement(Statement *p) override;
    void visitValue(Value *p) override;
    void visitListStatement(ListStatement *p) override;
    void visitInteger(Integer x) override;
    void visitChar(Char x) override;
    void visitDouble(Double x) override;
    void visitString(String x) override;
    void visitIdent(Ident x) override;
    void visitStatementIf_(StatementIf_ *p) override;
    void visitBody_(Body_ *p) override;
    void visitRangeExpr(RangeExpr *p) override;
    void visitStatementIf(StatementIf *p) override;
    void visitStatementWhile(StatementWhile *p) override;
    void visitStatementFor(StatementFor *p) override;
    void visitStatementReturnNone(StatementReturnNone *p) override;
    void visitStatementReturnValue(StatementReturnValue *p) override;
    void visitIfStatement(IfStatement *p) override;
    void visitIfElseIfStatement(IfElseIfStatement *p) override;
    void visitIfElseStatement(IfElseStatement *p) override;
    void visitBody(Body *p) override;
    void visitRangeExpressionTerm(RangeExpressionTerm *p) override;
    void visitDecl(Decl *p) override;
    void visitFuncDecl(FuncDecl *p) override;
    void visitFuncDefn(FuncDefn *p) override;
    void visitFuncDomain(FuncDomain *p) override;
    void visitFuncRange(FuncRange *p) override;
    void visitFuncParam(FuncParam *p) override;
    void visitFuncRangeNamed(FuncRangeNamed *p) override;
    void visitDeclaration(Declaration *p) override;
    void visitFunctionDeclType(FunctionDeclType *p) override;
    void visitFunctionDefType(FunctionDefType *p) override;
    void visitArrayType(ArrayType *p) override;
    void visitFunctionDeclaration(FunctionDeclaration *p) override;
    void visitFunctionDefinition(FunctionDefinition *p) override;
    void visitFunctionDomain(FunctionDomain *p) override;
    void visitFunctionRangeSingle(FunctionRangeSingle *p) override;
    void visitFunctionRangeMultiple(FunctionRangeMultiple *p) override;
    void visitFunctionParameter(FunctionParameter *p) override;
    void visitFunctionRangeSingleNamed(FunctionRangeSingleNamed *p) override;
    void visitFunctionRangeMultipleNamed(FunctionRangeMultipleNamed *p) override;
    void visitListDecl(ListDecl *p) override;
    void visitListTypeReference(ListTypeReference *p) override;
    void visitListFuncParam(ListFuncParam *p) override;
    void visitStatementAssignment(StatementAssignment *p) override;
    void visitFuncCall(FuncCall *p) override;
    void visitStatementFunctionCall(StatementFunctionCall *p) override;
    void visitFunctionCallExpr(FunctionCallExpr *p) override;

    void visitClassDecl(ClassDecl *p) override;
    void visitClassDeclaration(ClassDeclaration *p) override;
    void visitClassType(ClassType *p) override;
    void visitExtends(Extends *p) override;
    void visitFieldDef(FieldDef *p) override;
    void visitStatics(Statics *p) override;
    void visitCBody(CBody *p) override;
    void visitExtendsList(ExtendsList *p) override;
    void visitFieldDeclaration(FieldDeclaration *p) override;
    void visitFieldDefinition(FieldDefinition *p) override;
    void visitFieldDefinitionAsc(FieldDefinitionAsc *p) override;
    void visitStaticsEmpty(StaticsEmpty *p) override;
    void visitStaticsBody(StaticsBody *p) override;
    void visitClassBody(ClassBody *p) override;
    void visitListIdent(ListIdent *p) override;
    void visitListFieldDef(ListFieldDef *p) override;
    void visitExtendsEmpty(ExtendsEmpty *p) override;

  private:
    std::stack<StingrayType *> returnedTypes; // todo: mange memory correctly
    std::stack<std::string> returnedFieldNames;
    std::unordered_map<std::string, StingrayType *> UserDefinedTypes;
    LayeredTable<StingrayType> symbolTable;

    std::string currentClassName;
    SgClassType *currentClassType;

    std::string currentFunctionName;
    SgFunctionType *currentFunctionType;

    SgBaseType *NOTHING_TYPE = new SgBaseType(EBaseType::NOTHING);
    SgBaseType *INTEGER_TYPE = new SgBaseType(EBaseType::INTEGER);
    SgBaseType *DOUBLE_TYPE = new SgBaseType(EBaseType::DOUBLE);

    PrintAbsyn *printer = new PrintAbsyn();

    StingrayType *stackPop();
    void returnValue(StingrayType *);
    void returnValue(EBaseType);
    StingrayType *visit(Visitable *);

    void error(const std::string &, Visitable *);                     // todo: provide better errors
    static void printType(const std::string &, const StingrayType *); // todo: use only for debug
};

#endif // COMPILER_TYPECHECKER_H
