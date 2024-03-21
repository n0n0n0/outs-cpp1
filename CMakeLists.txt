cmake_minimum_required(VERSION 3.8)
project(lesson2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(lesson2 main.cpp hello.cpp)

target_compile_features(lesson2 PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(lesson2 PUBLIC /W4 /WX)
else()
    target_compile_options(lesson2 PUBLIC -Wall -Wextra -Werror -pedantic)
endif()