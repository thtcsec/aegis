#pragma once
#include <memory>
#include <vector>

#include "../ast/ast_nodes.hpp"
#include "../lexer/token.hpp"

namespace aegis {

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    std::unique_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens_;
    size_t current_;
};

}  // namespace aegis
