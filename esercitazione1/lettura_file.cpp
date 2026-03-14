// include <fstream>
// int main(void) {
	// std::cout <<"Enter file name: \\n;
	// std::string 
	// string filename = "lettura_file.txt";
	// ifstream ifs(filename);	
// }	if ( ifs.is_open() ) { // Check if file successfully opened
		// while( !ifs.eof() ) {
			// string location;
			// double temp;
			// ifs >> location >> temp; // also >> : S × T → S
			// cout << "Temperature at " << location << " is " << temp << "\n";
		// }
	// }
	// return 0;
// }

#include <fstream>  
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
// argc(argument count) -> intero con il numero di parametri passati al programma
// argv[] (argument vector)-> è un array di stringhe (puntatore di caratteri) in questo caso:
// 		arg[0] >> ./programma
//		arg[1] >> input_es1.txt

	// controllo se sono stati inseriti tutti gli input
	if (argc < 2) {
		std::cerr <<"Errore: scrivere ./nome_programma nome_file.txt\n";
		return 1;
		}
	// Una volta compilato, decido da terminale il nome del file da inserire(input_es1.txt) 
	std::string filename = argv[1];
	std::ifstream ifs(filename); //leggere dati da un file verso il programma

	if (ifs.is_open()) {
		std::string città; //inizializzo var stringa per il nome della città 
		double t0,t6,t12,t18; //inizializzo var decimali per le tempertaure 
		
		//   !!IMPORTANTE!! 
		while(ifs >> città >> t0 >> t6 >> t12 >> t18) { 
			//	L'operatore >> estrae i dati dal file e li "versa" nelle variabili:
			//	Cerca la prima parola e la salva in città.
			//	Salta lo spazio vuoto, cerca il numero successivo e lo salva in t0 ecc.
			double media = (t0+t6+t12+t18)/4.0;
			std::cout << città <<" "<< media <<"\n";
			}
		}
		
		else {
			std::cerr << "Errore: il file " << filename << " non è stato aperto correttamente\n" ; 
			// Dà errore se non è stato aperto correttamente 
			return 1;
		}
	return 0;
}
