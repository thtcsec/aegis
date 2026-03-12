#pragma once
#include <memory>

#include "../ast/ast_nodes.hpp"
#include "type.hpp"

namespace aegis {

class TypeChecker {
public:
    TypeChecker();
    bool check(ASTNode* node);

    // Type inference
    std::shared_ptr<Type> inferType(ASTNode* node);

    // Type compatibility
    bool isCompatible(const Type* from, const Type* to);
    bool canConvert(const Type* from, const Type* to);

private:
    std::shared_ptr<Type> checkExpression(ASTNode* expr);
    std::shared_ptr<Type> checkLiteral(ASTNode* literal);
    std::shared_ptr<Type> checkBinaryOp(ASTNode* binop);
};

}  // namespace aegis
