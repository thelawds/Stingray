#include "TypeChecker.h"

void TypeChecker::visitRelationalEquals(RelationalEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational = should be base", p);
    }
}

void TypeChecker::visitRelationalNotEquals(RelationalNotEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->typeCategory == TypeCategory::BASE && rhsType->typeCategory == TypeCategory::BASE) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational != should be base", p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);

    } else {
        error("Types for relational < should be base", p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);

    } else {
        error("Types for relational > should be base", p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);

    } else {
        error("Types for relational <= should be base", p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);

    } else {
        error("Types for relational >= should be base", p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);

    } else {
        error("Types for arithmetic + should be base", p);
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
              " and " + rhsType->toString(), p);

    } else {
        error("Types for arithmetic - should be base", p);
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
              " and " + rhsType->toString(), p);

    } else {
        error("Types for arithmetic * should be base", p);
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
              " and " + rhsType->toString(), p);

    } else {
        error("Types for arithmetic / should be base", p);
    }
}

void TypeChecker::visitArithmeticModulus(ArithmeticModulus *p) {
    // todo
}

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
              " and " + rhsType->toString(), p);

    } else {
        error("Types for arithmetic ^ should be base", p);
    }
}

void TypeChecker::visitLogicalUnaryNot(LogicalUnaryNot *p) {
    // todo
}

void TypeChecker::visitLogicalConjunction(LogicalConjunction *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    auto *boolType = new SgBaseType(EBaseType::BOOLEAN);
    if (lhsType->coercesTo(boolType) && rhsType->coercesTo(boolType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Expected both types of logical and to be of type convertible to boolean, but got: " +
              lhsType->toString() + " and " + rhsType->toString(), p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);
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
              lhsType->toString() + " and " + rhsType->toString(), p);
    }
}

void TypeChecker::visitUnaryHashCode(UnaryHashCode *p) {
    // todo: not implemented
}

void TypeChecker::visitUnaryMinus(UnaryMinus *p) {
    // todo
}

void TypeChecker::visitArrayInitializer(ArrayInitializer *p) {
    StingrayType *arrayElementType{nullptr};

    for (auto *expr : *p->listexpression_) {
        auto *exprType = visit(expr);

        if (arrayElementType) {
            if (exprType->coercesTo(arrayElementType)) {
                // skip
            } else if (arrayElementType->coercesTo(exprType)) {
                arrayElementType = exprType;
            } else {
                error("All elements in array should have the same type", p);
            }

        } else {
            arrayElementType = exprType;
        }

        returnValue(new SgArrayType(arrayElementType));
    }
}

void TypeChecker::visitArrayReferenceTerm(ArrayReferenceTerm *p) {}

void TypeChecker::visitFieldReferenceTerm(FieldReferenceTerm *p) {}

void TypeChecker::visitFunctionCall(FunctionCall *p) {
    auto*refType = visit(p->expression_);

    if (refType->typeCategory == TypeCategory::FUNCTION) {
        // todo: check parameters
        auto *funcType = dynamic_cast<SgFunctionType *>(refType);
        returnValue(funcType->domain);
    } else {
        error("Unable to apply call operator to variable of type " + refType->toString(),  p);
    }
}

void TypeChecker::visitMethodReference(MethodReference *p) {}
