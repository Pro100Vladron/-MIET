cmake_minimum_required(VERSION 3.14)
project(type_map_lab)

# Use FetchContent to get Catch2
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.0
)

FetchContent_MakeAvailable(Catch2)

# Create interface library for type_map
add_library(type_map INTERFACE)
target_include_directories(type_map INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add tests - используем Catch2WithMain для автоматического создания main()
add_executable(tests_type_map tests/type_map.cpp)
target_link_libraries(tests_type_map type_map Catch2::Catch2WithMain)

# Для catch_discover_tests нужно подключить модуль
include(CTest)
if(CATCH2_WITH_PREFIX)
  include(${CATCH2_SOURCE_DIR}/extras/Catch.cmake)
  catch_discover_tests(tests_type_map)
endif()