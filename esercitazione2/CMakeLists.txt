# In un file CMakeLists.txt si deve innanzitutto specificare la versione
# minima di CMake necessaria per compilare il progetto. Nel nostro caso
# specifichiamo 3.20
cmake_minimum_required(VERSION 3.20)

# Successivamente il file CMakeLists.txt deve specificare il nome del
# progetto software
project(esercitazione2) 

# In seguito dobbiamo specificare la versione di C++ che vogliamo
# sia usata per la compilazione. Utilizziamo C++20, ovvero la versione
# standardizzata nel 2020
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# A lezione abbiamo visto che possiamo specificare al compilatore delle
# opzioni per incrementare il livello di warning, in modo da avvisarci
# se nel programma vengono riscontrati dei costrutti potenzialmente
# problematici. Le opzioni devono essere aggiunte alla variabile di CMake
# chiamata CMAKE_CXX_FLAGS nel seguente modo
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

# A questo punto siamo pronti a dichiarare l'eseguibile che vogliamo produrre.
# Con il comando add_executable chiediamo di creare un eseguibile chiamato
# passo3 a partire dai file sorgente passo3_main.cpp e passo3_functions.cpp.
# In qualche modo questo genererà le seguenti chiamate al compilatore
#
#    g++ -o passo3_main.o passo3_main.cpp
#    g++ -o passo3_functions.o passo3_functions.cpp
#    g++ -o passo3 passo3_main.o passo3_functions.o
#
# La prima chiamata compila passo3_main.cpp e produce il codice oggetto
# passo3_main.o. La seconda chiamata fa la stessa cosa per passo3_functions.# L'ultima chiamata esegue il collegamento dei due file oggetto producendo
# l'eseguibile passo3
add_executable(prog1 pos_memoria.cpp)
add_executable(prog2 algoritmi2.cpp)

