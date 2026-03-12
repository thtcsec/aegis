#include "parser.hpp"

namespace aegis {

Parser::Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), current_(0) {}

// Placeholder implementation for Phase 1
std::unique_ptr<ASTNode> Parser::parse() {
    // TODO: Implement parser
    return nullptr;
}

}  // namespace aegis
