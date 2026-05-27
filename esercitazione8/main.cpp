#include <vector> 
#include <iostream> 
#include <cmath> // per sqrt, abs, pow, quelle

#include <cstddef>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/SVD>
#include "gradiente_coniugato.h"

/** TEST METODO DEL GRADIENTE CONIUGATO 
per matrici quadrate simmetriche definite positive 
 */

// compilazione con Eigen
// g++ -std=c++17 main.cpp -I /usr/include/eigen3 -o test

int main () {
	// definisco la mia matrice 2x2 di double 
	Eigen::MatrixXd A(2,2); 
	// Xd perchè:
	// X = dimensione dinamica (“unknown size at compile time”)
    // d = double
	// MatrixXf --> f = float
	
	A(0,0) = 5.0;
	A(0,1) = 2.0;
	A(1,0) = 2.0;
	A(1,1) = 4.0;
	
	// per inizializzare vettori con Eigen
	Eigen::VectorXd b(2);
	b << 1.0, 2.0;
	Eigen::VectorXd x0(2);
	x0 << 0.0, 0.0;
	
	double tol = 10e-10;
	
	std::size_t max_iter = 1000;
	
	Eigen::VectorXd x = gradiente_coniugato(A, b, x0, tol, max_iter);
	std::cout << "Soluzione x: \n";
	std::cout << x[0] << " " << x[1] << std::endl;
	
	Eigen::VectorXd x_esatta(2);
	x_esatta << 0.0, 0.5;
	Eigen::VectorXd errore = x - x_esatta;

    std::cout << "Errore = " << errore.norm() << std::endl;

    if (errore.norm() < 1e-8)
        std::cout << "Test superato" << std::endl;
    else
        std::cout << "Test fallito" << std::endl;

    return 0;
	
}