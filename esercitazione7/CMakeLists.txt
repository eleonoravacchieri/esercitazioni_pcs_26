cmake_minimum_required(VERSION 3.20)

project(esercitazione9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# flag per beccare subito errori comuni
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Definisco l'eseguibile
add_executable(test_visit_algorithms main.cpp)

# Abilitazione dei test per usare 'ctest'
enable_testing()
add_test(NAME run_visit_tests COMMAND test_visit_algorithms)

