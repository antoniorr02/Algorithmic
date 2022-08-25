#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

// ALGORITMO MAXIMIZACIÓN DEL PESO TIPO GREDDY.
void maximizacion_peso(vector<pair<string, double>> & pesoContenedores, double cargaMaxima) {
	int n = pesoContenedores.size();
	OrdenaBurbuja(pesoContenedores, n);
	double sumaPesos = 0;
	cout << "Carga máxima: " << cargaMaxima << endl;
	cout << "Contenedores cargados: ";
	while (sumaPesos < cargaMaxima && !pesoContenedores.empty()) {
		double aux = pesoContenedores.back().second;
		if (sumaPesos + aux <= cargaMaxima) {
			sumaPesos += aux;
			cout << pesoContenedores.back().first << ":" << aux << "T ";
		}
		pesoContenedores.pop_back();
	}
	cout << endl << "Peso total: " << sumaPesos << endl;
}

int main (int argc, char *argv[]) {
	if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" cargaMaxima identificador1 pesoContenedores1 identificador2 pesoContenedores2 ... identificadorN pesoContenedoresN\n\n";
		return 0;
	}
	vector<pair<string,double>> pesoContenedores;
	for (int i=2; i<argc; i+=2) {
		string id = argv[i];
		double aux = stod(argv[i+1]);
		pair<string, double> input;
		input.first = id;
		input.second = aux;
		pesoContenedores.push_back(input);
	}
	maximizacion_peso(pesoContenedores, stod(argv[1]));
}