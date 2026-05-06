#include <vector>
#include <iostream>
#include <algorithm> 
#include <iomanip> 
#include <string>
#include "sorting.h"
#include "randfiller.h"
#include "timecounter.h"

int main() {
    randfiller filler;
    timecounter timer;
    int num_prove = 100; // Dichiarata qui per usarla ovunque
    
    std::cout << std::left << std::setw(12) << "Dim(N)" 
              << std::setw(15) << "Insertion" 
              << std::setw(15) << "MergeSort" 
              << std::setw(15) << "QuickSort" 
              << "std::sort" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    // Variabile per salvare l'ultimo set di dati per i test successivi
    std::vector<std::vector<int>> last_base;

    for (int n = 4; n <= 8192; n *= 2) {
        std::vector<std::vector<int>> base(num_prove, std::vector<int>(n));
        for(int i=0; i<num_prove; ++i) filler.fill(base[i], -1000, 1000);
        
        last_base = base; // Salviamo l'ultima configurazione (N=8192)

        double t_ins = 0;
        if (n <= 2048) {
            auto v = base;
            timer.tic();
            for(int i=0; i<num_prove; ++i) insertion_sort(v[i]);
            t_ins = timer.toc() / num_prove;
        }

        auto v_m = base;
        timer.tic();
        for(int i=0; i<num_prove; ++i) merge_sort(v_m[i]);
        double t_merge = timer.toc() / num_prove;

        auto v_q = base;
        timer.tic();
        for(int i=0; i<num_prove; ++i) quick_sort(v_q[i]);
        double t_quick = timer.toc() / num_prove;

        auto v_s = base;
        timer.tic();
        for(int i=0; i<num_prove; ++i) std::sort(v_s[i].begin(), v_s[i].end());
        double t_std = timer.toc() / num_prove;

        std::cout << std::left << std::setw(12) << n 
                  << std::setw(15) << t_ins 
                  << std::setw(15) << t_merge 
                  << std::setw(15) << t_quick 
                  << t_std << std::endl;
    }

    // --- Ricerca soglia k (N=1000) ---
    int N_test = 1000;
    std::vector<std::vector<int>> base_data(num_prove, std::vector<int>(N_test));
    for(int i=0; i<num_prove; ++i) filler.fill(base_data[i], -1000, 1000);

    std::cout << "\nRicerca soglia k (N=1000):" << std::endl;
    std::cout << "k\tTempo Medio" << std::endl;

    for (int k : {1, 5, 10, 15, 20, 30, 50}) {
        auto v_hybrid = base_data;
        timer.tic();
        for(int i=0; i<num_prove; ++i) hybrid_quick_sort(v_hybrid[i], k);
        double t_hybrid = timer.toc() / num_prove;
        std::cout << k << "\t" << t_hybrid << std::endl;
    }

    // --- Ricerca soglia k ottimale (N=8192) ---
    std::cout << "\nRicerca soglia k ottimale (N=8192):" << std::endl;
    for (int k : {1, 10, 20, 30, 40, 50}) {
        auto v_hybrid = last_base; 
        timer.tic();
        for(int i=0; i<num_prove; ++i) hybrid_quick_sort(v_hybrid[i], k);
        double t_h = timer.toc() / num_prove;
        std::cout << "k = " << k << " -> Tempo: " << t_h << " s" << std::endl;
    }

    return 0;
}