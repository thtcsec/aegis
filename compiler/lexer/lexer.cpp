#include "lexer.hpp"

#include <cctype>
#include <unordered_map>

namespace aegis {

static const std::unordered_map<std::string, TokenType> keywords = {
    {"fn", TokenType::FN},
    {"let", TokenType::LET},
    {"mut", TokenType::MUT},
    {"input", TokenType::INPUT},
    {"query", TokenType::QUERY},
    {"execute", TokenType::EXECUTE},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"for", TokenType::FOR},
    {"in", TokenType::IN},
    {"return", TokenType::RETURN},
    {"break", TokenType::BREAK},
    {"continue", TokenType::CONTINUE},
    {"scan", TokenType::SCAN},
    {"sniff", TokenType::SNIFF},
    {"capability", TokenType::CAPABILITY},
    {"import", TokenType::IMPORT},
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"bool", TokenType::BOOL},
    {"string", TokenType::STRING},
    {"byte", TokenType::BYTE},
    {"array", TokenType::ARRAY},
    {"map", TokenType::MAP},
    {"tainted", TokenType::TAINTED},
    {"safe", TokenType::SAFE},
    {"void", TokenType::VOID},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"sql", TokenType::SQL},
    {"command", TokenType::COMMAND},
};

Lexer::Lexer(std::string source) : source_(std::move(source)), pos_(0), line_(1), column_(1) {}

Token Lexer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return Token(TokenType::EOF_TOKEN, "", line_, column_);
    }

    char c = advance();

    // Identifiers and keywords
    if (std::isalpha(c) || c == '_') {
        return identifier();
    }

    // Numbers
    if (std::isdigit(c)) {
        return number();
    }

    // String literals
    if (c == '"') {
        return stringLiteral();
    }

    // Single-character and multi-character tokens
    switch (c) {
        case '(':
            return Token(TokenType::LPAREN, "(", line_, column_ - 1);
        case ')':
            return Token(TokenType::RPAREN, ")", line_, column_ - 1);
        case '{':
            return Token(TokenType::LBRACE, "{", line_, column_ - 1);
        case '}':
            return Token(TokenType::RBRACE, "}", line_, column_ - 1);
        case '[':
            return Token(TokenType::LBRACKET, "[", line_, column_ - 1);
        case ']':
            return Token(TokenType::RBRACKET, "]", line_, column_ - 1);
        case ',':
            return Token(TokenType::COMMA, ",", line_, column_ - 1);
        case ';':
            return Token(TokenType::SEMICOLON, ";", line_, column_ - 1);
        case ':':
            return Token(TokenType::COLON, ":", line_, column_ - 1);
        case '+':
            if (match('='))
                return Token(TokenType::PLUS_ASSIGN, "+=", line_, column_ - 2);
            if (match('+'))
                return Token(TokenType::INCREMENT, "++", line_, column_ - 2);
            return Token(TokenType::PLUS, "+", line_, column_ - 1);
        case '-':
            if (match('='))
                return Token(TokenType::MINUS_ASSIGN, "-=", line_, column_ - 2);
            if (match('-'))
                return Token(TokenType::DECREMENT, "--", line_, column_ - 2);
            if (match('>'))
                return Token(TokenType::ARROW, "->", line_, column_ - 2);
            return Token(TokenType::MINUS, "-", line_, column_ - 1);
        case '*':
            if (match('='))
                return Token(TokenType::STAR_ASSIGN, "*=", line_, column_ - 2);
            return Token(TokenType::STAR, "*", line_, column_ - 1);
        case '/':
            if (match('='))
                return Token(TokenType::SLASH_ASSIGN, "/=", line_, column_ - 2);
            return Token(TokenType::SLASH, "/", line_, column_ - 1);
        case '%':
            return Token(TokenType::PERCENT, "%", line_, column_ - 1);
        case '<':
            if (match('='))
                return Token(TokenType::LE, "<=", line_, column_ - 2);
            return Token(TokenType::LT, "<", line_, column_ - 1);
        case '>':
            if (match('='))
                return Token(TokenType::GE, ">=", line_, column_ - 2);
            return Token(TokenType::GT, ">", line_, column_ - 1);
        case '!':
            if (match('='))
                return Token(TokenType::NE, "!=", line_, column_ - 2);
            return Token(TokenType::NOT, "!", line_, column_ - 1);
        case '&':
            if (match('&'))
                return Token(TokenType::AND, "&&", line_, column_ - 2);
            break;
        case '|':
            if (match('|'))
                return Token(TokenType::OR, "||", line_, column_ - 2);
            break;
        case '=':
            if (match('='))
                return Token(TokenType::EQ, "==", line_, column_ - 2);
            return Token(TokenType::ASSIGN, "=", line_, column_ - 1);
        case '.':
            if (match('.'))
                return Token(TokenType::RANGE, "..", line_, column_ - 2);
            return Token(TokenType::DOT, ".", line_, column_ - 1);
    }

    return Token(TokenType::INVALID, std::string(1, c), line_, column_ - 1);
}

bool Lexer::isAtEnd() const {
    return pos_ >= source_.length();
}

char Lexer::advance() {
    char c = source_[pos_++];
    column_++;
    return c;
}

char Lexer::peek() const {
    if (isAtEnd())
        return '\0';
    return source_[pos_];
}

char Lexer::peekNext() const {
    if (pos_ + 1 >= source_.length())
        return '\0';
    return source_[pos_ + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source_[pos_] != expected)
        return false;
    pos_++;
    column_++;
    return true;
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
        } else if (c == '\n') {
            line_++;
            column_ = 0;
            advance();
        } else if (c == '/' && peekNext() == '/') {
            // A single-line comment goes until the end of the line.
            while (!isAtEnd() && peek() != '\n') {
                advance();
            }
        } else {
            break;
        }
    }
}

Token Lexer::identifier() {
    int start = pos_ - 1;
    int startCol = column_ - 1;

    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        advance();
    }

    std::string text = source_.substr(start, pos_ - start);
    auto it = keywords.find(text);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;

    if (type == TokenType::TRUE)
        return Token(type, text, true, static_cast<uint32_t>(line_),
                     static_cast<uint32_t>(startCol));
    if (type == TokenType::FALSE)
        return Token(type, text, false, static_cast<uint32_t>(line_),
                     static_cast<uint32_t>(startCol));

    return Token(type, text, static_cast<uint32_t>(line_), static_cast<uint32_t>(startCol));
}

Token Lexer::number() {
    int start = pos_ - 1;
    int startCol = column_ - 1;

    while (!isAtEnd() && std::isdigit(peek())) {
        advance();
    }

    bool isFloat = false;

    // Look for a fractional part.
    if (!isAtEnd() && peek() == '.') {
        isFloat = true;
        advance();  // Consume the "."

        while (!isAtEnd() && std::isdigit(peek())) {
            advance();
        }
    }

    std::string text = source_.substr(start, pos_ - start);

    if (isFloat) {
        double val = std::stod(text);
        return Token(TokenType::FLOAT_LITERAL, text, val, static_cast<uint32_t>(line_),
                     static_cast<uint32_t>(startCol));
    }

    int64_t val = std::stoll(text);
    return Token(TokenType::INT_LITERAL, text, val, static_cast<uint32_t>(line_),
                 static_cast<uint32_t>(startCol));
}

Token Lexer::stringLiteral() {
    int start = pos_;
    int startCol = column_ - 1;
    std::string value;

    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') {
            line_++;
            column_ = 0;
        }

        char c = advance();

        // Handle escape sequences
        if (c == '\\' && !isAtEnd()) {
            char nextC = advance();
            switch (nextC) {
                case 'n':
                    value += '\n';
                    break;
                case 't':
                    value += '\t';
                    break;
                case 'r':
                    value += '\r';
                    break;
                case '\\':
                    value += '\\';
                    break;
                case '"':
                    value += '"';
                    break;
                default:
                    value += '\\';
                    value += nextC;
                    break;
            }
        } else {
            value += c;
        }
    }

    if (isAtEnd()) {
        return Token(TokenType::INVALID, "Unterminated string", line_, startCol);
    }

    advance();  // closing "
    return Token(TokenType::STRING_LITERAL, value, value, static_cast<uint32_t>(line_),
                 static_cast<uint32_t>(startCol));
}

}  // namespace aegis
