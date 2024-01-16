cmake_minimum_required(VERSION 3.12)
project(rgbmatrix)

# Set C++ standard (optional, adjust as needed)
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "lib/*.cc" "lib/*.c")

# Create a library
add_library(${PROJECT_NAME} ${SOURCES})

# Link pthread library
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Install headers
file(GLOB HEADERS "include/*.h")
install(FILES ${HEADERS} DESTINATION include)

# Install library
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

add_subdirectory(examples-api-use)
