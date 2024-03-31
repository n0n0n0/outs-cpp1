# CMake - установка библиотеки в систему
Ключевая команда в CMakeLists - `install(TARGETS...)`, `install(FILES ...)` и `install(EXPORT)`
Процесс сборки файла примера:
```shell
> cd sumlib
> mkdir build && cd build
```
Теперь нужно вызвать cmake для генерации файлов?, но мы хотим указать куда устанавливать библиотеку
если не указать то будет место в ОС по умолчанию
```shell
> cmake .. -DCMAKE_INSTALL_PREFIX=/path/where/to/install
```
или
```shell
> cmake .. -DCMAKE_INSTALL_PREFIX=../../install
```
Теперь нужно собрать (--build) и установить (--target install) библиотеку.
"После того как ты соберешь установи мне эту библиотеку"
```shell
> cmake --build . --target install
```

Файл примера:
```cmake
cmake_minimum_required(VERSION 3.12)

project(SumLibrary VERSION 0.0.3)

add_library(sumLib STATIC sumLib.cpp sumLib.h)

target_compile_features(sumLib PUBLIC cxx_std_17)
set_target_properties(sumLib PROPERTIES CXX_STANDARD_REQUIRED ON)

target_include_directories(
        sumLib
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# ##############################################################################

# Installs the lib.
# You can use "cmake .. -DCMAKE_INSTALL_PREFIX=/path/where/to/install" when generating
# and "cmake --build . --target install" when building.
install(TARGETS sumLib EXPORT sumLibTargets     // тут задали "экпортное" имя, дальше с ним работаем
        LIBRARY DESTINATION lib                 // куда будут устанавливаться динамические библиотеки
                                                // пусть lib - относительный
        ARCHIVE DESTINATION lib                 // куда будут устанавливаться статические библиотеки
        INCLUDES DESTINATION include            // куда кладем заголовочные файлы
)
install(FILES sumLib.h DESTINATION include)     // описываем какие заголовочные файлы мы кладем в описанную
                                                // ранее папку include

# describe generation of cmake config file
# гененрируем конфиг файл для CMake который будет потом подключать эту нашу библиотеку
install(EXPORT sumLibTargets
        FILE sumLibConfig.cmake
        NAMESPACE SumLib::              // cmake-овские нэймспейсы, не c++
        DESTINATION lib/cmake/SumLib    // куда этот конфиг положим
)

# "cmake --build . --target package" when packaging.
# можно всё упаоквать просто в архив, можно в пакет для линукса, например (.deb) есть варианты
set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)

# ##############################################################################
#
if(MSVC)
        target_compile_options(sumLib PUBLIC /W4 /WX)
else()
        target_compile_options(sumLib PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
```

## Использование библиотеки установленной в систему
Допустим в main.cpp подключаем заголовчный файл
```cpp
#include <sumLib.h>             // в <таких скобах>
```
Ключевые слова для подключения такой библиотеки из ОС: `find_package(<name> CONFIG ...)`
Но чтобы найти в нестандартных путях можем указать опцию 
```sh
> cmake .. -DCMAKE_PREFIX_PATH=/path/where/lib
```
В CMakeLists.txt проекта, который будет использовать библиотеку тогда должно быть что-то такое:
```cmake
cmake_minimum_required(VERSION 3.12)

project(Main VERSION 0.0.6)

add_executable(mainSumLib main.cpp)

target_compile_features(mainSumLib PUBLIC cxx_std_17)
set_target_properties(mainSumLib PROPERTIES CXX_STANDARD_REQUIRED ON)

target_include_directories(
        mainSumLib
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# find_package here to find package (see the file in example root
# - it doesn't build library)
#-DCMAKE_PREFIX_PATH for custom prefix path
#cmake searches for a file <lowercasePackageName>-config.cmake
find_package(sumLib CONFIG REQUIRED)
find_package(Boost CONFIG COMPONENTS program_options REQUIRED)

target_link_libraries(mainSumLib SumLib::sumLib Boost::program_options) # вот наш namespace SumLib::

if(MSVC)
        target_compile_options(mainSumLib PUBLIC /W4 /WX)
else()
        target_compile_options(mainSumLib PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
```