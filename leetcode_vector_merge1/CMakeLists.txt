cmake_minimum_required(VERSION 3.0.0)
project(leetvec1 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(leetvec1 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
