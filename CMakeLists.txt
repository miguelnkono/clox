cmake_minimum_required(VERSION 4.0)
project(Lox C)

set(CMAKE_C_STANDARD 23)

add_executable(Lox main.c
        test_my.c
        common.h
        chunk.h
        chunk.c
        memory.c
        memory.h
        debug.h
        debug.c)

# here we are downloading the check library for doing unit tests.
include(FetchContent)
FetchContent_Declare(
        check
        GIT_REPOSITORY https://github.com/libcheck/check.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(check)

add_executable(LoxTests test_my.c)
target_link_libraries(LoxTests check)
