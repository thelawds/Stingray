#include "InterpretationVisitor.h"

#include <stdexcept>

void InterpretationVisitor::visitIntegerTerm(IntegerTerm *p) { returnValue(new IntegerValue(p->integer_)); }

void InterpretationVisitor::visitDoubleTerm(DoubleTerm *p) { returnValue(new DoubleValue(p->double_)); }

void InterpretationVisitor::visitVariableReferenceTerm(VariableReferenceTerm *p) {
    if (stackFrame.contains(p->ident_)) {
        returnValue(stackFrame[p->ident_]);

    } else {
        throw std::logic_error("Stack frame does not contain " + p->ident_); // should not happen
    }
}

void InterpretationVisitor::visitValueArrowed(ValueArrowed *p) { returnValue(visit(p->expression_)); }

void InterpretationVisitor::visitValueBraced(ValueBraced *p) { returnValue(visit(p->expression_)); }

void InterpretationVisitor::visitArithmeticSum(ArithmeticSum *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->add(rhs));
}

void InterpretationVisitor::visitArithmeticProduct(ArithmeticProduct *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->multiply(rhs));
}

void InterpretationVisitor::visitArithmeticDifference(ArithmeticDifference *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->deduct(rhs));
}

void InterpretationVisitor::visitArithmeticQuotient(ArithmeticQuotient *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->divide(rhs));
}

void InterpretationVisitor::visitArithmeticModulus(ArithmeticModulus *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->mod(rhs));
}

void InterpretationVisitor::visitArithmeticExponentiation(ArithmeticExponentiation *p) {
    auto *lhs = visit(p->expression_1);
    auto *rhs = visit(p->expression_2);
    returnValue(lhs->pow(rhs));
}