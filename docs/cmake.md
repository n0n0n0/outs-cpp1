# CMake

Создаем в папке с проектом файл CMakeLists.txt	(vscode - Ctrl + Alt + P -> type "CMake: QuickStart" - визард простой по настройке проекта под CMake
`build -B build`	- собираем проект в папку build (точно что делает на этом этапе пока не известно
`build --build build` 	- собираем исполняемый файл (из объектных файлов собранных ранее?)

Создать exe-шник из проекта:
```
add_executable(
	<название ехе-ника>
	file.cpp
	file2.cpp 
	...
)
```
### Компиляция без CMake
> g++ -c main.cpp			-> получаем main.o объектный файл
> g++ main.o -o hello		-> получаем ехе-файл в директории с названием hello.exe

Можно добавлять в проект подпроекты (поддиректории) в которых тоже должен быть файл CMakeLists.txt
add_subdirectory(static_library)	где static_library - название папки в папке проекта

## Статические библиотеки
> набор объектных файлов (.o, .obj) в архиве (натурально, можно распаковать 7-zip) с заголовочными файлами", 
> в винде (а может и линухе?) с расширением .lib
> кодовая база статичной библиотеки зашивается прям в exe-файл

В CMake проект со статической библиотекой:
project(04.linkage)

```
add_library(
	datetime	<- название библиотеки (выходного файла)

	STATIC		<- тип библиотеки (может быть STATIC и SHARED)

	datetime.cpp
	datetime.h
	# ... 
)
```

## Динамические библиотеки
> набор объектных файлов (.o, .obj) скомпилированные и слинкованные в по сути исполняемый файл без функции main
> в винде - .dll (dynamic load library) в линуксе - .so (shared objects)
> такие файлы не зашиваются в exe, а идут отдельными файлами подключаются в runtime (после запуска программы)
> также нужны заголовочные файлы для работы с ней

В CMake проект с динамической библиотекой:
project(04.linkage)

```
add_library(
	datetime	<- название библиотеки (выходного файла)

	SHARED		<- тип библиотеки (может быть STATIC и SHARED)

	datetime.cpp
	datetime.h
	# ... 
)
```

## Подключение библиотек в проект CMake:
```
target_link_library {
	test_app_datetime		# название таргета = екзешника, который указан в проекте как add_executable
	PRIVATE					# тип линковки, можно PUBLIC тогда другие библиотеки будут знать эту
	datetime				# название библиотеки Cmake узнает об этом через add_subdirectory(папка со статичной либой) 
							# там в CMakeLists add_library(<первый параметр - название библиотеки>, ...)
}
```