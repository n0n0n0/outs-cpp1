# CMake - статические и динамические библиотеки
Строчки в CMakeLists в проекте со статической и динамической библиотеками
```cmake
cmake_minimum_required(VERSION 3.12)

project(Example3 VERSION 0.0.2)

add_subdirectory(lib)               // lib - название папки, там должен быть CMakeLists файл библиотеки
add_subdirectory(dynamic_lib)
add_subdirectory(src)               // в папке src у нас типа исполняемый файл

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    #Global flag to cause add_library() to create shared libraries if on
    set(BUILD_SHARED_LIBS TRUE)     
endif()
```
Тогда в файле `./lib/CMakeLists.txt` будет примерно следующее:
```cmake
cmake_minimum_required(VERSION 3.12)

project(Library VERSION 0.0.2)

add_library(lib STATIC lib.cpp lib.h)           // ключевое слово STATIC

target_compile_features(lib PUBLIC cxx_std_17)
set_target_properties(lib PROPERTIES CXX_STANDARD_REQUIRED ON)

target_include_directories(
        lib
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE
        private/
)
```
В файле `./dynamic_lib/CMakeLists.txt` будет примерно так
```cmake
cmake_minimum_required(VERSION 3.12)

project(DynamicLibrary VERSION 0.0.2)

add_library(dynamic_lib SHARED dynamic_lib.cpp)     // ключевое слово SHARED

target_include_directories(dynamic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(dynamic_lib PUBLIC cxx_std_17)
set_target_properties(dynamic_lib PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(dynamic_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
```

В файле `./src/CMakeLists.txt` будет так:
```cmake
cmake_minimum_required(VERSION 3.5)

project(Main VERSION 0.0.5)

add_executable(mainLib main.cpp)

target_compile_features(mainLib PUBLIC cxx_std_17)
set_target_properties(mainLib PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(mainLib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_include_directories(
        mainLib
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(mainLib lib dynamic_lib)      // собственно подключение библиотек
```
