cmake_minimum_required(VERSION 3.14)
project(strided_range_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(Catch2)

find_package(Boost REQUIRED)

add_library(strided_range INTERFACE)
target_include_directories(strided_range INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(strided_range INTERFACE Boost::boost)

add_executable(tests_strided_range tests/strided_range.cpp)
target_link_libraries(tests_strided_range PRIVATE strided_range Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests_strided_range)
