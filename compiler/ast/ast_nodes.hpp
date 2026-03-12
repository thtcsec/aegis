#pragma once
#include <memory>
#include <string>
#include <vector>

namespace aegis {

enum class ASTNodeType {
    PROGRAM,
    FUNCTION,
    VARIABLE,
    BINARY_OP,
    LITERAL,
    CALL,
    IF_STMT,
    WHILE_STMT,
    RETURN_STMT
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual ASTNodeType getType() const = 0;
};

class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;
    ASTNodeType getType() const override {
        return ASTNodeType::PROGRAM;
    }
};

class FunctionNode : public ASTNode {
public:
    std::string name;
    std::vector<std::string> params;
    std::unique_ptr<ASTNode> body;
    ASTNodeType getType() const override {
        return ASTNodeType::FUNCTION;
    }
};

class LiteralNode : public ASTNode {
public:
    std::string value;
    ASTNodeType getType() const override {
        return ASTNodeType::LITERAL;
    }
};

}  // namespace aegis
