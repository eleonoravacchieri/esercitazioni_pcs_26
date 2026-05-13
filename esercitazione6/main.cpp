#include <iostream>
#include <vector>
#include <set>
#include <cassert> // serve per assert che mi aiuta nelle verifiche 
#include "unidirected_graph.h"


int main() {
	// TEST 1: unidirected_edge
	std::cout << "Esecuzione TEST 1: unidirected_edge" << std::endl;
	unidirected_edge<int> e1(7,5);
	// verifico from < to (assert verifica che quella cosa sia vera)
	assert(e1.from() == 5);
	assert(e1.to() == 7);
	std::cout << "Arco e1 corretto: " << e1 << std::endl;
	
	//Test operator==
	unidirected_edge<int> e2(5, 7); 
	assert(e1 == e2);
	std::cout << "Test operator == superato" << std::endl;
	
	
	//TEST 2: unidirected_graph base 
    std::cout << "\nEsecuzione TEST 2: unidirected_graph base" << std::endl;
    unidirected_graph<int> g1;
    g1.add_edge(1, 2);
    g1.add_edge(2, 3);
    g1.add_edge(1, 3);
    g1.add_edge(3, 4);
	g1.add_edge(2, 5);
	
	// Test all_nodes 
    std::set<int> nodes = g1.all_nodes();
    assert(nodes.size() == 5);
    std::cout << "Nodi nel grafo: ";
    for(int n : nodes) std::cout << n << " ";
    std::cout << std::endl;

	// Test neighbours 
    std::set<int> v_di_3 = g1.neighbours(3);
    std::cout << "Vicini del nodo 3: ";
    for(int v : v_di_3) std::cout << v << " "; // dovrebbero essere 1, 2, 4
    std::cout << std::endl;

	// TEST 3: Numerazione archi 
    std::cout << "\nEsecuzione Test 3: Numerazione archi" << std::endl;
    unidirected_edge<int> edge_da_cercare(3, 2); // Sarà memorizzato come (2, 3)
    int idx = g1.edge_number(edge_da_cercare); 
    std::cout << "L'arco (2--3) si trova all'indice: " << idx << std::endl;
	
	// Test edge_at
    unidirected_edge<int> e_recuperato = g1.edge_at(idx);
    assert(e_recuperato == edge_da_cercare);
    std::cout << "Arco recuperato all'indice " << idx << ": " << e_recuperato << std::endl;

    // TEST 4: Differenza tra grafi (operator-)
    std::cout << "\nEsecuzione Test 4: Differenza tra grafi..." << std::endl;
    unidirected_graph<int> g2;
    g2.add_edge(1, 2);
    g2.add_edge(3, 4);

    // g3 conterrà gli archi di g1 che non sono in g2
    unidirected_graph<int> g3 = g1 - g2;
    std::vector<unidirected_edge<int>> diff_edges = g3.all_edges(); 

    std::cout << "Archi risultanti dalla differenza (g1 - g2):" << std::endl;
    for(const auto& e : diff_edges) {
        std::cout << e << " "; // Dovrebbe stampare (1--3), (2--3) e (2--5)
    };
	
    std::cout << std::endl;

    std::cout << "\n--- TUTTI I TEST SUPERATI CON SUCCESSO ---" << std::endl;

    return 0;	
	
}