cmake_minimum_required(VERSION 2.6)
project(game2048)

add_executable(game2048 main.cpp)

install(TARGETS game2048 RUNTIME DESTINATION bin)
