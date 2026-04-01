#pragma once
#include <concepts> 
#include <numeric> // per funzione gcd

#define RATIONAL

template<typename I> requires std::integral<I>
class rational {
	
	I num_;
	I den_;
	bool is_nan;
	bool is_inf;
	// DEFINIZIONE di simplify: fuori dal public, una volta sola
    void simplify() {
        if (is_nan || is_inf) return;
        I common = std::gcd(num_, den_);
        num_ /= common;
        den_ /= common;
        if (den_ < 0) { num_ = -num_; den_ = -den_; }
    }
	
public: 
	// costruttore di default
	rational() : num_(I{0.0}), den_(I{1.0}), is_nan(false), is_inf(false) {}

	//costruttore user-defined
	rational(const I& pnum, const I& pden) : num_(pnum), den_(pden) {
		
		// inizializzo booleani anche nel costruttore
		is_nan = (den_ == 0 && num_ == 0);
		is_inf = (den_ == 0 && num_ !=0);
		
		// a. CASO INFINITO 1/0:
		if (pden == 0) {
			if (pnum != 0) { // <- se il num è diverso da zero 
			//infinito in forma standard 
				num_ = I{1};
				den_ = I{0};
				is_inf = true; //uso booleano per l'infinito
				is_nan = false; 
			}
			else { // <- se anche il num è zero 
			// b. CASO NAN 0/0:
				num_=I{0};
				den_=I{0};
				is_nan = true ;
				is_inf = false;
			}
			} else {
			// c. CASO NORMALE a/b
				is_inf = false;
				is_nan = false;
				simplify(); // richiamo alla funzione sopra definita  
			}
		
	}
	
	// metodi per leggere i valori num e den (devono stare fuori dal costruttore) 
	I num() const {return num_;}
	I den() const {return den_;}
	bool isnan() const { return is_nan; }
	bool isinf() const { return is_inf; }
	
	// 1. SOMMA
	
	// implementazione canonica dell'incremento +=
	//+= prende i valori di other, li somma ai valori dell'oggetto attuale (this) 
	//e salva il risultato in this 
	
	rational& operator+=(const rational<I>& other) {
		// 1. Gestione stati speciali (Propagazione) 
		if (this->is_nan || other.is_nan) {
            this->is_nan = true;
            this->is_inf = false;
            return *this;
		}
		if (this->is_inf || other.is_inf) {
            this->is_inf = true;
            return *this; // !!! *this -> riferimento all'oggetto 
        }
		// 2. calcolo matematico 
		this->num_ = (num_ * other.den_) + (other.num_ * den_);
		this->den_ = den_ * other.den_;
		this->simplify();
		return *this; // Restituisce l'oggetto modificato
	}
	// Implementazione standard che sfrutta il +=
	rational operator+(const rational<I>& other) const {
		rational result = *this; // 1. Faccio una copia dell'oggetto attuale
		result += other;         // 2. Uso il += sulla copia
		return result;           // 3. Restituisco la copia (r1 e other sono salvi)
	}

	// 2. DIFFERENZA 
	
	rational& operator-=(const rational<I>& other) {
		// 1. Gestione stati speciali (Propagazione) 
		if (this->is_nan || other.is_nan) {
            this->is_nan = true;
            this->is_inf = false;
            return *this;
		}
		if (this->is_inf || other.is_inf) {
            this->is_nan = true; //inf - inf è una forma indeterminata => is_nan
			this->is_inf = false;
            return *this;
        }
		// 2. calcolo matematico 
		this->num_ = (num_ * other.den_) - (other.num_ * den_);
		this->den_ = den_ * other.den_;
		this->simplify();
		return *this; // Restituisce l'oggetto modificato
	}
	// Implementazione standard che sfrutta il -=
	rational operator-(const rational<I>& other) const {
		rational result = *this; // 1. Faccio una copia dell'oggetto attuale
		result -= other;         // 2. Uso il -= sulla copia
		return result;           // 3. Restituisco la copia (r1 e other sono salvi)
	}
	
	// 3. MOLTIPLICAZIONE
	
	rational& operator*=(const rational<I>& other) {
		// 1. Gestione stati speciali (Propagazione) 
		if (this->is_nan || other.is_nan) {
            this->is_nan = true;
            this->is_inf = false;
            return *this;
		}
		if (this->is_inf || other.is_inf) {
            this->is_nan = false; 
			this->is_inf = true;
            return *this;
		}
		// 2. calcolo matematico 
		this->num_ = num_ * other.num_;
		this->den_ = den_ * other.den_;
		this->simplify();
		return *this; // Restituisce l'oggetto modificato
	}
	rational operator*(const rational<I>& other) {
		rational result = *this;	// 1. Faccio una copia dell'oggetto attuale 
		result *= other; 		// 2. uso il *= sulla copia 
		return result; 			// 3. Restituisco la copia (r1 e other sono salvi
		
	}	
	
	// 4. DIVISIONE 
	rational& operator/=(const rational<I> other) {
		if (this->is_nan || other.is_nan) {
			this->is_nan = true;
			this->is_inf = false;
			return *this;
		}
		
		I new_num = num_ * other.den_;
        I new_den = den_ * other.num_;
        
        num_ = new_num;
        den_ = new_den;

        // Aggiorno gli stati se il nuovo denominatore è zero
        is_nan = (den_ == 0 && num_ == 0);
        is_inf = (den_ == 0 && num_ != 0);

        this->simplify();
        return *this;
	}
	rational operator/(const rational<I>& other) {
		rational result = *this;	// 1. Faccio una copia dell'oggetto attuale 
		result /= other; 			// 2. uso il /= sulla copia 
		return result; 				// 3. Restituisco la copia (r1 e other sono salvi
		
	}
	
};


// PER LA STAMPA 

template<typename I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) {
    if (r.isnan()) { 
        os << "NaN";
    } else if (r.isinf()) {
        os << "Inf";
    } else {
        os << r.num() << "/" << r.den();
    }
    return os;
}



