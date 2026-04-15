// prima: definisco is_sorted()

#pragma once
#include <vector>

template <typename T>
bool is_sorted(const std::vector<T>& vec) {
    // vettore di lunghezza 0 o con 1 solo elemento è ordinato per def
    if (vec.size() <= 1) {
        return true;
    }

    for (size_t i = 0; i < vec.size() - 1; ++i) {
		// mi fermo al penultimo elemento (vec.size() - 1)
        // se l'elemento corrente è maggiore del successivo, non è ordinato
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}


// Bubble-Sort -> confronta due elementi vicini e li scambia se è il caso 
template <typename T>
void bubble_sort(std::vector<T>& A) {
    size_t n = A.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = n - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                std::swap(A[j], A[j - 1]);
            }
        }
    }
}


// Insertion-Sort -> prende un elemento (key) dal mazzo e lo inserisce nell'ordine giusto tra quelli già ordinati 
template <typename T>
void insertion_sort(std::vector<T>& A) {
	// parto da dim = 1 perchè quello con dim = 0 è già ordinato per def 
    for (size_t j = 1; j < A.size(); ++j) { 
        T key = A[j]; // salvo elemento in una variabile 
        int i = j - 1;
        while (i >= 0 && A[i] > key) // finchè non arrivo all'inizio del vettore 
		// (i>=0)) e finchè non trovo elementi più grandi della mia key 
		// sposto a destra -> A[i+1]=A[i](!attenzione non è uno scambio, è uno slittamento per
		// creare spazio) e vado a sinistra per controllare elemento precedente 
			{
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}


// Selection-Sort -> vede tutti gli elementi che ci sono e mette quello più piccolo nella prima posizione disponibile 
template <typename T>
void selection_sort(std::vector<T>& A) {
    size_t n = A.size();
	// i -> posizione vuota 
    for (size_t i = 0; i < n - 1; ++i) 
	// fino a n-1 perchè quando scambio quello più grande sarà poi nella 
	// nell'ultima posizione, quindi quella corretta 
	{
        size_t min_idx = i; // all'inizio di ogni giro faccio finta che l'elemento in pos_format
		// i sia già il più piccolo di tutti quelli che restano -> salvo il suo indice in min_idx
        for (size_t j = i + 1; j < n; ++j) // scorro per tutto il vettore: da i+1 fino alla fine
		{
            if (A[j] < A[min_idx]) 
		// se A[j] è più piccolo di quello che avevamo salvato (A[min_idx]) aggiorniamo min_idx  
			{
                min_idx = j;
            }
        }
        std::swap(A[i], A[min_idx]);
    }
}