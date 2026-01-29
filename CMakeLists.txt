cmake_minimum_required(VERSION 3.16)
project(AdaptiveRadixTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)


# Required on Windows (prevents CRT mismatch)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_library(art
  src/ART.cpp
)

target_include_directories(art PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(art_tests
    test/Node_test.cpp
    test/ART_test.cpp
)

target_link_libraries(art_tests PRIVATE art gtest_main)


enable_testing()
add_test(NAME ARTTests COMMAND art_tests)
