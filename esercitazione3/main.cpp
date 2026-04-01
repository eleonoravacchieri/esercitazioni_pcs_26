// #include <concept> -> solo dentro il file della classe 
// #include <numeric> -> 	//
// per compilare:
// g++ -std=c++20 main.cpp -o es3 -> serve una versione più elevata 

#include <iostream>
#include "rational.hpp"

int main() {
	int n1, d1, n2, d2;
	std::cout<<"Inserire numeratore prima frazione: \n";
	std::cin >> n1;
	std::cout<<"Inserire denominatore prima frazione: \n";
	std::cin >> d1;

	rational<int> r1(n1, d1); // creo la prima frazione

	std::cout<<"Inserire numeratore seconda frazione: \n";
	std::cin >> n2;
	std::cout<<"Inserire denominatore seconda frazione: \n";
	std::cin >> d2;

	rational<int> r2(n2, d2); // creo la seconda frazione
	
	// operazioni 
	rational<int> somma = r1 + r2;
    rational<int> prodotto = r1 * r2;
	rational<int> differenza = r1 - r2;
	rational<int> divisione = r1 / r2;
	
	
	// stampa a video 
	std::cout << "Frazione 1: " << r1 << "\n";
    std::cout << "Frazione 2: " << r2 << "\n";
	std::cout << "Somma: " << somma << "\n";
    std::cout << "Prodotto: " << prodotto << "\n";
	std::cout << "Differenza: " << differenza << "\n";
	std::cout << "Divisione: " << divisione << "\n";
	
	return 0;
}
