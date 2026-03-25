# include <iostream>
# include <algorithm> // libreria di min e max 
# include <cmath> // libreria di sqrt
 
static const int N=6;
int main()
{	
	double ad[N]={0.6,1.1,1.3,1.8,2.0,2.7};
	// massimo e minimo
	// std::min restituisce un iteratore (puntatore), quindi uso * per il valore
	double min = *std::min_element(ad, ad+N); // devo mettere inizio e fine dell'array!!!
	double max = *std::max_element(ad, ad+N);
	
	// media
	double sum = 0.0;
	for ( int i=0; i<N ; ++i)	{
		sum = sum + ad[i];
	}
	double media = sum / N; 
	
	// deviazione standard
	double sum_quadrati = 0.0;
	for ( int i=0; i<N ; ++i) {
		sum = pow(ad[i] - media, 2)/N;
	}
	double st_dev = sqrt(sum);
	
	
	//std::sqrt << sqrt(ad);
	
	std::cout << "Min: " << min << "\n";
	std::cout << "Max: " << max << "\n";
	std::cout << "Media: " << media << "\n";
	std::cout << "Deviazione standard: " << st_dev << "\n";

	return 0;
}
