cmake_minimum_required(VERSION 3.10)

project(clox C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
  clox.c
  chunk.c
  chunk.h
  memory.c
  memory.h
  common.c
  common.h
  debug.c
  debug.h
  value.c
  value.h
  vm.c
  vm.h
)

set_property(TARGET clox PROPERTY C_STANDARD 11)
