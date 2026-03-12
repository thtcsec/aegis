#include <cassert>
#include <iostream>

#include "../compiler/lexer/lexer.hpp"

void test_basic_tokens() {
    aegis::Lexer lexer("fn main() { }");

    auto t1 = lexer.nextToken();
    assert(t1.type == aegis::TokenType::FN);

    auto t2 = lexer.nextToken();
    assert(t2.type == aegis::TokenType::IDENTIFIER);
    assert(t2.lexeme == "main");

    std::cout << "test_basic_tokens passed\n";
}

int main() {
    test_basic_tokens();
    std::cout << "All lexer tests passed!\n";
    return 0;
}
