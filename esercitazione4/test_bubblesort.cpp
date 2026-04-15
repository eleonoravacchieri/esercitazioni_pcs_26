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
        // Dimensione casuale tra 10 e 100 (esempio)
        std::vector<int> v(10 + (std::rand() % 90));
		
		// ALLORA std::rand() genera un numero a caso enorme (tipo 468462)
		// % 90 -> prendo quel numero, lo divido per 90 ma tengo solo il resto 
        
        // Riempio con numeri tra -1000 e 1000 
        filler.fill(v, -1000, 1000);

        bubble_sort(v);

        // Verifico se è ordinato usando la tua funzione
        if (!is_sorted(v)) {
            std::cerr << "Errore: vettore int non ordinato all'iterazione " << i << std::endl;
            return EXIT_FAILURE; 
        }
    }

    // 2. Test su vettore di stringhe 
    std::vector<std::string> v_str = {"eleonora", "emanuele", "marco", "vittoria", "giulio", "marta", "francesco", "gabriele", "chiara"};
	bubble_sort(v_str);
	// voglio vedere il mio vettore ordinato 
    std::cout << "Vettore ordinato da Bubble Sort: ";
	for (const auto& s : v_str) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
    if (!is_sorted(v_str)) {
        std::cerr << "Errore: vettore stringhe non ordinato" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Tutti i test per Bubble Sort completati" << std::endl;
    return EXIT_SUCCESS; 
	
}