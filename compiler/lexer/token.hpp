#pragma once
#include <cstdint>
#include <string>
#include <variant>

namespace aegis {

enum class TokenType {
    // Keywords
    FN,
    LET,
    MUT,
    IF,
    ELSE,
    WHILE,
    FOR,
    IN,
    RETURN,
    BREAK,
    CONTINUE,
    IMPORT,
    INPUT,
    QUERY,
    EXECUTE,
    SCAN,
    SNIFF,
    CAPABILITY,

    // Core Types & Qualifiers
    INT,
    FLOAT,
    BOOL,
    STRING,
    BYTE,
    ARRAY,
    MAP,
    TAINTED,
    SAFE,
    VOID,

    // Literals
    IDENTIFIER,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    TRUE,
    FALSE,

    // Special Keywords (DSL)
    SQL,
    COMMAND,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    ASSIGN,
    PLUS_ASSIGN,
    MINUS_ASSIGN,
    STAR_ASSIGN,
    SLASH_ASSIGN,
    INCREMENT,
    DECREMENT,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    AND,
    OR,
    NOT,

    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    COMMA,
    SEMICOLON,
    COLON,
    DOT,
    ARROW,
    RANGE,

    // Special
    EOF_TOKEN,
    INVALID
};

using Literal = std::variant<std::monostate, int64_t, double, std::string, bool>;

struct Token {
    TokenType type;
    std::string lexeme;
    Literal literal;
    uint32_t line;
    uint32_t column;

    Token(TokenType t, std::string lex, Literal lit, uint32_t l, uint32_t c)
        : type(t), lexeme(std::move(lex)), literal(std::move(lit)), line(l), column(c) {}

    Token(TokenType t, std::string lex, uint32_t l, uint32_t c)
        : type(t), lexeme(std::move(lex)), literal(std::monostate{}), line(l), column(c) {}
};

}  // namespace aegis
