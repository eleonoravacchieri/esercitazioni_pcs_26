#pragma once

#include "unidirected_graph.h"

#include <queue> 
#include <stack>
#include <map>
#include <limits>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm> // necessario per algoritmi STL
#include <stdexcept> //per std::out_of_range 


// ================================= ESERCITAZIONE 9 ===================================

// BFS: contenitore FIFO = coda
// DFS: contenitore LIFO = pila
// visited: std::set<T> oppure std::map<T,bool>

// --- contenitore con politica FIFO ---


template <typename T>
class fifo {
private:
	std::queue<T> q;

public: 

	// inserisco elemento in fondo alla coda  
	fifo() = default;
	void put(const T& value){
		q.push(value);		
	}
	
	// estraggo elemento in testa alla coda 
	T get() {
		T value = q.front();
		q.pop();
		return value;
	}
	
	// verifico se il contenitore è vuoto
	bool empty() const{
		return q.empty();
	}
};


// --- contenitore con politica LIFO ---

template <typename T>
class lifo {
private:
    std::stack<T> l;

public:
    lifo() = default;
	
	// inserisco elemento in cima allo stack
    void put(const T& value) {
        l.push(value);
    }
	
	// estrae elemento sulla cima dello stack
    T get() {
        T value = l.top();
        l.pop();
        return value;
    }

	// verifico se il contenitore è vuoto 
    bool empty() const {
        return l.empty();
    }
};

// ===========================================================
/** funzione graph_visit() 

• Prende in input due parametri, il grafo da visitare ed il nodo sorgente
• Prende un parametro template che specifica il tipo del contenitore da usare per effettuare la
visita
• Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita

La funzione, in base al contenitore passato come parametro, deve effettuare una visita in ampiezza
oppure una visita in profondit`a (Figura 2). Si ottengano le immagini dei due grafi utilizzando
GraphViz e si verifichi che `e stata effettuata la visita richiesta
*/

template <typename T, typename Container>
unidirected_graph<T> graph_visit(
    const unidirected_graph<T>& G,
    const T& source,
    Container container
) 

{

    unidirected_graph<T> tree;

    // insieme dei nodi visitati
    std::set<T> visited;

    // inserisco il nodo sorgente
    container.put(source);
    visited.insert(source);

    while (!container.empty()) {

        T current = container.get();

        // prendo i vicini
        std::set<T> neigh = G.neighbours(current);

        for (const auto& v : neigh) {

            // se NON visitato
            if (visited.find(v) == visited.end()) {

                visited.insert(v);

                // aggiungo arco all'albero visita
                tree.add_edge(current, v);

                // inserisco nel contenitore
                container.put(v);
            }
        }
    }

    return tree;
}


// ------------- DFS ricorsiva ------------------
template <typename T>
void dfs_recursive_helper(
    const unidirected_graph<T>& G,
    const T& current,
    std::set<T>& visited,
    unidirected_graph<T>& tree
) {

    visited.insert(current);

    std::set<T> neigh = G.neighbours(current);

    for (const auto& v : neigh) {

        if (visited.find(v) == visited.end()) {

            tree.add_edge(current, v);

            dfs_recursive_helper(G, v, visited, tree);
        }
    }
}

template <typename T>
unidirected_graph<T> recursive_dfs(
    const unidirected_graph<T>& G,
    const T& source
) {

    unidirected_graph<T> tree;

    std::set<T> visited;

    dfs_recursive_helper(G, source, visited, tree);

    return tree;
}

// -------------------- DIJKSTRA ---------------------------

template <typename T>
std::map<T, int> dijkstra(
    const unidirected_graph<T>& G,
    const T& source
) {
    std::map<T, int> dist;
    std::set<T> visited;

    const int INF = std::numeric_limits<int>::max();

    for (const auto& node : G.all_nodes()) {
        dist[node] = INF;
    }

    dist[source] = 0;

    while (visited.size() < G.all_nodes().size()) {

        T current;
        int best_dist = INF;
        bool found = false;

        for (const auto& node : G.all_nodes()) {
            if (visited.find(node) == visited.end() && dist[node] < best_dist) {
                best_dist = dist[node];
                current = node;
                found = true;
            }
        }

        if (!found) {
            break;
        }

        visited.insert(current);

        for (const auto& neigh : G.neighbours(current)) {
            if (visited.find(neigh) == visited.end()) {

                int new_dist = dist[current] + 1;

                if (new_dist < dist[neigh]) {
                    dist[neigh] = new_dist;
                }
            }
        }
    }

    return dist;
}