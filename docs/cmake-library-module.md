# CMake - подключение "модульной" библиотеки find_package(name MODULE ...)
Библиотека может не иметь, например, cmake - конфига, а будет просто набор объектных/исполняемых и заголовочных файлов, как это подключить к проекту?
Нужно прописать `find_package(sumLib MODULE REQUIRED)` - это означает что либа "sumLib" конфига cmake в себе не содержит (ключевое слово MODULE) и мы сами сделаем этот конфиг.
Мы дописываем в наш проект FindSumLib.cmake файл с конфигом формат имени файла Find<LibName>.cmake
Ниже пример CMakeLists файла с таким типом подключения модуля
```cmake
cmake_minimum_required(VERSION 3.12)

project(example6 VERSION 0.0.6)

configure_file(
        config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_executable(mainSumExtLib main.cpp)
target_compile_features(mainSumExtLib PUBLIC cxx_std_17)
set_target_properties(mainSumExtLib PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
        mainSumExtLib
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

if(MSVC)
        target_compile_options(mainSumExtLib PUBLIC /W4 /WX)
else()
        target_compile_options(mainSumExtLib PUBLIC -Wall -Wextra -Werror -pedantic)
endif()

# We're adding a new path (our path) to the path list where CMake searches
# modules for "find_package(... MODULE ...)":
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# find_package here to find library by module
# (prev. example was CONFIG - "by config")
#cmake searches for a file Find<PackageName>.cmake
find_package(sumLib MODULE REQUIRED)
find_package(PNG MODULE REQUIRED)

message("!!!! SUMLIB_INCLUDE_DIRS = ${SUMLIB_INCLUDE_DIRS}")
message("!!!! SUMLIB_LIB = ${SUMLIB_LIB}")

target_include_directories(mainSumExtLib PRIVATE ${SUMLIB_INCLUDE_DIRS})
target_link_libraries(mainSumExtLib ${SUMLIB_LIB} PNG::PNG)
```

Что интересного в файле конфига cmake есть?
1. cmake может получать переменные окружения с помощью выражения `"$ENV{SUMLIBDIR}"`  
Для macOS можно задать переменную как
```shell
export SUMLIBDIR=/path/to/dir
```

Пример файла FindSumLib.cmake
```cmake
# Find module for the sumLib
# Exports
# SUMLIB_INCLUDE_DIRS - for include folder path
# SUMLIB_LIB - for lib path
# This is the directory where the sumLib is located.
# By default SUMLIBDIR environment variable value is taken.
set(SUMLIB_ROOT
    "$ENV{SUMLIBDIR}"
    CACHE PATH "sumLib root directory.")

# Look for headers.
find_path(SUMLIB_INCLUDE_DIRS
    NAMES sumLib.h
    HINTS $ENV{SUMLIBDIR}
    PATHS ${SUMLIB_ROOT}
    PATH_SUFFIXES include
)

message(status $ENV{SUMLIBDIR})
message(status ${SUMLIB_ROOT})

# Not just "find path or file", it find_library - file name/path depends on OS.
find_library(SUMLIB_LIB
    NAMES sumLib
    HINTS SUMLIB_INCLUDE_DIRS
    HINTS $ENV{SUMLIBDIR}
    PATHS ${SUMLIB_ROOT}
    PATH_SUFFIXES lib
    NO_DEFAULT_PATH
)

# Support the REQUIRED and QUIET arguments, and set SUMLIB_FOUND if found.
# https://cmake.org/cmake/help/latest/module/FindPackageHandleStandardArgs.html
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(sumLib DEFAULT_MSG
    SUMLIB_LIB
    SUMLIB_INCLUDE_DIRS)

```