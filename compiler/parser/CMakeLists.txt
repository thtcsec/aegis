add_library(aegis_parser OBJECT
    parser.cpp
)

target_include_directories(aegis_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
