
#ifndef COMPILER_CODEGENERATIONVISITOR_H
#define COMPILER_CODEGENERATIONVISITOR_H

#include "syntax/Absyn.H"
#include "intermediate//StingrayTypes.h"
#include "intermediate/LayeredTable.h"

#include <stack>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

class InterpretationVisitor : Visitor {

  public:
    InterpretationVisitor();

     void visitProgram_(Program_ *p) override;
     void visitDecl(Decl *p) override;
     void visitTypeReference(TypeReference *p) override;
     void visitFuncDecl(FuncDecl *p) override;
     void visitFuncDefn(FuncDefn *p) override;
     void visitFuncDomain(FuncDomain *p) override;
     void visitFuncRange(FuncRange *p) override;
     void visitFuncParam(FuncParam *p) override;
     void visitFuncRangeNamed(FuncRangeNamed *p) override;
     void visitStatement(Statement *p) override;
     void visitStatementIf_(StatementIf_ *p) override;
     void visitBody_(Body_ *p) override;
     void visitValue(Value *p) override;
     void visitExpression(Expression *p) override;
     void visitRangeExpr(RangeExpr *p) override;
     void visitUnsteppedRangeExpression(UnsteppedRangeExpression *p) override;
     void visitRangeBody_(RangeBody_ *p) override;
     void visitProgram(Program *p) override;
     void visitDeclaration(Declaration *p) override;
     void visitUserType(UserType *p) override;
     void visitNothingType(NothingType *p) override;
     void visitBoolType(BoolType *p) override;
     void visitIntegerType(IntegerType *p) override;
     void visitDoubleType(DoubleType *p) override;
     void visitStringType(StringType *p) override;
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
     void visitStatementVarDecl(StatementVarDecl *p) override;
     void visitStatementVarDef(StatementVarDef *p) override;
     void visitStatementVarDefAsc(StatementVarDefAsc *p) override;
     void visitStatementAssignment(StatementAssignment *p) override;
     void visitStatementIf(StatementIf *p) override;
     void visitStatementWhile(StatementWhile *p) override;
     void visitStatementFor(StatementFor *p) override;
     void visitStatementReturnNone(StatementReturnNone *p) override;
     void visitStatementReturnValue(StatementReturnValue *p) override;
     void visitIfStatement(IfStatement *p) override;
     void visitIfElseIfStatement(IfElseIfStatement *p) override;
     void visitIfElseStatement(IfElseStatement *p) override;
     void visitBody(Body *p) override;
     void visitValueArrowed(ValueArrowed *p) override;
     void visitValueBraced(ValueBraced *p) override;
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
     void visitRangeExpressionTerm(RangeExpressionTerm *p) override;
     void visitRangeExpression(RangeExpression *p) override;
     void visitSteppedRangeExpression(SteppedRangeExpression *p) override;
     void visitOpenRange(OpenRange *p) override;
     void visitClosedRange(ClosedRange *p) override;
     void visitLeftClosedRightOpenedRange(LeftClosedRightOpenedRange *p) override;
     void visitLeftOpenedRightClosedRange(LeftOpenedRightClosedRange *p) override;
     void visitRangeBody(RangeBody *p) override;
     void visitListDecl(ListDecl *p) override;
     void visitListTypeReference(ListTypeReference *p) override;
     void visitListFuncParam(ListFuncParam *p) override;
     void visitListStatement(ListStatement *p) override;
     void visitListExpression(ListExpression *p) override;
     void visitInteger(Integer x) override;
     void visitChar(Char x) override;
     void visitDouble(Double x) override;
     void visitString(String x) override;
     void visitIdent(Ident x) override;

  private:

    std::stack<llvm::Value *> returnValues;
    LayeredTable<llvm::AllocaInst> symbolTable;

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> module;


    llvm::Value *stackPop();
    void returnValue(llvm::Value *);
    llvm::Value *visit(Visitable *);

};

#endif // COMPILER_CODEGENERATIONVISITOR_H
