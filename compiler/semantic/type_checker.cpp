#include "type_checker.hpp"

#include "type.hpp"

namespace aegis {

TypeChecker::TypeChecker() {}

// Placeholder for Phase 1
bool TypeChecker::check(ASTNode* node) {
    // TODO: Implement type checking
    return true;
}

std::shared_ptr<Type> TypeChecker::inferType(ASTNode* node) {
    // TODO: Implement type inference
    return makeIntType();
}

bool TypeChecker::isCompatible(const Type* from, const Type* to) {
    // Same types are always compatible
    if (from->equals(to)) {
        return true;
    }

    // Safe -> Tainted is allowed (implicit conversion)
    if (from->getKind() == TypeKind::SAFE && to->getKind() == TypeKind::TAINTED) {
        auto* safe_from = dynamic_cast<const SafeType*>(from);
        auto* tainted_to = dynamic_cast<const TaintedType*>(to);
        if (safe_from && tainted_to) {
            return safe_from->getInnerType()->equals(tainted_to->getInnerType().get());
        }
    }

    return false;
}

bool TypeChecker::canConvert(const Type* from, const Type* to) {
    // Explicit conversions allowed
    // TODO: Implement conversion rules
    return false;
}

std::shared_ptr<Type> TypeChecker::checkExpression(ASTNode* expr) {
    // TODO: Implement expression type checking
    return makeIntType();
}

std::shared_ptr<Type> TypeChecker::checkLiteral(ASTNode* literal) {
    // TODO: Implement literal type checking
    return makeIntType();
}

std::shared_ptr<Type> TypeChecker::checkBinaryOp(ASTNode* binop) {
    // TODO: Implement binary operation type checking
    return makeIntType();
}

}  // namespace aegis
