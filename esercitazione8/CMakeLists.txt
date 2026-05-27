cmake_minimum_required(VERSION 3.20)

project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# flag per beccare subito errori comuni
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# per far vedere Eigen
include_directories(/usr/include/eigen3)

# Definisco l'eseguibile
add_executable(gradiente_coniugato main.cpp)

# Abilitazione dei test per usare 'ctest'
enable_testing()
add_test(NAME test_gradiente COMMAND gradiente_coniugato)

