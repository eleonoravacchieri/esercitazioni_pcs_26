#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iterator>

template <typename T>
class unidirected_edge
{
	
private:
	T u, v;    
	
public:
	unidirected_edge(const T& u1, const T& v1)  //prende due nodi
	{
		if (u1<v1)           //inserisco i due nodi nei nodi da me inizializzati con u<v
		{
			u=u1;
			v=v1;
		}
		else
		{
			u=v1;
			v=u1;       //prendo u come il minore dei due nodi per metterlo in from
		}
	}
	
	T from() const 
	{ 
		return u; 
	}
    T to() const 
	{ 
		return v; 
	}
	
	bool operator<(const unidirected_edge& other) const    //affinch´e gli archi possano essere ordinabili
	{														//prendo un arco 'unidirected_edge' e un altro 'other'
		if (u != other.u) //se il primo nodo di un_e è diverso dal primo nodo di other ordino
		{
			return u < other.u;   
		}
		return v < other.v;
	}
	
	bool operator==(const unidirected_edge<T>& other) const
	{
		return u==other.u && v==other.v;		
	}
	
	friend std::ostream& operator<<(std::ostream& os, const unidirected_edge<T>& lato) 
	{
        os << "(" << lato.u << " -- " << lato.v << ")";
        return os;
    }
};

template <typename T>
class unidirected_graph
{
	
private:
	std::set<unidirected_edge<T> > archi;  //creo un set con gli archi (chiavi), infatti il tipo degli elementi del set è unidirected_edge
    std::map<T, std::set<T> > la;   //creo una lista di adiacenza con una mappa che ha come chiavi i nodi, per ognuno dei quali è associata una lista di nodi adiacenti
                                     //la chiave (nodo) si trova con pair.first, i nodi adiacenti con pair.second(che rende un set con all vicini) 
public:
    unidirected_graph() = default;
    unidirected_graph(const unidirected_graph& other) = default;
	

	std::set<T> neighbours(const T& u) const   //i vicini di u(nodo dato) sono in un set
	{
        if (la.count(u))    //count è un booleano che rende True se la chiave (nodo u) esiste
		{					//controllo che avrei potuto fare anche con find
			return la.at(u);  //potevo usare anche la[u], che però se non trova la chiave ne crea una nuova con quel nome (ho comunque fatto l'if quindi non ci sarebbe problema)
        }
		return {};            //rende un set vuoto sei il nodo non ha vicini
    }
	
	std::map<unidirected_edge<T>, double> W;
	void add_edge(const T& u, const T& v, double peso)
	{
		if (u==v)
		{
			return;
		}
		
		unidirected_edge<T> nuovo_arco(u,v);  //se i due nodi son diversi creo un nuovo elemento di tipo unidirected_edge tra i due (arco)
		archi.insert(nuovo_arco);          //lo aggiungo al set di archi
		la[u].insert(v);				   //aggiungo i nodi alla lista di adiacenza
		la[v].insert(u);
		
		W[nuovo_arco]=peso;      //creo una mappa che associa a ogni arco un peso
	}

	double weight(const T& u, const T& v) const 
	{
        return W.at(unidirected_edge<T>(u, v));
    }
	
	std::set<unidirected_edge<T> > all_edges() const   //all edges rende tutti gli archi sottoforma di set di archi
	{
        return archi; 
    }
	
	std::set<T> all_nodes() const   //rende tutti i nodi sottoforma di set di nodi
	{
		std::set<T> nodi;      //lista nodi
        for(const auto& pair : la) //scorre ogni elemento della mappa
		{
			nodi.insert(pair.first);   
		}
		return nodi;
    }
	
	size_t edge_number(const unidirected_edge<T>& arco) const //dato un arco rende la sua numerazione nel grafo
	{
		auto pos=archi.find(arco);   //trova l'arco nella lista
		if (pos==archi.end())
		{
			std::cerr << "ERRORE arco non trovato nel grafo" << std::endl;
		}
		return std::distance(archi.begin(), pos);
	}
	
	unidirected_edge<T> edge_at(int num) const  //data il numero di arco, rende l'arco del grafo corrispondente
	{
		if (num>=archi.size())                    
		{
			std::cerr << "ERRORE indice troppo grande" << std::endl;
		}
		auto arco= std::next(archi.begin(), num);  //prende l'elemento in posizione num nel set
		return *arco;  //referenziato
	}
		
	unidirected_graph<T> operator-(const unidirected_graph<T>& other) const   //due grafici this e other
	{
		unidirected_graph<T> result;   //result è un nuovo grafo vuoto
        for (const auto& arco : this->archi) //prendo ogni arco nel grafico attuale(this)
		{
            if (other.archi.find(arco) == other.archi.end()) //se nel secondo grafo non trovo questo arco 
			{
                result.add_edge(arco.from(), arco.to(), this->W.at(arco));    //aggiungo l'arco che è solo nel primo grafo al grafo result
            } 
        }
        return result;
	}	
};
	