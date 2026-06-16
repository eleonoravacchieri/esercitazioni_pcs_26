#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "graphs.hpp"
#include "cicli_fondamentali.hpp"
#include "DePina.hpp"

struct struttura {
    std::string type;    // 'R' o 'V'
    double value;
    int sign;     // +1 se nodo1 < nodo2 nella netlist, -1 altrimenti
    int nodo1;
    int nodo2;
};

struct circuito{
    unidirected_graph<int> G;
    std::map<unidirected_edge<int>, struttura> componenti;
};

circuito lettura(const std::string& nome){
    unidirected_graph<int> G;
    std::map<unidirected_edge<int>, struttura> componenti;
    std::ifstream ifs(nome);
    circuito c;

    if ( ifs.is_open() ){
        std::string tipo;
        double peso;
        int nodo1, nodo2;

        while ( ifs >> tipo>> peso >> nodo1 >> nodo2 ){
            //gestisco gli errori
            
            if (nodo1==nodo2){
                std::cerr << "ERRORE: l'arco è un loop" << std::endl ;
                continue;
            }


            unidirected_edge<int> nuovo_arco(nodo1, nodo2);
            auto archi_attuali =c.G.all_edges();

            if (archi_attuali.find(nuovo_arco) != archi_attuali.end()){
                std::cerr<< "ERRORE: l'arco esiste già" << std::endl ; //controllare 
                continue;
            }
                
            c.G.add_edge(nodo1, nodo2, peso); //il peso è double

            if (nuovo_arco.from()== nodo1) { //se il nodo1 è il minore prendo il segno positivo
                c.componenti[nuovo_arco] = struttura{ tipo, peso, +1, nodo1, nodo2};
            } 
            else {
                c.componenti[nuovo_arco] = struttura{ tipo, peso, -1, nodo1, nodo2 };
            }
        }
    }
    else {
        std::cerr << "ERRORE: il file non è stato aperto correttamente"<< std::endl ; 
        return c;
    }
    return c;
}

Eigen::MatrixXd costruzione_R (const std::vector<struttura>& resistori){
    int m= resistori.size();
    Eigen::VectorXd valori(m);
    for (int v=0; v<m; v++){
        valori(v) = resistori[v].value;
    }
    Eigen::MatrixXd R= valori.asDiagonal();
    return R;
}

Eigen::MatrixXd costruzione_B(const std::vector<struttura>& resistenze, const std::vector<struttura_cicli<int>>& cicli) {

    int m= resistenze.size();
    int n= cicli.size();
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, n);

    for (size_t z = 0; z < n; z++) {
        
        const std::vector<int>& percorso = cicli[z].nodes;
        
        for (size_t k = 0; k < percorso.size() - 1; k++) {
            int nodo_partenza = percorso[k];
            int nodo_arrivo = percorso[k + 1];
            
            for (int r = 0; r < m; r++) {
                unidirected_edge<int> arco_r (resistenze[r].nodo1, resistenze[r].nodo2);
                if (nodo_partenza == arco_r.from() && nodo_arrivo == arco_r.to()) { 
                    B(r, z) = +1;
                    break; 
                }
                else if (nodo_partenza == arco_r.to() && nodo_arrivo == arco_r.from()) {
                    B(r, z) = -1;
                    break; 
                }
                
            }
        }
    }
    return B;
}

Eigen::VectorXd costruzione_v(const std::vector<struttura>& generatori, const std::vector<struttura_cicli<int>>& cicli) {
    int n= cicli.size();

    Eigen::VectorXd v = Eigen::VectorXd::Zero(n);

    for (size_t z = 0; z < cicli.size(); z++) {
        
        const std::vector<int>& maglia = cicli[z].nodes;

        for (size_t k = 0; k < maglia.size() - 1; k++) {
            int nodo_partenza = maglia[k];
            int nodo_arrivo = maglia[k + 1];

            for (int g = 0; g < generatori.size(); g++) {
                unidirected_edge<int> arco_g (generatori[g].nodo1, generatori[g].nodo2);
                if (nodo_partenza == arco_g.from() && nodo_arrivo == arco_g.to()) {
                    v(z) -= generatori[g].value * generatori[g].sign;
                    break;
                }
                else if (nodo_partenza == arco_g.to() && nodo_arrivo == arco_g.from()) {
                    v(z) += generatori[g].value * generatori[g].sign;
                    break;
                }
            }
        }
    }
    return v;
}

