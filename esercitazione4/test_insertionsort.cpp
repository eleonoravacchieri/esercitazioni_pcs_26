#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Per EXIT_SUCCESS e EXIT_FAILURE
#include "sort_functions.h"
#include "randfiller.h"

int main() {
    randfiller filler;  // creo oggetto di nome filler appartenente alla classe randfiller

    // 1. Test su 100 vettori di dimensioni casuali 
    for (int i = 0; i < 100; ++i) {
        // Dimensione casuale tra 10 e 100
        std::vector<int> v(10 + (std::rand() % 90));
        
        // Riempio con numeri tra -1000 e 1000 (positivi e negativi) 
        filler.fill(v, -1000, 1000);

        insertion_sort(v); // Chiamata all'algoritmo specifico

        // Verifico se è ordinato usando la tua funzione 
        if (!is_sorted(v)) {
            std::cerr << "Errore: vettore int non ordinato da Insertion Sort all'iterazione " << i << std::endl;
            return EXIT_FAILURE; 
        }
    }

    // 2. Test su vettore di stringhe
    std::vector<std::string> v_str = {"eleonora", "emanuele", "marco", "vittoria", "giulio", "marta", "francesco", "gabriele", "chiara"};
    insertion_sort(v_str);

	// voglio un attimo vedere il vettore 
    std::cout << "Vettore stringhe ordinato da Insertion Sort: ";
    for (const auto& s : v_str) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    if (!is_sorted(v_str)) {
        std::cerr << "Errore: vettore stringhe non ordinato da Insertion Sort" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Tutti i test per Insertion Sort completati" << std::endl;
    return EXIT_SUCCESS; 
}