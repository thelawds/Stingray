
#ifndef COMPILER_STINGRAYTYPES_H
#define COMPILER_STINGRAYTYPES_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ALLOWS_IMPLICIT_CONVERSION

enum class EBaseType { NOTHING, BOOLEAN, INTEGER, DOUBLE, STRING, UNTYPED };
enum class TypeCategory { BASE, ARRAY, FUNCTION, CLASS, AUTO };

struct StingrayType {
    const TypeCategory typeCategory;

    explicit StingrayType(TypeCategory typeCategory);

    virtual bool equals(const StingrayType *) const = 0;

    virtual bool coercesTo(const StingrayType *) const = 0;

    virtual std::string toString() const = 0;

    virtual StingrayType *copy() const = 0;

    inline virtual bool isArray() { return false; }
    inline virtual bool isFunction(size_t rangeSize) { return false; }

};

struct SgAutoType : StingrayType {
    SgAutoType();

    void coercedBy(const StingrayType *type) const;
    bool equals(const StingrayType *type) const override;
    bool coercesTo(const StingrayType *type) const override;

    bool isArray() override;

    bool isFunction(size_t rangeSize) override;

    std::string toString() const override;
    virtual StingrayType *copy() const override;

    StingrayType *decide() const;

    mutable bool function{false};
    mutable bool array{false};
    mutable bool decidable{true};
    mutable StingrayType *constraint;
};

struct SgBaseType : StingrayType {
    EBaseType value;

    ALLOWS_IMPLICIT_CONVERSION
    SgBaseType(EBaseType value); // NOLINT(google-explicit-constructor)

    bool operator==(const SgBaseType &rhs) const;
    bool operator!=(const SgBaseType &rhs) const;

    bool equals(const StingrayType *type) const override;
    bool coercesTo(const StingrayType *type) const override;

    std::string toString() const override;
    virtual StingrayType *copy() const override;
};

struct SgArrayType : StingrayType {
    StingrayType *parentType;

    explicit SgArrayType(StingrayType *parentType);

    bool equals(const StingrayType *type) const override;
    bool coercesTo(const StingrayType *type) const override;

    std::string toString() const override;
    virtual StingrayType *copy() const override;

    inline virtual bool isArray() { return true; }
};

struct SgFunctionType : StingrayType {
    std::vector<StingrayType *> range;
    StingrayType *domain;

    SgFunctionType(std::vector<StingrayType *> range, StingrayType *domain);

    void addRangeType(StingrayType *);

    bool equals(const StingrayType *type) const override;
    bool coercesTo(const StingrayType *type) const override;

    std::string toString() const override;
    virtual StingrayType *copy() const override;

    inline bool isFunction(size_t rangeSize) override { return range.size() == rangeSize; }
};

struct SgClassType : StingrayType {
    std::string className;
    StingrayType *parentClass{nullptr};

    std::unordered_map<std::string, StingrayType *> classVariables;
    std::unordered_map<std::string, StingrayType *> objectVariables;

    explicit SgClassType(std::string name);
    SgClassType(std::string className, StingrayType *parentClass,
                std::unordered_map<std::string, StingrayType *> classVariables,
                std::unordered_map<std::string, StingrayType *> objectVariables);

    bool equals(const StingrayType *type) const override;
    bool coercesTo(const StingrayType *type) const override;
    std::string toString() const override;

    bool contains(const std::string &fieldName) const;

    StingrayType *get(const std::string &fieldName);

    virtual StingrayType *copy() const override;
};

#endif // COMPILER_STINGRAYTYPES_H
