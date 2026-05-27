#pragma once 

// #include <vector> 
#include <iostream> 
#include <cmath> // per sqrt, abs, pow, quelle
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Eigen/Eigen>
#include <cstddef>

using namespace std;

/** METODO DEL GRADIENTE CONIUGATO 
per matrici quadrate simmetriche definite positive 
 */

// template <typename T> <-- tolgo il template perchè Xd è già un double 
Eigen::VectorXd gradiente_coniugato(
							const Eigen::MatrixXd& A, 
							const Eigen::VectorXd& b, 
							const Eigen::VectorXd& x0,
							double tol, // per capire quando fermare l'algoritmo
// inoltre se T=double, tol è double 
// se T=float, tol è float  					  
							std::size_t max_iter) // evito cicli infiniti se il metodo non converge 
{
	// inizializzo
	Eigen::VectorXd x = x0;
	Eigen::VectorXd r = b-A*x;
	Eigen::VectorXd p = r;
	
	for (std::size_t k=0; k < max_iter; ++k)	
	{
		if (r.norm() < tol) //devo mettere r.norm() e non norm(r) perchè sono su Eigen
			break;
		
		Eigen::VectorXd Ap = A*p;
		
		// alpha:
		double alpha = p.dot(r)/p.dot(Ap); // attenzione alla sintassi di Eigen
		// x:
		x = x + alpha*p;
		// r nuovo:
		Eigen::VectorXd r_new = r - alpha*Ap;
		// beta:
		double beta = p.dot(A*r_new)/p.dot(Ap);
		// p:
		p = r_new - beta*p;
		
		r = r_new;
	}
	
	return x;

}

