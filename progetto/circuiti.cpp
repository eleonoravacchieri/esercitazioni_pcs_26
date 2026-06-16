#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "metodi_correnti.hpp"
#include "graphs.hpp"
#include "gradiente_coniugato.hpp"

int main(){
    circuito C=lettura("../netlist.txt"); //la netlist non si trova in build/
    
    unidirected_graph<int>& G=C.G;
    unidirected_edge<int> arco_sorgente= G.edge_at(0);
    std::vector<struttura_cicli<int>> cicli = cicli_fondamentali_dfs(G, arco_sorgente.from());
    std::vector<struttura_cicli<int>> maglie = de_pina( G, arco_sorgente.from()); 

    //creare vettore resistori e struttura componenti
    std::vector<struttura> resistenze;
    for (const auto& coppia : C.componenti) {
        if (coppia.second.type.front() == 'R') {   //confronta il primo carattere
            resistenze.push_back(coppia.second);
        }
    }
    std::vector<struttura> generatori;
    for (const auto& pair : C.componenti) {
        if (pair.second.type.front() == 'V') {
            generatori.push_back(pair.second);
        }
    }

    //creo matrice di incidenza e resistenza
    //n= numero di cicli 
    //m= numero di resitori
    //metodo dfs = 1
    //metodo de pina = 2
    Eigen::MatrixXd R = costruzione_R (resistenze); //resistenza mxm
    Eigen::MatrixXd B = costruzione_B (resistenze , cicli ); //incidenza mxn
    Eigen::MatrixXd B2 = costruzione_B (resistenze , maglie );
    Eigen::VectorXd v = costruzione_v (generatori, cicli); //vettore termini noti
    Eigen::VectorXd v2 = costruzione_v (generatori, maglie);
    Eigen::MatrixXd A = B.transpose() * R * B;
    Eigen::MatrixXd A2 = B2.transpose() * R * B2;
    
    // Parametri per il Gradiente Coniugato
    Eigen::VectorXd x0_1 = Eigen::VectorXd::Zero(v.size()); 
    Eigen::VectorXd x0_2 = Eigen::VectorXd::Zero(v2.size()); 
    double tolleranza = 1e-10;  
    unsigned int iter_max = 1000; 

    // Risoluzione per DFS
    risultati ris_dfs = gradiente_coniugato(A, v, x0_1, tolleranza, iter_max);
    Eigen::VectorXd i = ris_dfs.x;

    // Risoluzione per De Pina
    risultati ris_depina = gradiente_coniugato(A2, v2, x0_2, tolleranza, iter_max);
    Eigen::VectorXd i2 = ris_depina.x;

    Eigen::VectorXd tensioni = R * B * i;
    Eigen::VectorXd correnti = B * i;
    Eigen::VectorXd tensioni2 = R * B2 * i2;
    Eigen::VectorXd correnti2 = B2 * i2;

    std::cout << "\nRISULTATI CICLI FONDAMENTALI (DFS): \n";
    for (int r=0; r<resistenze.size(); r++){
        std::cout << resistenze[r].type << ": V = " << tensioni[r] << " volts, I = " << correnti[r] << " amps\n";
    }
    std::cout << "\nRISULTATI DE PINA: \n";
    for (int r=0; r<resistenze.size(); r++){
        std::cout << resistenze[r].type << ": V = " << tensioni2[r] << " volts, I = " << correnti2[r] << " amps\n";
    }
    std::cout << "\n";

    return 0;
}