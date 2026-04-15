#include <iostream>
#include <vector>
#include <algorithm>
#include "sort_functions.h"
#include "timecounter.h"
#include "randfiller.h"

int main() {
    randfiller filler; // creo oggetto di nome filler appartenente alla classe randfiller
    timecounter timer; // creo oggetto di nome timer appartenente alla classe timecounter

    // Intestazione 
    std::cout << "Dimensione\tBubble\tInsertion\tSelection\tstd::sort" << std::endl;

    // Ciclo che raddoppia la dimensione n: 4, 8, 16... fino a 8192
    for (int n = 4; n <= 8192; n *= 2) {
        
        // Creiamo il vettore disordinato di partenza
        std::vector<int> base_vec(n);
        filler.fill(base_vec, -10000, 10000);

        std::cout << n << "\t";

        // 1. Misura Bubble Sort
        std::vector<int> v1 = base_vec;
        timer.tic();
        bubble_sort(v1);
        std::cout << timer.toc() << "\t";

        // 2. Misura Insertion Sort
        std::vector<int> v2 = base_vec;
        timer.tic();
        insertion_sort(v2);
        std::cout << timer.toc() << "\t";

        // 3. Misura Selection Sort
        std::vector<int> v3 = base_vec;
        timer.tic();
        selection_sort(v3);
        std::cout << timer.toc() << "\t";

        // 4. Misura std::sort (il riferimento di sistema)
        std::vector<int> v4 = base_vec;
        timer.tic();
        std::sort(v4.begin(), v4.end());
        std::cout << timer.toc() << std::endl;
    }

    return 0;
}