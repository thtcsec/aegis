add_subdirectory(memory)
add_subdirectory(sandbox)
add_subdirectory(capability)

add_library(aegis_runtime STATIC
    $<TARGET_OBJECTS:aegis_memory>
    $<TARGET_OBJECTS:aegis_sandbox>
    $<TARGET_OBJECTS:aegis_capability>
)
