#include "TypeChecker.h"

void TypeChecker::visitRelationalEquals(RelationalEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational = should be base");
    }
}

void TypeChecker::visitRelationalNotEquals(RelationalNotEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational != should be base");
    }
}

void TypeChecker::visitRelationalLess(RelationalLess *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if ((bLhsType == EBaseType::INTEGER || bLhsType == EBaseType::DOUBLE) &&
            (bRhsType == EBaseType::INTEGER || bRhsType == EBaseType::DOUBLE)) {

            returnValue(EBaseType::BOOLEAN);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::STRING) {
            returnValue(EBaseType::BOOLEAN);
            return;
        }

        error("Unexpected types for relational < operator. Expected both numerical or string, but got: " +
              lhsType->toString() + " and " + rhsType->toString());

    } else {
        error("Types for relational < should be base");
    }
}

void TypeChecker::visitRelationalGreater(RelationalGreater *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if ((bLhsType == EBaseType::INTEGER || bLhsType == EBaseType::DOUBLE) &&
            (bRhsType == EBaseType::INTEGER || bRhsType == EBaseType::DOUBLE)) {

            returnValue(EBaseType::BOOLEAN);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::STRING) {
            returnValue(EBaseType::BOOLEAN);
            return;
        }

        error("Unexpected types for relational > operator. Expected both numerical or string, but got: " +
              lhsType->toString() + " and " + rhsType->toString());

    } else {
        error("Types for relational > should be base");
    }
}

void TypeChecker::visitRelationalLessOrEqual(RelationalLessOrEqual *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if ((bLhsType == EBaseType::INTEGER || bLhsType == EBaseType::DOUBLE) &&
            (bRhsType == EBaseType::INTEGER || bRhsType == EBaseType::DOUBLE)) {

            returnValue(EBaseType::BOOLEAN);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::STRING) {
            returnValue(EBaseType::BOOLEAN);
            return;
        }

        error("Unexpected types for relational <= operator. Expected both numerical or string, but got: " +
              lhsType->toString() + " and " + rhsType->toString());

    } else {
        error("Types for relational <= should be base");
    }
}

void TypeChecker::visitRelationalGreaterOrEqual(RelationalGreaterOrEqual *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if ((bLhsType == EBaseType::INTEGER || bLhsType == EBaseType::DOUBLE) &&
            (bRhsType == EBaseType::INTEGER || bRhsType == EBaseType::DOUBLE)) {

            returnValue(EBaseType::BOOLEAN);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::STRING) {
            returnValue(EBaseType::BOOLEAN);
            return;
        }

        error("Unexpected types for relational >= operator. Expected both numerical or string, but got: " +
              lhsType->toString() + " and " + rhsType->toString());

    } else {
        error("Types for relational >= should be base");
    }
}

void TypeChecker::visitArithmeticSum(ArithmeticSum *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if (bLhsType == bRhsType && bLhsType == EBaseType::INTEGER) {
            returnValue(EBaseType::INTEGER);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::DOUBLE ||
            bLhsType == EBaseType::DOUBLE && bRhsType == EBaseType::INTEGER ||
            bLhsType == EBaseType::INTEGER && bRhsType == EBaseType::DOUBLE) {

            returnValue(EBaseType::DOUBLE);
            return;
        }

        auto *stringType = new SgBaseType(EBaseType::STRING);// todo delete
        if ((lhsType->equals(stringType) || rhsType->equals(stringType)) && lhsType->coercesTo(stringType) && // todo: optimize
            rhsType->coercesTo(stringType)) {

            returnValue(EBaseType::STRING);
            return;
        }

        error("Unexpected types for arithmetic + operator. Expected both numerical or string, but got: " +
              lhsType->toString() + " and " + rhsType->toString());

    } else {
        error("Types for arithmetic + should be base");
    }
}

void TypeChecker::visitArithmeticDifference(ArithmeticDifference *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if (bLhsType == bRhsType && bLhsType == EBaseType::INTEGER) {
            returnValue(EBaseType::INTEGER);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::DOUBLE ||
            bLhsType == EBaseType::DOUBLE && bRhsType == EBaseType::INTEGER ||
            bLhsType == EBaseType::INTEGER && bRhsType == EBaseType::DOUBLE) {

            returnValue(EBaseType::DOUBLE);
            return;
        }

        error("Unexpected types for arithmetic - operator. Expected both numerical, but got: " + lhsType->toString() +
              " and " + rhsType->toString());

    } else {
        error("Types for arithmetic - should be base");
    }
}

void TypeChecker::visitArithmeticProduct(ArithmeticProduct *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if (bLhsType == bRhsType && bLhsType == EBaseType::INTEGER) {
            returnValue(EBaseType::INTEGER);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::DOUBLE ||
            bLhsType == EBaseType::DOUBLE && bRhsType == EBaseType::INTEGER ||
            bLhsType == EBaseType::INTEGER && bRhsType == EBaseType::DOUBLE) {

            returnValue(EBaseType::DOUBLE);
            return;
        }

        error("Unexpected types for arithmetic * operator. Expected both numerical, but got: " + lhsType->toString() +
              " and " + rhsType->toString());

    } else {
        error("Types for arithmetic * should be base");
    }
}

void TypeChecker::visitArithmeticQuotient(ArithmeticQuotient *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if (bLhsType == bRhsType && bLhsType == EBaseType::INTEGER) {
            returnValue(EBaseType::INTEGER);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::DOUBLE ||
            bLhsType == EBaseType::DOUBLE && bRhsType == EBaseType::INTEGER ||
            bLhsType == EBaseType::INTEGER && bRhsType == EBaseType::DOUBLE) {

            returnValue(EBaseType::DOUBLE);
            return;
        }

        error("Unexpected types for arithmetic / operator. Expected both numerical, but got: " + lhsType->toString() +
              " and " + rhsType->toString());

    } else {
        error("Types for arithmetic / should be base");
    }
}

void TypeChecker::visitArithmeticModulus(ArithmeticModulus *p) {}

void TypeChecker::visitArithmeticExponentiation(ArithmeticExponentiation *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        auto bLhsType = dynamic_cast<SgBaseType *>(lhsType)->value;
        auto bRhsType = dynamic_cast<SgBaseType *>(rhsType)->value;

        if (bLhsType == bRhsType && bLhsType == EBaseType::INTEGER) {
            returnValue(EBaseType::INTEGER);
            return;
        }

        if (bLhsType == bRhsType && bLhsType == EBaseType::DOUBLE ||
            bLhsType == EBaseType::DOUBLE && bRhsType == EBaseType::INTEGER ||
            bLhsType == EBaseType::INTEGER && bRhsType == EBaseType::DOUBLE) {

            returnValue(EBaseType::DOUBLE);
            return;
        }

        error("Unexpected types for arithmetic ^ operator. Expected both numerical but got: " + lhsType->toString() +
              " and " + rhsType->toString());

    } else {
        error("Types for arithmetic ^ should be base");
    }
}

void TypeChecker::visitLogicalUnaryNot(LogicalUnaryNot *p) {}

void TypeChecker::visitLogicalConjunction(LogicalConjunction *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString());
    }
}

void TypeChecker::visitLogicalDisjunction(LogicalDisjunction *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString());
    }
}

void TypeChecker::visitLogicalExclusiveDisjunction(LogicalExclusiveDisjunction *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString());
    }
}

void TypeChecker::visitLogicalImplication(LogicalImplication *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString());
    }
}

void TypeChecker::visitLogicalEquivalence(LogicalEquivalence *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString());
    }
}

void TypeChecker::visitUnaryHashCode(UnaryHashCode *p) {
    // todo: not implemented
}

void TypeChecker::visitUnaryMinus(UnaryMinus *p) {}
void TypeChecker::visitRangeExpr(RangeExpr *p) {}
void TypeChecker::visitRangeExpressionTerm(RangeExpressionTerm *p) {}
void TypeChecker::visitArrayReferenceTerm(ArrayReferenceTerm *p) {}
void TypeChecker::visitFieldReferenceTerm(FieldReferenceTerm *p) {}
void TypeChecker::visitFunctionCall(FunctionCall *p) {}
void TypeChecker::visitArrayInitializer(ArrayInitializer *p) {}
void TypeChecker::visitRangeExpression(RangeExpression *p) {}
void TypeChecker::visitSteppedRangeExpression(SteppedRangeExpression *p) {}
void TypeChecker::visitOpenRange(OpenRange *p) {}
void TypeChecker::visitClosedRange(ClosedRange *p) {}
void TypeChecker::visitLeftClosedRightOpenedRange(LeftClosedRightOpenedRange *p) {}
void TypeChecker::visitLeftOpenedRightClosedRange(LeftOpenedRightClosedRange *p) {}
void TypeChecker::visitRangeBody(RangeBody *p) {}
void TypeChecker::visitMethodReference(MethodReference *p) {}
