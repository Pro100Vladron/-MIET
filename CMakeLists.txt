cmake_minimum_required(VERSION 3.10)

project(iomanip_tests LANGUAGES CXX)

# Установка стандарта C++17 (необходим для constexpr if)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Создаем исполняемый файл
add_executable(iomanip_tests main.cpp)

# Если нужно явно указать поддержку math (для cos), можно добавить:
target_link_libraries(iomanip_tests PRIVATE m)

# Опции компиляции (опционально, для отладки)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Добавляем флаги для более строгой проверки
target_compile_options(iomanip_tests PRIVATE
    -Wall -Wextra -Wpedantic
)

# Для Windows: если есть проблемы с math.h, можно использовать
# target_link_libraries(iomanip_tests PRIVATE winmm)

message(STATUS "Project configured for C++17")
