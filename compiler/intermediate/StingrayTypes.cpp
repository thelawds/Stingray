#include "StingrayTypes.h"

#include <iostream>
#include <utility>

StingrayType::StingrayType(const TypeCategory typeCategory) : typeCategory(typeCategory) {}

SgBaseType::SgBaseType(EBaseType value) : value(value), StingrayType(TypeCategory::BASE) {}

bool SgBaseType::operator==(const SgBaseType &rhs) const { return value == rhs.value; }

bool SgBaseType::operator!=(const SgBaseType &rhs) const { return !(rhs == *this); }

bool SgBaseType::equals(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        return type->equals(this);
    }

    if (type->typeCategory == TypeCategory::BASE) {
        return *this == *dynamic_cast<const SgBaseType *>(type);
    } else {
        return false;
    }
}

bool SgBaseType::coercesTo(const StingrayType *type) const {

    if (type->typeCategory == TypeCategory::AUTO) {
        auto *baseType = dynamic_cast<const SgAutoType *>(type);
        baseType->coercedBy(this);
        return true;
    }

    if (type->typeCategory != TypeCategory::BASE) {
        return false;
    }

    auto *bType = dynamic_cast<const SgBaseType *>(type);

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
StingrayType *SgBaseType::copy() const { return new SgBaseType(value); }

SgArrayType::SgArrayType(StingrayType *parentType) : StingrayType(TypeCategory::ARRAY), parentType(parentType) {}

bool SgArrayType::equals(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        return type->equals(this);
    }

    if (type->typeCategory == TypeCategory::ARRAY) {
        auto *arrType = dynamic_cast<const SgArrayType *>(type);
        return arrType->parentType->equals(this->parentType);
    }

    return false;
}

bool SgArrayType::coercesTo(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        auto *baseType = dynamic_cast<const SgAutoType *>(type);
        baseType->coercedBy(this);
        return true;
    }

    return this->equals(type) || type->typeCategory == TypeCategory::ARRAY &&
                                     this->parentType->coercesTo(dynamic_cast<const SgArrayType *>(type)->parentType);
}

std::string SgArrayType::toString() const { return "Array<" + parentType->toString() + ">"; }

StingrayType *SgArrayType::copy() const { return new SgArrayType(parentType); }

SgFunctionType::SgFunctionType(std::vector<StingrayType *> range, StingrayType *domain)
    : StingrayType(TypeCategory::FUNCTION), range(std::move(range)), domain(domain) {}

bool SgFunctionType::equals(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        return type->equals(this);
    }

    if (type->typeCategory == TypeCategory::FUNCTION) {
        auto *fType = dynamic_cast<const SgFunctionType *>(type);

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

bool SgFunctionType::coercesTo(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        auto *baseType = dynamic_cast<const SgAutoType *>(type);
        baseType->coercedBy(this);
        return true;
    }

    return this->equals(type);
}

std::string SgFunctionType::toString() const {
    std::string rangeStr;
    bool needComma = false;
    for (auto *rItem : range) {
        if (needComma) {
            rangeStr += ", ";
        }
        rangeStr += rItem->toString();
        needComma = true;
    }

    return "(" + rangeStr + ") -> " + domain->toString();
}

void SgFunctionType::addRangeType(StingrayType *t) { range.push_back(t); }

StingrayType *SgFunctionType::copy() const { return new SgFunctionType(range, domain); }

bool SgClassType::equals(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        return type->equals(this);
    }

    if (type->typeCategory == TypeCategory::CLASS) {
        auto *classT = dynamic_cast<const SgClassType *>(type);
        return classT->className == className;
    }

    return false;
}

bool SgClassType::coercesTo(const StingrayType *type) const {
    if (type->typeCategory == TypeCategory::AUTO) {
        auto *baseType = dynamic_cast<const SgAutoType *>(type);
        baseType->coercedBy(this);
        return true;
    }

    return this->equals(type) || this->parentClass != nullptr && this->parentClass->coercesTo(type);
}

std::string SgClassType::toString() const {
    std::string extends;
    std::string statics = (classVariables.empty() ? "(" : "(\n");
    std::string body = (objectVariables.empty() ? "{" : "{\n");

    if (parentClass) {
        extends = "< " + parentClass->toString() + "> ";
    }

    for (auto &[name, type] : classVariables) {
        statics += "\t" + name + ": " + type->toString() + "\n";
    }
    statics += ")";

    for (auto &[name, type] : objectVariables) {
        body += "\t" + name + ": " + type->toString() + "\n";
    }
    body += "}";

    return "class " + className + extends + statics + body;
}

SgClassType::SgClassType(std::string name) : StingrayType(TypeCategory::CLASS), className(std::move(name)) {}

bool SgClassType::contains(const std::string &fieldName) const {
    return classVariables.contains(fieldName) || objectVariables.contains(fieldName);
}

StingrayType *SgClassType::get(const std::string &fieldName) {
    if (classVariables.contains(fieldName)) {
        return classVariables[fieldName];
    } else if (objectVariables.contains(fieldName)) {
        return objectVariables[fieldName];
    } else {
        return nullptr;
    }
}
SgClassType::SgClassType(std::string className, StingrayType *parentClass,
                         std::unordered_map<std::string, StingrayType *> classVariables,
                         std::unordered_map<std::string, StingrayType *> objectVariables)
    : StingrayType(TypeCategory::CLASS), className(std::move(className)), parentClass(parentClass),
      classVariables(std::move(classVariables)), objectVariables(std::move(objectVariables)) {}

StingrayType *SgClassType::copy() const {
    return new SgClassType(className, parentClass, classVariables, objectVariables);
}

SgAutoType::SgAutoType() : StingrayType(TypeCategory::AUTO) {}

std::string SgAutoType::toString() const { return "UNDECIDED: (" + constraint->toString() + ")"; }

bool SgAutoType::equals(const StingrayType *type) const {

    if (constraint) {
        if (constraint->coercesTo(type)) {
            constraint = type->copy();
        } else {
            return false;
        }
    } else {
        constraint = type->copy();
    }

    return true;
}

bool SgAutoType::coercesTo(const StingrayType *type) const {

    if (!constraint) {
        constraint = type->copy();
        return true;
    }

    if (!constraint->coercesTo(type)) {
        decidable = false;
    }

    if (!type->coercesTo(constraint)) {
        constraint = type->copy();
    }

    if (array) {
        decidable = constraint->typeCategory == TypeCategory::ARRAY;
    }

    return true;
}

void SgAutoType::coercedBy(const StingrayType *type) const {
    if (!constraint) {
        constraint = type->copy();
        return;
    }
}

StingrayType *SgAutoType::decide() const {
    if (auto constraintArray = dynamic_cast<SgArrayType *>(constraint)) {
        if (auto constraintUndecided = dynamic_cast<SgAutoType *>(constraintArray->parentType)) {
            constraintArray->parentType = constraintUndecided->decide();
            if (!constraintArray->parentType) {
                decidable = false;
            }
        }
    } else if (auto constraintFunction = dynamic_cast<SgFunctionType *>(constraint)) {
        for (auto *&rangeEl : constraintFunction->range) {
            if (auto *rangeElUndecided = dynamic_cast<SgAutoType *>(rangeEl)) {
                rangeEl = rangeElUndecided->decide();
                if (!rangeEl) {
                    decidable = false;
                    break;
                }
            }
        }

        if (auto *domainUndecided = dynamic_cast<SgAutoType *>(constraintFunction->domain)) {
            constraintFunction->domain = domainUndecided->decide();
            if (!constraintFunction->domain) {
                decidable = false;
            }
        }
    }

    if (decidable) {
        return constraint;
    }

    return nullptr;
}

StingrayType *SgAutoType::copy() const { return new SgAutoType(); }

bool SgAutoType::isArray() {
    if (constraint) {
        decidable = constraint->typeCategory == TypeCategory::ARRAY;
    } else {
        array = true;
        constraint = new SgArrayType(new SgAutoType());
    }

    return true;
}
bool SgAutoType::isFunction(size_t rangeSize) {
    if (constraint) {
        decidable = constraint->typeCategory == TypeCategory::FUNCTION;
    } else {
        function = true;

        std::vector<StingrayType *> range(rangeSize);
        for (int i = 0; i < rangeSize; ++i) {
            range[i] = new SgAutoType();
        }

        constraint = new SgFunctionType(range, new SgAutoType);
    }
    return true;
}
