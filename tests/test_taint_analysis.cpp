#include <cassert>
#include <iostream>

#include "../compiler/security/taint_analysis.hpp"

void test_taint_tracking() {
    aegis::security::TaintAnalyzer analyzer;

    analyzer.markTainted("user_input", "input()", 10);
    assert(analyzer.isTainted("user_input"));

    analyzer.markSanitized("user_input");
    assert(!analyzer.isTainted("user_input"));

    std::cout << "test_taint_tracking passed\n";
}

int main() {
    test_taint_tracking();
    std::cout << "All taint analysis tests passed!\n";
    return 0;
}
