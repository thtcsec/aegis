#include <cassert>
#include <iostream>

#include "../compiler/security/sql_checker.hpp"

void test_sql_injection_detection() {
    aegis::security::SQLChecker checker;

    // Vulnerable query
    auto vuln1 =
        checker.analyze(std::string("SELECT * FROM users WHERE name = ") + "user_input", true);
    assert(vuln1.vulnerable);

    // Safe parameterized query
    auto vuln2 = checker.analyze("SELECT * FROM users WHERE name = ?", true);
    assert(!vuln2.vulnerable);

    std::cout << "test_sql_injection_detection passed\n";
}

int main() {
    test_sql_injection_detection();
    std::cout << "All SQL checker tests passed!\n";
    return 0;
}
