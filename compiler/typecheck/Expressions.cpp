#include "TypeChecker.h"

void TypeChecker::visitRelationalEquals(RelationalEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->coercesTo(rhsType) || rhsType->coercesTo(lhsType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational = should be equal or derived from common base", p);
    }
}

void TypeChecker::visitRelationalNotEquals(RelationalNotEquals *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    if (lhsType->coercesTo(rhsType) || rhsType->coercesTo(lhsType)) {
        returnValue(EBaseType::BOOLEAN);
    } else {
        error("Types for relational != should be equal or derived from common base", p);
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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);

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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);

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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);

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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);

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

        auto *stringType = new SgBaseType(EBaseType::STRING); // todo delete
        if ((lhsType->equals(stringType) || rhsType->equals(stringType)) &&
            lhsType->coercesTo(stringType) && // todo: optimize
            rhsType->coercesTo(stringType)) {

            returnValue(EBaseType::STRING);
            return;
        }

        error("Unexpected types for arithmetic + operator. Expected both numerical or string, but got: " +
                  lhsType->toString() + " and " + rhsType->toString(),
              p);

    } else {
        error("Types for arithmetic + should be base", p);
    }
}

void TypeChecker::visitArithmeticDifference(ArithmeticDifference *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    bool lhsNumeric = lhsType->coercesTo(DOUBLE_TYPE) || lhsType->coercesTo(INTEGER_TYPE);
    bool rhsNumeric = rhsType->coercesTo(DOUBLE_TYPE) || rhsType->coercesTo(INTEGER_TYPE);

    if (lhsNumeric && rhsNumeric) {

        if (lhsType->equals(INTEGER_TYPE) && rhsType->equals(INTEGER_TYPE)) {
            returnValue(EBaseType::INTEGER);
            return;
        } else {
            returnValue(EBaseType::DOUBLE);
            return;
        }

    } else {
        error("Types for arithmetic - should be base numeric", p);
    }
}

void TypeChecker::visitArithmeticProduct(ArithmeticProduct *p) {
    auto *lhsType = visit(p->expression_1); // validate lhs
    auto *rhsType = visit(p->expression_2); // validate rhs

    bool lhsNumeric = lhsType->coercesTo(DOUBLE_TYPE) || lhsType->coercesTo(INTEGER_TYPE);
    bool rhsNumeric = rhsType->coercesTo(DOUBLE_TYPE) || rhsType->coercesTo(INTEGER_TYPE);

    if (lhsNumeric && rhsNumeric) {

        if (lhsType->equals(INTEGER_TYPE) && rhsType->equals(INTEGER_TYPE)) {
            returnValue(EBaseType::INTEGER);
            return;
        } else {
            returnValue(EBaseType::DOUBLE);
            return;
        }

    } else {
        error("Types for arithmetic * should be base numeric", p);
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
                  " and " + rhsType->toString(),
              p);

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
                  " and " + rhsType->toString(),
              p);

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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);
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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);
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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);
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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);
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
                  lhsType->toString() + " and " + rhsType->toString(),
              p);
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

void TypeChecker::visitArrayReferenceTerm(ArrayReferenceTerm *p) {
    auto *lhsType = visit(p->expression_1);
    if (!lhsType->isArray()) {
        error("Can not apply [] to the variable of type " + lhsType->toString() + ". Expected array.", p);
    }

    auto *rhsType = visit(p->expression_2);
    if (!rhsType->coercesTo(INTEGER_TYPE)) {
        error("Can not apply [] with index of type " + rhsType->toString() + ". Expected Integer.", p);
    }

    auto *arr = dynamic_cast<SgArrayType *>(lhsType);

    if (!arr){
        arr = dynamic_cast<SgArrayType *>(dynamic_cast<SgAutoType *>(lhsType)->constraint);
    }

    returnValue(arr->parentType);
}

void TypeChecker::visitFunctionCallExpr(FunctionCallExpr *p) { returnValue(visit(p->funccall_)); }

void TypeChecker::visitFunctionCall(FunctionCall *p) {
    auto *refType = visit(p->expression_);

    if (refType->isFuncion()) {
        // todo: check parameters
        // todo: apply type inference
        auto *funcType = dynamic_cast<SgFunctionType *>(refType);

        if (funcType->range.size() != p->listexpression_->size()) {
            error("Can not call function. Size of formal parameters differs from actual given: expected " +
                      std::to_string(funcType->range.size()) +
                      ", but given: " + std::to_string(p->listexpression_->size()),
                  p);
        }

        for (size_t i = 0; i < funcType->range.size(); ++i) {
            auto *paramType = funcType->range[i];
            auto *argumentType = visit((*p->listexpression_)[i]);

            if (!argumentType->coercesTo(paramType)) {
                error("Can not call function. Parameter at position " + std::to_string(i) +
                          " differs in type from given argument. Expected " + paramType->toString() +
                          ", but given: " + argumentType->toString(),
                      p);
            }
        }

        returnValue(funcType->domain);
    } else if (refType->typeCategory == TypeCategory::CLASS) {
        auto *classType = dynamic_cast<SgClassType *>(refType);
        returnValue(classType);
    } else {
        error("Unable to apply call operator to variable of type " + refType->toString(), p);
    }
}

void TypeChecker::visitFieldReferenceTerm(FieldReferenceTerm *p) {
    auto *referencableType = visit(p->expression_);

    bool isArrayOrString = referencableType->typeCategory == TypeCategory::ARRAY ||
                           referencableType->typeCategory == TypeCategory::BASE &&
                               dynamic_cast<SgBaseType *>(referencableType)->value == EBaseType::STRING;

    if (isArrayOrString && p->ident_ == "length") {
        returnValue(EBaseType::INTEGER);
        return;
    }

    if (referencableType->typeCategory != TypeCategory::CLASS) {
        error("Can not apply referencing operator '.' to the variable of type " + referencableType->toString(), p);
    }

    auto *classType = dynamic_cast<SgClassType *>(referencableType);

    if (classType->contains(p->ident_)) {
        returnValue(classType->get(p->ident_));
    } else {
        error("Class " + classType->className + " does not contain member named " + p->ident_, p);
    }
}

void TypeChecker::visitMethodReference(MethodReference *p) {
    // todo: implement after classes
}
