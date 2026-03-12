add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(semantic)
add_subdirectory(security)
add_subdirectory(codegen)

add_library(aegis_compiler STATIC
    $<TARGET_OBJECTS:aegis_lexer>
    $<TARGET_OBJECTS:aegis_parser>
    $<TARGET_OBJECTS:aegis_ast>
    $<TARGET_OBJECTS:aegis_semantic>
    $<TARGET_OBJECTS:aegis_security>
    $<TARGET_OBJECTS:aegis_codegen>
)

target_include_directories(aegis_compiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
