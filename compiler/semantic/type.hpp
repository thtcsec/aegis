#pragma once
#include <memory>
#include <string>
#include <vector>

namespace aegis {

enum class TypeKind { INT, FLOAT, BOOL, STRING, BYTE, ARRAY, MAP, TAINTED, SAFE, VOID, UNKNOWN };

class Type {
public:
    virtual ~Type() = default;
    virtual TypeKind getKind() const = 0;
    virtual std::string toString() const = 0;
    virtual bool equals(const Type* other) const = 0;
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(TypeKind kind) : kind_(kind) {}

    TypeKind getKind() const override {
        return kind_;
    }

    std::string toString() const override {
        switch (kind_) {
            case TypeKind::INT:
                return "int";
            case TypeKind::FLOAT:
                return "float";
            case TypeKind::BOOL:
                return "bool";
            case TypeKind::STRING:
                return "string";
            case TypeKind::BYTE:
                return "byte";
            case TypeKind::VOID:
                return "void";
            default:
                return "unknown";
        }
    }

    bool equals(const Type* other) const override {
        if (auto* prim = dynamic_cast<const PrimitiveType*>(other)) {
            return kind_ == prim->kind_;
        }
        return false;
    }

private:
    TypeKind kind_;
};

class ArrayType : public Type {
public:
    explicit ArrayType(std::shared_ptr<Type> element_type) : element_type_(element_type) {}

    TypeKind getKind() const override {
        return TypeKind::ARRAY;
    }

    std::string toString() const override {
        return "array<" + element_type_->toString() + ">";
    }

    bool equals(const Type* other) const override {
        if (auto* arr = dynamic_cast<const ArrayType*>(other)) {
            return element_type_->equals(arr->element_type_.get());
        }
        return false;
    }

    std::shared_ptr<Type> getElementType() const {
        return element_type_;
    }

private:
    std::shared_ptr<Type> element_type_;
};

class MapType : public Type {
public:
    MapType(std::shared_ptr<Type> key_type, std::shared_ptr<Type> value_type)
        : key_type_(key_type), value_type_(value_type) {}

    TypeKind getKind() const override {
        return TypeKind::MAP;
    }

    std::string toString() const override {
        return "map<" + key_type_->toString() + ", " + value_type_->toString() + ">";
    }

    bool equals(const Type* other) const override {
        if (auto* map = dynamic_cast<const MapType*>(other)) {
            return key_type_->equals(map->key_type_.get()) &&
                   value_type_->equals(map->value_type_.get());
        }
        return false;
    }

    std::shared_ptr<Type> getKeyType() const {
        return key_type_;
    }
    std::shared_ptr<Type> getValueType() const {
        return value_type_;
    }

private:
    std::shared_ptr<Type> key_type_;
    std::shared_ptr<Type> value_type_;
};

class TaintedType : public Type {
public:
    explicit TaintedType(std::shared_ptr<Type> inner_type) : inner_type_(inner_type) {}

    TypeKind getKind() const override {
        return TypeKind::TAINTED;
    }

    std::string toString() const override {
        return "tainted<" + inner_type_->toString() + ">";
    }

    bool equals(const Type* other) const override {
        if (auto* tainted = dynamic_cast<const TaintedType*>(other)) {
            return inner_type_->equals(tainted->inner_type_.get());
        }
        return false;
    }

    std::shared_ptr<Type> getInnerType() const {
        return inner_type_;
    }

private:
    std::shared_ptr<Type> inner_type_;
};

class SafeType : public Type {
public:
    explicit SafeType(std::shared_ptr<Type> inner_type) : inner_type_(inner_type) {}

    TypeKind getKind() const override {
        return TypeKind::SAFE;
    }

    std::string toString() const override {
        return "safe<" + inner_type_->toString() + ">";
    }

    bool equals(const Type* other) const override {
        if (auto* safe = dynamic_cast<const SafeType*>(other)) {
            return inner_type_->equals(safe->inner_type_.get());
        }
        return false;
    }

    std::shared_ptr<Type> getInnerType() const {
        return inner_type_;
    }

private:
    std::shared_ptr<Type> inner_type_;
};

// Type factory functions
inline std::shared_ptr<Type> makeIntType() {
    return std::make_shared<PrimitiveType>(TypeKind::INT);
}

inline std::shared_ptr<Type> makeFloatType() {
    return std::make_shared<PrimitiveType>(TypeKind::FLOAT);
}

inline std::shared_ptr<Type> makeBoolType() {
    return std::make_shared<PrimitiveType>(TypeKind::BOOL);
}

inline std::shared_ptr<Type> makeStringType() {
    return std::make_shared<PrimitiveType>(TypeKind::STRING);
}

inline std::shared_ptr<Type> makeByteType() {
    return std::make_shared<PrimitiveType>(TypeKind::BYTE);
}

inline std::shared_ptr<Type> makeVoidType() {
    return std::make_shared<PrimitiveType>(TypeKind::VOID);
}

inline std::shared_ptr<Type> makeArrayType(std::shared_ptr<Type> element_type) {
    return std::make_shared<ArrayType>(element_type);
}

inline std::shared_ptr<Type> makeMapType(std::shared_ptr<Type> key_type,
                                         std::shared_ptr<Type> value_type) {
    return std::make_shared<MapType>(key_type, value_type);
}

inline std::shared_ptr<Type> makeTaintedType(std::shared_ptr<Type> inner_type) {
    return std::make_shared<TaintedType>(inner_type);
}

inline std::shared_ptr<Type> makeSafeType(std::shared_ptr<Type> inner_type) {
    return std::make_shared<SafeType>(inner_type);
}

}  // namespace aegis
