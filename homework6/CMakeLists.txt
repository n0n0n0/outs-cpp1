cmake_minimum_required(VERSION 3.8)
project(hw6 VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

add_executable(hw6 
    main.cpp
)

target_compile_features(hw6 PUBLIC cxx_std_17)

# if (MSVC)
#     target_compile_options(hw6 PUBLIC /W4 /WX)
# else()
#     target_compile_options(hw6 PUBLIC -Wall -Wextra -Werror -pedantic)
# endif()