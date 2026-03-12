#pragma once

#include <memory>
#include <string>
#include <vector>

namespace aegis {
namespace compiler {
namespace ast {

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// Expressions
class Expression : public ASTNode {
public:
    virtual ~Expression() = default;
};

class NumberLiteral : public Expression {
public:
    double value;
    explicit NumberLiteral(double val) : value(val) {}
};

class StringLiteral : public Expression {
public:
    std::string value;
    explicit StringLiteral(const std::string& val) : value(val) {}
};

class VariableRef : public Expression {
public:
    std::string name;
    explicit VariableRef(const std::string& n) : name(n) {}
};

class BinaryExpression : public Expression {
public:
    std::string op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    BinaryExpression(std::string o, std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : op(std::move(o)), left(std::move(l)), right(std::move(r)) {}
};

// Statements
class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

class VariableDecl : public Statement {
public:
    std::string name;
    std::unique_ptr<Expression> initializer;

    VariableDecl(std::string n, std::unique_ptr<Expression> init)
        : name(std::move(n)), initializer(std::move(init)) {}
};

class ExpressionStmt : public Statement {
public:
    std::unique_ptr<Expression> expr;

    explicit ExpressionStmt(std::unique_ptr<Expression> e) : expr(std::move(e)) {}
};

class BlockStmt : public Statement {
public:
    std::vector<std::unique_ptr<Statement>> statements;
};

class FunctionDecl : public Statement {
public:
    std::string name;
    std::vector<std::string> params;  // Simplified for now
    std::unique_ptr<BlockStmt> body;

    FunctionDecl(std::string n, std::vector<std::string> p, std::unique_ptr<BlockStmt> b)
        : name(std::move(n)), params(std::move(p)), body(std::move(b)) {}
};

}  // namespace ast
}  // namespace compiler
}  // namespace aegis
