add_library(aegis_lexer OBJECT
    lexer.cpp
)

target_include_directories(aegis_lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
