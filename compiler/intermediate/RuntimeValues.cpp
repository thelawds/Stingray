#include "RuntimeValues.h"
#include <stdexcept>

IntegerValue::IntegerValue(int value) : value(value) {}

std::string IntegerValue::toString() { return std::to_string(value); }

RuntimeValue *IntegerValue::add(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new IntegerValue(value + otherInt->value);
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value + otherDouble->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

DoubleValue::DoubleValue(double value) : value(value) {}

std::string DoubleValue::toString() { return std::to_string(value); }

RuntimeValue *DoubleValue::add(RuntimeValue *other) {

    if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value + otherDouble->value);
    } else if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(value + otherInt->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}
