#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Per EXIT_SUCCESS e EXIT_FAILURE
#include "sorting.h"
#include "randfiller.h"

int main() {
    randfiller filler; // creo oggetto di nome filler appartenente alla classe randfiller

    // 1. Test su 100 vettori di dimensioni casuali
    for (int i = 0; i < 100; ++i) {
        // Dimensione casuale tra 10 e 100
        // std::rand() genera un numero enorme, % 90 prende il resto (0-89), + 10 porta il range a 10-99
        std::vector<int> v(10 + (std::rand() % 90));
        
        // Riempio con numeri tra -1000 e 1000
        filler.fill(v, -1000, 1000);

        merge_sort(v); // Chiamata al nuovo algoritmo Merge Sort

        // Verifico se è ordinato usando la funzione is_sorted in sorting.h
        if (!is_sorted(v)) {
            std::cerr << "Errore: vettore int non ordinato da Merge Sort all'iterazione " << i << std::endl;
            return EXIT_FAILURE; 
        }
    }

    // 2. Test su vettore di stringhe 
    std::vector<std::string> v_str = {"eleonora", "emanuele", "marco", "vittoria", "giulio", "marta", "francesco", "gabriele", "chiara"};
    merge_sort(v_str);

    // Visualizzo il vettore di stringhe ordinato
    std::cout << "Vettore stringhe ordinato da Merge Sort: ";
    for (const auto& s : v_str) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    if (!is_sorted(v_str)) {
        std::cerr << "Errore: vettore stringhe non ordinato da Merge Sort" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Tutti i test per Merge Sort completati con successo!" << std::endl;
    return EXIT_SUCCESS; 
}