#include <iostream>
#include <vector>

template <typename T>
class unidirected_edge {
	int _u, _v;

private:
	T _from;
	T _to;

public:
	unidirected_edge(const T& a, const T& b) 
		// gestisco ordine --> _from < _to 
		if (a < b) {
			_from = a;
			_to = b;
		} else {
			_from = b;
			_to = a;
		}	
}
