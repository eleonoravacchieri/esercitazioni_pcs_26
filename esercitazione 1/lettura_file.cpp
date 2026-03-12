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

using namespace std;

int main(void) {
	string filename = "lettura_file.txt";
	ifstream ifs(filename);
	if ( ifs.is_open() ) { // Controlla se è stato aèerto correttamente 
		while( !ifs.eof() ) {
			string location;
			double temp;
			ifs >> location >> temp; // also >> : S × T → S
			cout << "Temperature at " << location << " is " << temp << "\n";
		}
	}
	return 0;
}
