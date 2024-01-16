add_executable(demo demo-main.cc)
add_executable(minimal-example minimal-example.cc)

# Link your library to the examples
target_link_libraries(demo ${PROJECT_NAME})
target_link_libraries(minimal-example ${PROJECT_NAME})
