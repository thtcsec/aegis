add_library(aegis_codegen OBJECT
    llvm_codegen.cpp
    ir_builder.cpp
)

target_include_directories(aegis_codegen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(aegis_codegen PUBLIC ${LLVM_LIBRARIES})
