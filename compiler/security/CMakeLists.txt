add_library(aegis_security OBJECT
    taint_analysis.cpp
    sql_checker.cpp
    vuln_detector.cpp
)

target_include_directories(aegis_security PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
