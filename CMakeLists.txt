cmake_minimum_required(VERSION 3.20)
project(rgbmatrix C CXX)

set(CMAKE_CXX_STANDARD 17)

set(COMMON_FLAGS "-Wall -pedantic -Werror -fPIC")
set(DEBUG_FLAGS "-ggdb -g3 -O0")
set(RELEASE_FLAGS "-O3 -flto=thin")
set(CXX_SPECIFIC_FLAGS "")
set(C_SPECIFIC_FLAGS "-std=c11")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${C_SPECIFIC_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${CXX_SPECIFIC_FLAGS}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${COMMON_FLAGS} ${DEBUG_FLAGS} ${C_SPECIFIC_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COMMON_FLAGS} ${DEBUG_FLAGS} ${CXX_SPECIFIC_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${RELEASE_FLAGS} ${C_SPECIFIC_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${RELEASE_FLAGS} ${CXX_SPECIFIC_FLAGS}")

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
