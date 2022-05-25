#ifndef COMPILER_RUNTIMEVALUES_H
#define COMPILER_RUNTIMEVALUES_H

#include <string>

struct RuntimeValue {

    virtual RuntimeValue *add(RuntimeValue *other) = 0;
    virtual std::string toString() = 0;
};

struct IntegerValue : RuntimeValue {

    int value;

    explicit IntegerValue(int value);

    std::string toString() override;

    RuntimeValue *add(RuntimeValue *other) override;
};

struct DoubleValue : RuntimeValue {
    double value;

    explicit DoubleValue(double value);

    std::string toString() override;

    RuntimeValue *add(RuntimeValue *other) override;
};

#endif // COMPILER_RUNTIMEVALUES_H
