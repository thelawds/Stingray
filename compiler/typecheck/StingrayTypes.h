
#ifndef COMPILER_STINGRAYTYPES_H
#define COMPILER_STINGRAYTYPES_H

#include <string>
#include <vector>

#define ALLOWS_IMPLICIT_CONVERSION

enum class EBaseType { NOTHING, BOOLEAN, INTEGER, DOUBLE, STRING, UNTYPED };
enum class TypeCategory { BASE, ARRAY, FUNCTION };

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

#endif // COMPILER_STINGRAYTYPES_H
