cmake_minimum_required(VERSION 3.0.0)
project(objects_and_pointers VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(objects_and_pointers polymorphism.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
