## Плагины:
1. c\c++ от microsoft
2. c\c++ extension pack от microsoft
3. Clang-format - для выбора форматтера (стиля)
	точное название в плагинах vscode: "clangformat" без дефиса
	после установки хотим форматировать документ: правой кнопкой внутри текстового редактора vscode - Format Document
	дает выбрать первый раз (может потом тоже) - выбираем ClangFormat
	выбираем, но по умолчанию в винде нет самой программы clangformat его надо где-то скачать и поставить
	настроить стиль можно создав файл .clang-format (через file - new) в корне проекта
4. Clang-tidy (вроде не плагин, уже есть в vscode) - анализатор кода
	настройки в File - preferences - settings
	в поиске набираем "clang tidy"
	там ищем .. > Code analysis > Clang Tidy > Checks: Enabled
	там добавляем нужные из кучи возможных проверок, а именно:
		cppcoreguidelines-*
		и modernize-*
5. CMake (подсветка синтаксиса и т.п.) и CMake Tools 2 плагина
> пока ставил другие плагины как-то CMake и Cmake Tools сами установились в vscode
	После установки и перезапуска vscode появится в обозревателе файлов внутри vscode контекстное меню новое при нажатии правой клавишей
	мыши на CMakeLists.txt

## Горячие клавиши

## Новый проект CMake:
1. создаем папку
2. vscode - open folder
3. (vscode) ctrl + shift + p	-	type "cmake" 	- CMake: QuickStart
	3.1 выбор набора инструментов (выпадает) - GCC (есть и gcc (gnu C compiler) и g++ для C++)
	3.2 поиск makefike - жмем Esc(нету, само создаст)
	3.3 вводим название проекта - fibo
	3.4 язык проекта - С++
	3.5 тип проекта - executable (не либа)
в результате сгенерится CMakeLists.txt:

cmake_minimum_required(VERSION 3.0.0)
project(fibo VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(fibo main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


можно упростить до:
cmake_minimum_required(VERSION 3.0.0)
project(fibo VERSION 0.1.0)

add_executable(fibo main.cpp)
