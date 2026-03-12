#pragma once
#include <string>
#include <variant>

namespace aegis {

enum class TokenType {
    // Keywords
    FN,
    INPUT,
    QUERY,
    EXECUTE,
    IF,
    WHILE,
    FOR,
    RETURN,
    BREAK,
    CONTINUE,
    LET,
    MUT,
    SCAN,
    SNIFF,
    CAPABILITY,
    IMPORT,

    // Type keywords
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
    INTEGER,
    FLOAT_LITERAL,
    STRING_LITERAL,
    TRUE,
    FALSE,

    // Special keywords
    SQL,
    COMMAND,
    ELSE,
    IN,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    ASSIGN,
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

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType t, std::string lex, int l, int c)
        : type(t), lexeme(std::move(lex)), line(l), column(c) {}
};

}  // namespace aegis
