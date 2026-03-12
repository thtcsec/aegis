#pragma once
#include <string>

#include "token.hpp"

namespace aegis {

class Lexer {
public:
    explicit Lexer(std::string source);
    Token nextToken();

private:
    std::string source_;
    size_t pos_;
    int line_;
    int column_;

    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);
    void skipWhitespace();

    Token identifier();
    Token number();
    Token stringLiteral();
};

}  // namespace aegis
