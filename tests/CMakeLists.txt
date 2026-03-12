# Test framework setup

# Lexer test
add_executable(test_lexer test_lexer.cpp)
target_link_libraries(test_lexer PRIVATE aegis_compiler)
add_test(NAME LexerTests COMMAND test_lexer)

# Taint analysis test
add_executable(test_taint_analysis test_taint_analysis.cpp)
target_link_libraries(test_taint_analysis PRIVATE aegis_compiler)
add_test(NAME TaintAnalysisTests COMMAND test_taint_analysis)

# SQL checker test
add_executable(test_sql_checker test_sql_checker.cpp)
target_link_libraries(test_sql_checker PRIVATE aegis_compiler)
add_test(NAME SqlCheckerTests COMMAND test_sql_checker)

# Type system test
add_executable(test_type_system test_type_system.cpp)
target_link_libraries(test_type_system PRIVATE aegis_compiler)
add_test(NAME TypeSystemTests COMMAND test_type_system)
