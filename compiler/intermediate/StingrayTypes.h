
#ifndef COMPILER_STINGRAYTYPES_H
#define COMPILER_STINGRAYTYPES_H

#include <string>
#include "unordered_map"
#include <vector>

#define ALLOWS_IMPLICIT_CONVERSION

enum class EBaseType { NOTHING, BOOLEAN, INTEGER, DOUBLE, STRING, UNTYPED };
enum class TypeCategory { BASE, ARRAY, FUNCTION, CLASS };

struct StingrayType {
    const TypeCategory typeCategory;

    explicit StingrayType(TypeCategory typeCategory);

    virtual bool equals(StingrayType *) const = 0;

    virtual bool coercesTo(StingrayType *) const = 0;

    virtual std::string toString() const = 0;
};

struct SgBaseType : StingrayType {
    EBaseType value;

    ALLOWS_IMPLICIT_CONVERSION
    SgBaseType(EBaseType value); // NOLINT(google-explicit-constructor)

    bool operator==(const SgBaseType &rhs) const;
    bool operator!=(const SgBaseType &rhs) const;

    bool equals(StingrayType *type) const override;
    bool coercesTo(StingrayType *type) const override;

    std::string toString() const override;
};

struct SgArrayType : StingrayType {
    StingrayType *parentType;

    explicit SgArrayType(StingrayType *parentType);

    bool equals(StingrayType *type) const override;
    bool coercesTo(StingrayType *type) const override;

    std::string toString() const override;
};

struct SgFunctionType : StingrayType {
    std::vector<StingrayType *> range;
    StingrayType *domain;

    SgFunctionType(std::vector<StingrayType *> range, StingrayType *domain);

    void addRangeType(StingrayType *);

    bool equals(StingrayType *type) const override;
    bool coercesTo(StingrayType *type) const override;

    std::string toString() const override;
};

struct SgClassType : StingrayType {
    std::string className;
    StingrayType *parentClass{nullptr};

    std::unordered_map<std::string, StingrayType *> classVariables;
    std::unordered_map<std::string, StingrayType *> objectVariables;

    SgClassType(std::string name);

    bool equals(StingrayType *type) const override;
    bool coercesTo(StingrayType *type) const override;
    std::string toString() const override;

    bool contains(const std::string &fieldName) const;

    StingrayType *get(const std::string &fieldName);
};

#endif // COMPILER_STINGRAYTYPES_H
