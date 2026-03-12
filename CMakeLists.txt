cmake_minimum_required(VERSION 3.20)
project(Aegis 
    VERSION 0.1.0 
    DESCRIPTION "A secure systems language with built-in cybersecurity features"
    HOMEPAGE_URL "https://github.com/thtcsec/aegis"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Compiler components
add_subdirectory(compiler)
add_subdirectory(runtime)
add_subdirectory(std)
add_subdirectory(cli)

# Tests
enable_testing()
add_subdirectory(tests)
