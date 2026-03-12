add_library(aegis_semantic OBJECT
    type_checker.cpp
    symbol_table.cpp
)

target_include_directories(aegis_semantic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
