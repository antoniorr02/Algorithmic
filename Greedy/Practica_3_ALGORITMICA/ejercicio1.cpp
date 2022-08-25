#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Valor Infinito
#define INF 1e20

// Cadena nula
#define SINNOMBRE ""

class Problema
{

private:
	double **t_transmission; // Tiempo de transmisión (ns)
	string **aristas;		 // Nombre de las aristas (sensor x a sensor y)
	string *sensor;			 // Nombres de los sensores
	int n;					 // Número de sensores

	void Inicializar() {

		n = 0;
		t_transmission = 0;
		aristas = 0;
		sensor = 0;
	}

	void Liberar() { // Libera la memoria e inicializa a NULL todo

		if (n > 0) {
			for (int i = 0; i < n; i++){
				delete[] aristas[i];
				delete[] t_transmission[i];
			}

			delete[] t_transmission;
			delete[] aristas;
			delete[] sensor;
			Inicializar();
		}
	}

	void Reservar() {

		if (n > 0) {

			sensor = new string[n];
			aristas = new string *[n];
			t_transmission = new double *[n];
			for (int i = 0; i < n; i++) {

				sensor[i] = SINNOMBRE;
				aristas[i] = new string[n];
				t_transmission[i] = new double[n];

				for (int j = 0; j < n; j++)
				{
					aristas[i][j] = SINNOMBRE;
					t_transmission[i][j] = INF;
				}
			}
		}
	}

public:
	Problema() { // Crear un problema vacío
		Inicializar();
	}

	Problema(const Problema &otro) {

		Inicializar();
		*this = otro;
	}

	Problema &operator=(const Problema &otro) {

		Liberar();

		n = otro.n;
		Reservar();
		for (int i = 0; i < n; i++)
			sensor[i] = otro.sensor[i];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				aristas[i][j] = otro.aristas[i][j];
				t_transmission[i][j] = otro.t_transmission[i][j];
			}
		}

		return *this;
	}

	~Problema() {
		Liberar();
	}

	void setNumsensores(int otran) {
		if (otran >= 0) {
			Liberar();

			n = otran;
			Reservar();
		}
	}

	int getNumsensores() {
		return n;
	}

	void setSensor(int idx, string nombre) {
		if (idx >= 0 && idx < n)
			sensor[idx] = nombre;
	}

	string getSensor(int idx) {
		if (idx >= 0 && idx < n)
			return sensor[idx];
		return SINNOMBRE;
	}

	// Precondición: El tiempo debe ser > 0
	void setArista(int pOrigen, int pDestino, string nombre, double coste) {

		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n && coste > 0) {
			t_transmission[pOrigen][pDestino] = coste;
			aristas[pOrigen][pDestino] = nombre;
		}
	}

	double gett_transmission(int pOrigen, int pDestino) {
		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n)
			return t_transmission[pOrigen][pDestino];
		return INF;
	}

	string getArista(int pOrigen, int pDestino) {
		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n)
			return aristas[pOrigen][pDestino];
		return SINNOMBRE;
	}

	bool leerFichero(const char *nombrefich) {
		ifstream fich;
		int numSensores;
		double t_trans;
		char nombres[1001];
		char c;

		fich.open(nombrefich);
		if (!fich)
			return false;

		fich >> numSensores;
		fich.get(c);
		if (numSensores <= 0) {
			fich.close();
			return false;
		}

		Liberar();
		n = numSensores;
		Reservar();

		for (int i = 0; i < n; i++) { // Leemos los sensores
			fich.getline(nombres, 1000);
			if (!fich.eof())
				setSensor(i, nombres);
			else {
				Liberar();
				fich.close();
				return false;
			}
		}

		// Leemos las aristas
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				fich >> t_trans;
				if (fich.eof() && i != n - 1 && j != n - 1) {
					Liberar();
					fich.close();
					return false;
				}

				if (t_trans > -1) {
					fich.getline(nombres, 1000);
					setArista(i, j, nombres, t_trans);
				}
			}
		}

		fich.close();
		return true;
	}
};

double Dijkstra(Problema p, int destino, int origen) {
	int n = p.getNumsensores();
	int sol[n] = {-1};
	double distancia[n], C[n];
	for (int i = 0; i < n; i++) {
		distancia[i] = p.gett_transmission(destino, i);
		C[i] = p.gett_transmission(destino, i);
		sol[i] = -1;
	}

	int cont = 1;
	while(cont < n) {
		int pos = 0;
		for (int i = 0; i < n; i++) {
			if (C[i] < distancia[cont]) {
				pos = i;
				C[pos] = INF;
				i = n;
			}
		}
		int aux = 0;
		for (int i = 0; i < n; i++) {
			if (distancia[i] > distancia[pos] + p.gett_transmission(pos, i)) {
				distancia[i] = distancia[pos] + p.gett_transmission(pos, i);
				if (aux != i) sol[aux] = -1;
				sol[i] = pos;
				aux = i;
			}
		}
		cont++;
	}

	cout << "Señal emitida desde: " << p.getSensor(origen) << endl;
	cout << "\nSensores intermedios: " << endl;
	int id = sol[origen];
	while (id != -1) {
		cout << p.getSensor(id) << endl;
  		id = sol[id];
	}
	cout << endl;
	cout << "Sensor destino: " << p.getSensor(destino);

	return distancia[origen];
}

int main()
{
	Problema p;
	double s;

	p.leerFichero("sensores.dat");
	s = Dijkstra(p, 0, 3);

	cout << endl
		 << "Tiempo transmisión: " << s << endl;

	return 0;
}