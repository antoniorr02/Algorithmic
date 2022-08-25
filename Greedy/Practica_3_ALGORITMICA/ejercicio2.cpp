#include <iostream>
#include <string>
#include <vector>

using namespace std;

void OrdenaBurbuja(vector<pair<string,double>> & v, int n) {
	
	int i, j, aux;
	string id;
	bool haycambios= true;
	
	i= 0;
	while (haycambios) {
		haycambios=false; // Suponemos vector ya ordenado
		for (j= n-1; j>i; j--) { // Recorremos vector de final a i
			 
			if (v[j-1].second>v[j].second) { // Dos elementos consecutivos mal ordenados
			  aux = v[j].second; // Los intercambiamos
			  id = v[j].first;
			  v[j].second = v[j-1].second;
			  v[j].first = v[j-1].first;
			  v[j-1].second = aux;
			  v[j-1].first = id;
			  haycambios= true; // Al intercambiar, hay cambio
			}
		}
		i++;
	}
}

void Minimas_paradas(vector<pair<string,double>> gasolineras, double autonomia){
    OrdenaBurbuja(gasolineras, gasolineras.size());
	cout << "Salimos de: " << gasolineras.front().first << endl << "Pararemos en: \n";
	int cont = 0;
	for(int n = 0; n < gasolineras.size();) { 
		int distancia = gasolineras[n].second - gasolineras[cont].second;
		if(distancia <= autonomia){
            n++;
        } else {
            if (gasolineras[n-1] != gasolineras[cont]){
                cout << "Gasolinera " << gasolineras[n-1].first << " en el km " << gasolineras[n-1].second << endl;
				cont = n-1;
            } else {
                cout << "No es posible completar el recorrido" << endl;
                exit(-1);
            }
        }
	}
	cout << gasolineras.back().first << " en el kilometro " << gasolineras.back().second << endl;
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" Autonomía gasolinera1 dist_origen1 identificador2 gasolinera2 ... gasolineraN dist_origenN\n\n";
		return 0;
	}
	vector<pair<string,double>> gasolineras;
	for (int i=2; i<argc; i+=2) {
		string gasolinera = argv[i];
		double dist = stod(argv[i+1]);
		pair<string, double> input;
		input.first = gasolinera;
		input.second = dist;
		gasolineras.push_back(input);
	}
	int autonomia = stod(argv[1]);
	Minimas_paradas(gasolineras, autonomia);

////////////////////////// USADO PARA DEBUGGER.
/*
	vector<pair<string,double>> ejemplo;
    ejemplo={{"salida", 0},{"a", 2},{"b", 4},{"c", 9},{"llegada", 14}};
    
    Minimas_paradas(ejemplo,5);
    
    return 0;
*/
}