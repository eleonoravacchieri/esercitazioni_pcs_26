// creo sorting.h con mergesort e quicksort 

#include <vector>
#include <iostream>
#include <algorithm> // per swap


//MERGE ausiliaria
template <typename T>
void merge(std::vector<T>& A, int p, int q, int r) {
    // n1 e n2 sono le dimensioni dei due sottovettori da fondere
    int n1 = q - p + 1;
    int n2 = r - q;  

    // inizializzo i vettori temporanei L (Left) e R (Right)
    std::vector<T> L(n1);
    std::vector<T> R(n2);

    // copio dati dal vettore originale A ai vettori temporanei 
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    // indici iniziali per i sottovettori e per il vettore fuso
    int i = 0, j = 0, k = p; 

    // fondo i vettori temporanei in A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // copio gli eventuali elementi rimanenti di L[]
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // copio gli eventuali elementi rimanenti di R[]
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// funzione principale MERGE-SORT (Ricorsiva)
template <typename T>
void merge_sort(std::vector<T>& A, int p, int r) {
    if (p < r) {
        // calcolo il punto medio per dividere il vettore 
        int q = p + (r - p) / 2;

        // ordinare la prima e la seconda metà
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);

        // fondere le due metà ordinate 
        merge(A, p, q, r);
    }
}

// per chiamarla come gli altri sort:
template <typename T>
void merge_sort(std::vector<T>& A) {
    if (A.size() > 1) {
        merge_sort(A, 0, static_cast<int>(A.size()) - 1);
    }
}


// funzione ausiliaria PARTITION (Schema di Lomuto)
template <typename T>
int partition(std::vector<T>& A, int p, int r) {
    // scelgo l'ultimo elemento come pivot
    T x = A[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++) {
        //l'elemento corrente è minore o uguale al pivot?
        if (A[j] <= x) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    // metto il pivot al punto giusto
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

// funzione principale QUICK-SORT (Ricorsiva)
template <typename T>
void quick_sort(std::vector<T>& A, int p, int r) {
    if (p < r) {
        // determino l'indice del pivot dopo la partizione
        int q = partition(A, p, r);

        // ordino ricorsivamente le due parti
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

// per chiamarla come gli altri algoritmi sort
template <typename T>
void quick_sort(std::vector<T>& A) {
    if (A.size() > 1) {
        quick_sort(A, 0, static_cast<int>(A.size()) - 1);
    }
}

// metto pure gli altri!!!
// copio uguali alla vecchia esercitazione 

template <typename T>
bool is_sorted(const std::vector<T>& vec) {
    // vettore di lunghezza 0 o con 1 solo elemento è ordinato per def
    if (vec.size() <= 1) {
        return true;
    }

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        // Se l'elemento corrente è maggiore del successivo, non è ordinato
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}


// Bubble-Sort
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


// Insertion-Sort 
template <typename T>
void insertion_sort(std::vector<T>& A) {
    for (size_t j = 1; j < A.size(); ++j) {
        T key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}


// Selection-Sort 
template <typename T>
void selection_sort(std::vector<T>& A) {
    size_t n = A.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(A[i], A[min_idx]);
    }
}


// -----------------------------------------------------
// funzioni di sorting ottimizzate 
// -----------------------------------------------------

template <typename T>
void insertion_sort_range(std::vector<T>& A, int p, int r) {
    for (int j = p + 1; j <= r; ++j) {
        T key = A[j];
        int i = j - 1;
        while (i >= p && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}


// Quick Sort ibrido 

template <typename T>
void hybrid_quick_sort(std::vector<T>& A, int p, int r, int k) {
    if (p < r) {
        // Se la dimensione del pezzo è <= k, usa Insertion Sort
        if ((r - p + 1) <= k) {
            insertion_sort_range(A, p, r);
        } else {
            // Altrimenti continua con la partizione standard
            int q = partition(A, p, r);
            hybrid_quick_sort(A, p, q - 1, k);
            hybrid_quick_sort(A, q + 1, r, k);
        }
    }
}


// Questa funzione permette di chiamare l'ibrido passando solo vettore e k
template <typename T>
void hybrid_quick_sort(std::vector<T>& A, int k) {
    if (A.size() > 1) {
        // Chiama la funzione vera usando 0 come inizio e size-1 come fine
        hybrid_quick_sort(A, 0, static_cast<int>(A.size()) - 1, k);
    }
}