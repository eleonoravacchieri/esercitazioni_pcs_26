#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <limits>
#include <algorithm>
#include <queue>      //per priority_queue 
#include <limits>     //per std::numeric_limits 
#include <utility>    // Per pair 
#include <functional>  //per greater
#include "graphs.hpp"

template <typename T, typename contenitore>
unidirected_graph<T> graph_visit(const unidirected_graph<T> g, const T& nodos, contenitore& c)  //prendo un grafo, il nodo sorgente e un contenitore(pila o coda, a seconda che voglia usare BFS o DFS)
{
	unidirected_graph<T> albero;
	std::set<T> visitati;   //sostituisce il ciclo for che controlla azzera tutte le posizioni
	
	c.put(nodos);
	visitati.insert(nodos);
	
	//BFS e DFS hanno struttura identica, colo che uno usa la pila uno usa la coda. creando un contenitore e le funzioni in contenitori.hpp che hanno nomi uguali per i due tipi di contenitore, posso scegliere in seguito quale usare
	while(!c.empty())
	{
		T u=c.get();
		for (const T& w : g.neighbours(u))
		{
			if(visitati.find(w) == visitati.end())  // se non trova in nodo w nel set di nodi già visitati
			{
				visitati.insert(w);  //inserisco w nei nodi visitati
				double peso = g.weight(u, w);
				albero.add_edge(u,w,peso);  //aggiungo il ramo all'albero
				c.put(w);             
			}
		}
	}
	return albero;
	
}


//il dfs ricorsivo mi da un risultato differente da quello iterativo perchè 
//quello ricorsivo scorre la lista dei vicini e appena ne trova uno che non ho ancora visitato va in quello, 
//mentre quello iterativo prima inserisce tutti i vicini nello stack e poi prende quello in cima (l'ultimo inserito), invertendo quindi l'ordine di visita dei nodi

template <typename T>
void recursive_dfs_base(const unidirected_graph<T>& g, const T& u, std::set<T>& visitati, unidirected_graph<T>& albero) 
{
	visitati.insert(u);
    for (const T& v : g.neighbours(u)) 
	{
        if (visitati.find(v) == visitati.end()) 
		{
			double w = g.weight(u, v);
            albero.add_edge(u, v, w);
            recursive_dfs_base(g, v, visitati, albero);
        }
    }
}

template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& g, const T& nodos) 
{
    unidirected_graph<T> albero;
    std::set<T> visitati;
    recursive_dfs_base(g, nodos, visitati, albero);
    return albero;
}

template <typename T>
unidirected_graph<T> dijkstra(const unidirected_graph<T>& g, const T& s) 
{
	//s nodo sorgente
	//n+2 numero totale nodi {s,u1,u2,...,un,v}
	//w matrice dei pesi
	//pred array del predecessore
	//dist array delle distanze
	std::map<T, double> dist;
    std::map<T, T> pred;
	
	for (const auto& i : g.all_nodes())
	{
		pred[i]=-1;
		dist[i]= std::numeric_limits<double>::infinity();
	}
	pred[s]=0;
	dist[s]=0;
	
	//ps: coda con priorità per visitare il grafo, con i vertici come elementi 
	//e con priorità associata alla distanza tra due vertici !=
	
    using distanza = std::pair<T, T>;  //contiene (distanza dal sorgente,nodo in questione)
    std::priority_queue<distanza, std::vector<distanza>, std::greater<distanza>> pq;  //(nodo, distanza minima dalla sorgente)
	//greater<T> ordina la priorityqueue in modo che venga sempre estratto per primo il nodo con la distanza minore
	
	for (const auto& j : g.all_nodes())
	{
		pq.push({dist[j], j});
	}
	while(!pq.empty()) 
	{
		T u=pq.top().second;
		//double p= pq.top().first; inutilizzato   //p è la distanza tra s e u
		pq.pop();
		
		for (const auto& w : g.neighbours(u))  //per ogni w nodo della lista di adiacenza di u
		{
			//ho aggiunto a graphs una mappa W che ha archi(chiavi) e peso arco
			T peso_uw= g.weight(u,w);
			if(dist[w]>dist[u]+peso_uw)  //se distanza(s,w) è > di (dist(s,u)+peso arco da u in w)
			{
				dist[w]=dist[u]+peso_uw;
				pred[w]=u;
				pq.push({dist[w], w});  //inserimento in pq
			}
		}
	}
		
	unidirected_graph<T> albero_minimo;
	
    for (const auto& coppia : pred) 
	{
        T nodo_corrente = coppia.first;
        T predecessore = coppia.second;
        
        if (nodo_corrente != s && predecessore != -1) 
		{
            albero_minimo.add_edge(predecessore, nodo_corrente, g.weight(predecessore, nodo_corrente));
        }
    }
	return albero_minimo;  //restituisce mappe distanze e dei predecessori
}