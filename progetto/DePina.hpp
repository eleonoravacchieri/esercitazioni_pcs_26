#pragma once
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include "graphs.hpp"
#include "contenitori.hpp"
#include "graph_visit.hpp"
#include "cicli_fondamentali.hpp"

inline int prodotto_scalare_z2(const std::vector<int>& v1, const std::vector<int>& v2) {
    int sum = 0;
    for (size_t i = 0; i < v1.size(); ++i) sum += v1[i] * v2[i];
    return sum % 2;
}

inline std::vector<int> xor_vettori(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> res(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) res[i] = v1[i] ^ v2[i];
    return res;
}

// RICERCA DEL CICLO MINIMO 
inline std::pair<std::vector<int>, struttura_cicli<int>> trova_ciclo_minimo(const unidirected_graph<int>& G, const std::vector<int>& S_i) {
    int m = G.all_edges().size();
    int V_offset = *G.all_nodes().rbegin() + 1; //uso l'offset per gli indici

    // Costruiamo il grafo sdoppiato
    unidirected_graph<int> G_lift;
    for (const auto& e : G.all_edges()) {
        int u = e.from(), v = e.to();
        
        //forzo il peso a 1
        if (S_i[G.edge_number(e)] == 1) {
            G_lift.add_edge(u, v + V_offset, 1.0); 
            G_lift.add_edge(u + V_offset, v, 1.0);
        } 
        else {
            G_lift.add_edge(u, v, 1.0);
            G_lift.add_edge(u + V_offset, v + V_offset, 1.0);
        }
    }

    double peso_minimo = 1e9;
    std::vector<int> maschera_ottima(m, 0); //vettore di incidenza
    struttura_cicli<int> struttura_ottima;

    for (int nodo_start : G.all_nodes()) {
        int target = nodo_start + V_offset;
        unidirected_graph<int> albero = dijkstra(G_lift, nodo_start);

        // Ricostruzione cammino BFS
        std::map<int, int> padre; //backtracking
        std::queue<int> q;
        q.push(nodo_start);
        padre[nodo_start] = -1;

        bool trovato = false;
        while (!q.empty() && !trovato) {
            int cur = q.front(); q.pop();
            for (int vicino : albero.neighbours(cur)) {
                if (padre.find(vicino) == padre.end()) {
                    padre[vicino] = cur;
                    if (vicino == target) { 
                        trovato = true; 
                        break; 
                    }
                    q.push(vicino);
                }
            }
        }
        
        if (!trovato) continue;

        std::vector<int> cammino;
        for (int c = target; c != -1; c = padre[c]) cammino.push_back(c);
        std::reverse(cammino.begin(), cammino.end());

        // Calcolo peso
        double peso = cammino.size()-1;

        if (peso >= peso_minimo) continue;

        // Se è il migliore, lo salviamo
        peso_minimo = peso;
        maschera_ottima.assign(m, 0); //sovrascrive (buono per il costo computazionale)
        struttura_ottima.nodes.clear();
        struttura_ottima.edges.clear();

        for (size_t i = 0; i + 1 < cammino.size(); ++i) {
            int n1 = cammino[i] % V_offset;
            int n2 = cammino[i + 1] % V_offset;
            struttura_ottima.nodes.push_back(n1);
            
            unidirected_edge<int> arco(n1, n2);
            if (G.all_edges().count(arco)) {
                maschera_ottima[G.edge_number(arco)] ^= 1; //operatore xor
                struttura_ottima.edges.insert(arco);
            }
        }
        struttura_ottima.nodes.push_back(cammino.back() % V_offset);
    }

    return {maschera_ottima, struttura_ottima};
}

// controllo che il senso delle maglie sia concorde
inline void orienta_maglie(std::vector<struttura_cicli<int>>& maglie) {
    if (maglie.size() <= 1) return;

    std::vector<bool> orientata(maglie.size(), false);
    orientata[0] = true; // La maglia 0 detta le regole

    bool modificato = true;
    while (modificato) {
        modificato = false;
        
        for (size_t i = 1; i < maglie.size(); ++i) {
            if (orientata[i]) continue; 

            // la confrontiamo con tutte le maglie già controllate
            for (size_t j = 0; j < maglie.size(); ++j) {
                if (!orientata[j]) continue;

                bool trovato_arco_comune = false;
                bool discordi = false;

                // Controlliamo ogni arco della maglia da sistemare
                for (size_t ki = 0; ki + 1 < maglie[i].nodes.size(); ++ki) {
                    int ui = maglie[i].nodes[ki], vi = maglie[i].nodes[ki+1];

                    // Controlliamo ogni arco della maglia buona
                    for (size_t kj = 0; kj + 1 < maglie[j].nodes.size(); ++kj) {
                        int uj = maglie[j].nodes[kj], vj = maglie[j].nodes[kj+1];

                        // Se attraversano gli stessi nodi ESATTAMENTE nello stesso verso (es. 2->3 e 2->3)
                        if (ui == uj && vi == vj) {
                            trovato_arco_comune = true;
                            discordi = true; 
                        } 
                        // Se li attraversano in versi opposti (es. 2->3 e 3->2)
                        else if (ui == vj && vi == uj) {
                            trovato_arco_comune = true;
                        }
                    }
                }

                //arco in comune
                if (trovato_arco_comune) {
                    if (discordi) {
                        // Invertiamo tutto il percorso della maglia i!
                        std::reverse(maglie[i].nodes.begin(), maglie[i].nodes.end() - 1);
                        maglie[i].nodes.back() = maglie[i].nodes.front(); // Chiudiamo il cammino
                    }
                    orientata[i] = true;
                    modificato = true;
                    break; // Passiamo alla prossima maglia
                }
            }
        }
    }
}

// algoritmo di De Pina
inline std::vector<struttura_cicli<int>> de_pina(const unidirected_graph<int>& G, int nodo_sorgente) {
    
    lifo<int> pila;
    unidirected_graph<int> T = graph_visit(G, nodo_sorgente, pila); //albero DFS
    unidirected_graph<int> Coalbero = G - T; 

    int m = G.all_edges().size();
    int k = Coalbero.all_edges().size();

    std::vector<std::vector<int>> S(k, std::vector<int>(m, 0));
    int l = 0;
    for (const auto& arco_corda : Coalbero.all_edges()) {
        S[l][G.edge_number(arco_corda)] = 1;
        l++;
    }

    std::vector<struttura_cicli<int>> base_cicli;
    
    for (int i = 0; i < k; ++i) {
        auto [maschera_ottima, ciclo_struttura] = trova_ciclo_minimo(G, S[i]);
        base_cicli.push_back(ciclo_struttura);

        for (int j = i + 1; j < k; ++j) {
            if (prodotto_scalare_z2(maschera_ottima, S[j]) == 1) {
                S[j] = xor_vettori(S[j], S[i]);
            }
        }
    }

    orienta_maglie(base_cicli);

    return base_cicli;
}