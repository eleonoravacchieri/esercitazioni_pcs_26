cmake_minimum_required(VERSION 3.20)
project(esercitazione8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

find_package(Eigen3 CONFIG REQUIRED)
list(APPEND libraries_list PUBLIC Eigen3::Eigen)

set(SOURCES circuiti.cpp graphs.hpp graph_visit.hpp contenitori.hpp cicli_fondamentali.hpp metodi_correnti.hpp DePina.hpp)
add_executable(programma ${SOURCES})

target_link_libraries(programma ${libraries_list})