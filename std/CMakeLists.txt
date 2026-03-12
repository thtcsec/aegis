add_subdirectory(net)
add_subdirectory(crypto)
add_subdirectory(db)
add_subdirectory(exploit)

add_library(aegis_std STATIC
    $<TARGET_OBJECTS:aegis_std_net>
    $<TARGET_OBJECTS:aegis_std_crypto>
    $<TARGET_OBJECTS:aegis_std_db>
    $<TARGET_OBJECTS:aegis_std_exploit>
)
