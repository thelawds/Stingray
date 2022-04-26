#include "StingrayTypes.h"

#include <utility>

StingrayType::StingrayType(const TypeCategory typeCategory) : typeCategory(typeCategory) {}

SgBaseType::SgBaseType(EBaseType value) : value(value), StingrayType(TypeCategory::BASE) {}

bool SgBaseType::operator==(const SgBaseType &rhs) const { return value == rhs.value; }

bool SgBaseType::operator!=(const SgBaseType &rhs) const { return !(rhs == *this); }

bool SgBaseType::equals(StingrayType *type) const {
    if (type->typeCategory == TypeCategory::BASE) {
        return *this == *dynamic_cast<SgBaseType *>(type);
    } else {
        return false;
    }
}

bool SgBaseType::coercesTo(StingrayType *type) const {

    if (type->typeCategory != TypeCategory::BASE) {
        return false;
    }

    auto *bType = dynamic_cast<SgBaseType *>(type);

    EBaseType lType = value;
    EBaseType rType = bType->value;

    // todo: empty conversions
    // Empty should convert:
    // -> Bool as 0
    // -> Integer as 0
    // -> Double as 0
    // -> String as ""
    // Or should just get runtime errors.

    return (lType == rType) ||                                             // Type -> Type
           (lType == EBaseType::INTEGER && rType == EBaseType::DOUBLE) ||  // Int -> Double
           (lType == EBaseType::BOOLEAN && rType == EBaseType::INTEGER) || // Bool -> Int
           (lType == EBaseType::INTEGER && rType == EBaseType::BOOLEAN) || // Int -> Bool
           lType == EBaseType::UNTYPED ||                                  // empty can be of any type
           rType == EBaseType::STRING;                                     // anything can be converted to String
}

std::string SgBaseType::toString() const {
    switch (value) {
    case EBaseType::NOTHING:
        return "Nothing";
    case EBaseType::BOOLEAN:
        return "BOOLEAN";
    case EBaseType::INTEGER:
        return "INTEGER";
    case EBaseType::DOUBLE:
        return "DOUBLE";
    case EBaseType::STRING:
        return "STRING";
    case EBaseType::UNTYPED:
        return "UNTYPED";
    }
}

SgArrayType::SgArrayType(StingrayType *parentType) : StingrayType(TypeCategory::ARRAY), parentType(parentType) {}

bool SgArrayType::equals(StingrayType *type) const {
    if (type->typeCategory == TypeCategory::ARRAY) {
        auto *arrType = dynamic_cast<SgArrayType *>(type);
        return arrType->parentType->equals(this->parentType);
    }

    return false;
}

bool SgArrayType::coercesTo(StingrayType *type) const { return this->equals(type); }

std::string SgArrayType::toString() const { return parentType->toString() + "[]"; }

SgFunctionType::SgFunctionType(std::vector<StingrayType *> range, StingrayType *domain)
    : StingrayType(TypeCategory::FUNCTION), range(std::move(range)), domain(domain) {}

bool SgFunctionType::equals(StingrayType *type) const {
    if (type->typeCategory == TypeCategory::FUNCTION) {
        auto *fType = dynamic_cast<SgFunctionType *>(type);

        if (!domain->equals(fType->domain)) {
            return false;
        }

        if (range.size() != fType->range.size()) {
            return false;
        }

        for (int i = 0; i < range.size(); ++i) {
            if (!range[i]->equals(fType->range[i])) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool SgFunctionType::coercesTo(StingrayType *type) const { return this->equals(type); }

std::string SgFunctionType::toString() const {
    std::string rangeStr;
    for (auto *rItem : range) {
        rangeStr += rItem->toString() + ", ";
    }

    return "(" + rangeStr + ") -> " + domain->toString();
}

void SgFunctionType::addRangeType(StingrayType *t) { range.push_back(t); }
