#include "RuntimeValues.h"
#include <stdexcept>
#include <cmath>

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

RuntimeValue *IntegerValue::multiply(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new IntegerValue(value * otherInt->value);
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value * otherDouble->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *IntegerValue::deduct(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new IntegerValue(value - otherInt->value);
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value - otherDouble->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *IntegerValue::divide(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(value / otherInt->value);
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value / otherDouble->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *IntegerValue::mod(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new IntegerValue(value % otherInt->value);
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value % otherDouble->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *IntegerValue::pow(RuntimeValue *other) {

    if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new IntegerValue(pow(value, otherInt->value));
    } else if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(pow(value, otherDouble->value));
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

RuntimeValue *DoubleValue::multiply(RuntimeValue *other) {

    if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value * otherDouble->value);
    } else if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(value * otherInt->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *DoubleValue::deduct(RuntimeValue *other) {

    if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value - otherDouble->value);
    } else if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(value - otherInt->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *DoubleValue::divide(RuntimeValue *other) {

    if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(value / otherDouble->value);
    } else if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(value / otherInt->value);
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}

RuntimeValue *DoubleValue::pow(RuntimeValue *other) {

    if (auto *otherDouble = dynamic_cast<DoubleValue *>(other)) {
        return new DoubleValue(pow(value, otherDouble->value));
    } else if (auto *otherInt = dynamic_cast<IntegerValue *>(other)) {
        return new DoubleValue(pow(value, otherInt->value));
    }

    throw std::logic_error("Bad Types"); // should not happen, type checker should handle this
}