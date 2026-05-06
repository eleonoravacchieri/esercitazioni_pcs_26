cmake_minimum_required(VERSION 3.20)
project(esercitazione5) # Aggiornato il nome del progetto

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# 1. Target per l'eseguibile principale (Misurazione Tempi e ricerca soglia)
# Assicurati che il file si chiami measure_sorts.cpp o main.cpp (cambia se necessario)
set(SRC_measure_sorts timecounter.cpp main.cpp) 
add_executable(measure_sorts ${SRC_measure_sorts})

# 2. Target per i test unitari degli algoritmi precedenti (Esercitazione 4)
add_executable(test_bubblesort test_bubblesort.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

add_executable(test_insertionsort test_insertionsort.cpp)
add_test(NAME insertionsort COMMAND test_insertionsort)

add_executable(test_selectionsort test_selectionsort.cpp)
add_test(NAME selectionsort COMMAND test_selectionsort)

# 3. Target per i nuovi test unitari (Esercitazione 5)
add_executable(test_mergesort test_mergesort.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

# Abilitazione dei test per usare 'ctest'
enable_testing()