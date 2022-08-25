/*
	Autor: Equipo Chanchullo
	Fecha: 12/05/2022
	Version: Definitiva
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Valor Infinito
#define INF 1e20

// Cadena nula
#define SINNOMBRE ""


class Problema {

private:
	double **t_envio; // Tiempo de envio de un nodo a otro
	string **conexiones; // Nombre de las conexiones entre nodos
	string *nodo; // Nombres de los nodos
	int n; // Número de nodos

	void Inicializar() {
		n= 0;
		t_envio= 0;
		conexiones= 0;
		nodo= 0;
	}

	void Liberar() {  // Libera la memoria e inicializa a NULL todo

		if (n> 0) {

			for (int i= 0; i<n; i++) {
				delete [] conexiones[i];
				delete [] t_envio[i];
			}

			delete [] t_envio;
			delete [] conexiones;
			delete [] nodo;
			Inicializar();
		}
	}

	void Reservar() { 

		if (n>0) {

			nodo= new string[n];
			conexiones= new string *[n];
			t_envio= new double *[n];
			for (int i= 0; i<n; i++) {

				nodo[i]= SINNOMBRE;
				conexiones[i]= new string[n];
				t_envio[i]= new double[n];

				for (int j= 0; j<n; j++) {
					conexiones[i][j]= SINNOMBRE;
					t_envio[i][j]= INF;
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
		*this= otro;
	}

	Problema & operator=(const Problema &otro) {

		Liberar();

		n= otro.n;
		Reservar();
		for (int i= 0; i<n; i++)
			nodo[i]= otro.nodo[i];

		for (int i= 0; i<n; i++) {
			for (int j= 0; j<n; j++) {
				conexiones[i][j]= otro.conexiones[i][j];
				t_envio[i][j]= otro.t_envio[i][j];
			}
		}

		return *this;
	}

	~Problema() {
		Liberar();
	}


	void setNumNodos(int otran) { 
		
		if (otran >= 0) {
			Liberar();

			n= otran;
			Reservar();
		}
	}

	int getNumNodos() {
		return n;
	}



	void setNodo(int idx, string nombre) {
		
		if (idx >= 0 && idx < n)
			nodo[idx]= nombre;
	}



	string getNodo(int idx) {

		if (idx >= 0 && idx < n)
			return nodo[idx];
		return SINNOMBRE;
	}

	// Precondición: El tiempo debe ser > 0
	void setConexion(int pOrigen, int pDestino, string nombre, double tiempo) {

		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n
			&& tiempo > 0) {

			t_envio[ pOrigen ][ pDestino ]= tiempo;
			conexiones[ pOrigen ][ pDestino ]= nombre;
		}
	}

	double gett_envio(int pOrigen, int pDestino) {

		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n)
			return t_envio[ pOrigen ][ pDestino ];
		return INF;
	}

	string getConexion(int pOrigen, int pDestino) {

		if (pOrigen >= 0 && pDestino >= 0 && pOrigen < n && pDestino < n)
			return conexiones[ pOrigen ][ pDestino ];
		return SINNOMBRE;
	}
	

	bool leerFichero(const char *nombrefich) {

		ifstream fich;
		int numNodos;
		double t_trans;
		char nombres[1001];
		char c;

		fich.open(nombrefich);
		if (!fich)
			return false;

		fich >> numNodos;
		fich.get(c);
		if (numNodos <= 0) {

			fich.close();
			return false;
		}

		Liberar();
		n= numNodos;
		Reservar();

		for (int i= 0; i<n; i++) { // Leemos los sensores
			fich.getline(nombres, 1000);
			if (!fich.eof())
				setNodo(i, nombres);
			else {

				Liberar();
				fich.close();
				return false;
			}
		}

		// Leemos las aristas
		for (int i= 0; i<n; i++) {
			for (int j= 0; j<n; j++) {

				fich >> t_trans;
				if (fich.eof() && i!=n-1 && j!=n-1) {
					Liberar();
					fich.close();
					return false;
				}

				if (t_trans > -1) {

					fich.getline(nombres, 1000);
					setConexion(i, j, nombres, t_trans);
				}
			}
		}

		fich.close();
		return true;
	}
};

double Greedy(Problema p, int servidor, int nodo_i) {
  
  // p.getNumsensores() es el número de vértices que tiene el Grafo
  int n = p.getNumNodos();
  
  // Vector de distancias respecto al nodo Servidor ---> Inicializado posteriormente
  double D[n];
  // Vector booleano de nodos marcados/vistos ---> Inicializamos a FALSE y actualizaremos durante el proceso
  bool marcados[n] = {false};
  // Vector de enteros que indica el identificador del nodo previo al mismo ---> Inicializado posteriormente
  int previo[n];
  
  // Inicializamos vector  distancia
  for(int i = 0; i < n; i++) {
  	if(i != servidor){
  		if (p.gett_envio(servidor, i) == INF){
  			D[i] = INF;
  		}
  		else{	// Ademas de asignar la distancia del nodo "i" al servidor, en este caso se verifica que Servidor es el nodo previo a "i", ya que existe conexion directa.
  			D[i] = p.gett_envio(servidor,i);
  			previo[i] = servidor;
  		}
  	}
  }
  D[servidor] = 0;
  marcados[servidor] = true;
  previo[servidor] = -1;

  // Llevamos un nodo visto/marcado, el Servidor
  int vistos = 1;
  // Hasta que todos sean VISTOS
  while(vistos < n) {
  	double menor = INF;
  	int pos;
  	// Buscamos el nodo con la menor distancia respecto al nodo Servidor
  	for (int i = 0; i < n; i++) {
  		if (D[i] < menor && !marcados[i] && i != servidor) {
  			pos = i;
  			menor = D[i];
  		}
  	}
  	// Marcamos la posicion encontrada
	marcados[pos] = true;
	vistos++;
   	/* Transformamos el valor Distancia para un nodo "i" si encontramos un camino menor a través de un nodo de paso.
    	Además, si encontramos el mencionado nodo de paso, tomaremos este nodo como el previo de "i". */
	for (int i = 0; i < n; i++) {
		if (D[i] > D[pos] + p.gett_envio(pos, i)) {
			D[i] = D[pos] + p.gett_envio(pos, i);
			previo[i] = pos;
		}
	}
  }
  // Mostramos por pantalla el camino seguido y retornamos la distancia obtenida
  cout << endl << "Camino minimo que recorre la transmision: " << endl << endl;
  cout << "Nodo origen: " << p.getNodo(nodo_i) << endl;
  
  int k = previo[nodo_i];
  while(previo[k] != -1){
  	cout << "Nodo de paso: " << p.getNodo(k) << endl;
  	k = previo[k];
  }
  cout << "Nodo final: " << p.getNodo(servidor) << endl;
  
  return D[nodo_i];
}



int main() {
	Problema p;
	double t_minimo;

	p.leerFichero("definitivo.dat");
	t_minimo = Greedy(p, 0, 5);
	
	cout << endl<< "Tiempo de transmision entre nodos inicial y final: "<< t_minimo << endl;

	return 0;
}

