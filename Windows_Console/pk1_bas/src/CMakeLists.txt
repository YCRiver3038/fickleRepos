cmake_minimum_required(VERSION 3.0)
project(pk1_bas C)

add_library(mods STATIC mods.c)
add_executable(pk1_bas.out main.c)
target_link_libraries(pk1_bas.out mods)

add_executable(dispChars.out dispChars.c)
