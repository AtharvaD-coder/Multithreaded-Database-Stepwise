cmake_minimum_required(VERSION 3.14)
project(multithreaded_db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the main executable
add_executable(multithreaded_db main.cpp)

# Add GoogleTest as a submodule
add_subdirectory(libs/gtest)

# Include directories
target_include_directories(multithreaded_db PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/libs/concurrentqueue
)

# Link necessary libraries for main executable
target_link_libraries(multithreaded_db gtest gtest_main)

# Add test executable
add_executable(run_tests tests/database.cpp)

# Link libraries for tests
target_link_libraries(run_tests gtest gtest_main)

# Include directories for tests
target_include_directories(run_tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/libs/concurrentqueue
)
