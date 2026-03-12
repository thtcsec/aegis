add_library(aegis_ast OBJECT
    ast.cpp
)

target_include_directories(aegis_ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
