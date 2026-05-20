#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm> // necessario per algoritmi STL
#include <stdexcept> //per std::out_of_range 


template <typename T>
class unidirected_edge {
private:
	T _from;
	T _to;
	
public:
	//costruttore: _from < _to
	unidirected_edge(const T& a, const T& b) {
		if (a < b) {
			_from = a;
			_to = b;
		} else {
			_from = b;
			_to = a;
		}
	}


	// getter
	T from() const { return _from; }
	T to() const { return _to; }

	// OPERATOR<: ordina gli archi (e li usa in un std::set)
	bool operator<(const unidirected_edge<T>& other) const {
		if (_from != other._from) {
			return _from < other._from;
		}
		return _to < other._to;
	}
		
	// OPERATOR== : due archi sono uguali se hanno gli stessi identici nodi 
	bool operator==(const unidirected_edge<T>& other) const {
		return (_from == other._from && _to == other._to);
	}

	// OPERATOR<< : STAMPA --> uso friend che, anche se non è un metodo che ho definito io può leggere le variabili private 
	friend std::ostream& operator<<(std::ostream& os, const unidirected_edge<T>& edge) {
		os << "(" << edge._from << " -- " << edge._to << ")";
		return os;
    }
	
 // <-- ricordarsi il punto e virgola!!
};

// ora vado con UNIDIRECTED GRAPH --> dato che devo gestire una numerazione degli archi
// la scelta di un contenitore STL è findaamentale 

template <typename T>
class unidirected_graph {
private:
// salvo gli archi in un vettore per avere una numerazione (indice) 
	std::vector<unidirected_edge<T>> _edges;

public:
	// 1. costruttore di default 
	unidirected_graph() = default; 
	
	// 2. costruttore di copia 
	unidirected_graph(const unidirected_graph& other) : _edges(other._edges) {}
	
	// ADD_EDGE: aggiunge un arco al grafo.
    // l'operazione add_node() non è prevista perchè i nodi vengono creati
    // implicitamente quando si aggiunge un arco.
	 
	 
	// 3. aggiunta di un arco
	void add_edge(const T& u, const T& v) {
		unidirected_edge<T> new_edge(u, v);
		// no duplicati o semplice aggiunta:
		_edges.push_back(new_edge);
	}
	
	// 4. restituisce tutti i nodi (no duplicati)
	std::set<T> all_nodes() const {
		std::set<T> nodes;
		for (const auto& edge : _edges) {
			nodes.insert(edge.from());
			nodes.insert(edge.to ());
		}
		return nodes;
	}	
	// NEIGHBOURS: dato un nodo, restituisce i suoi vicini
	// Scorre tutti gli archi e, se il nodo fa parte dell'arco, 
    // aggiunge l'altro estremo al set dei vicini.
	
	std::set<T> neighbours(const T& node) const {
		std::set<T> result;
		
		for (const auto& edge : _edges) {
			if (edge.from() == node) {
                result.insert(edge.to());
            } else if (edge.to() == node) {
                result.insert(edge.from());
            }
        }
		return result;
    }
	
	// all_edges: restituisce tutti gli archi
	std::vector<unidirected_edge<T>> all_edges() const {
    return _edges;
	}
	
	/**
     * EDGE_NUMBER: dato un arco, ne restituisce il suo indice
     * all'interno del grafo.
     */
	 
    int edge_number(const unidirected_edge<T>& edge) const {
        for (size_t i = 0; i < _edges.size(); ++i) {
            if (_edges[i] == edge) {
                return i; // restituisce pos se trovato
            }
        }
        return -1; // convenzione: restituisce -1 se l'arco non esiste
    }

    /**
     * EDGE_AT: dato un numero d'arco (indice), restituisce l'oggetto arco
     * corrispondente all'interno del grafo.
     */
	 
    unidirected_edge<T> edge_at(int index) const {
        // indice valido?
        if (index >= 0 && index < _edges.size()) {
            return _edges[index];
        }
        // indice non valido
        throw std::out_of_range("Indice arco non valido");
    }
	
	/**
     * OPERATOR-: calcola la differenza tra due grafi.
     * Restituisce un nuovo grafo contenente gli archi presenti 
     * in questo grafo (this) e non presenti nel grafo 'other'.
     */
	 
    unidirected_graph<T> operator-(const unidirected_graph<T>& other) const {
        unidirected_graph<T> result;
        
        // Recuperiamo tutti gli archi del secondo grafo per il confronto
        std::vector<unidirected_edge<T>> other_edges = other.all_edges();

        for (const auto& e : _edges) {
            bool found = false;
            for (const auto& oe : other_edges) {
                if (e == oe) {
                    found = true;
                    break;
                }
            }
            
            // se l'arco non è stato trovato nel secondo grafo, 
			// lo aggiungo al risultato
			
            if (!found) {
                result.add_edge(e.from(), e.to());
            }
        }
        
        return result;
    }

};

