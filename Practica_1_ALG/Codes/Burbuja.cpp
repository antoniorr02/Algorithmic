// Ejemplo de la ordenacion por burbuja sobre un vector de enteros

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void insertarEnPos(double *apo, int pos){
	int idx = pos-1;
	int padre;
	if(idx > 0) {
		padre=(idx-2)/2;
	} else {
		padre=(idx-1)/2;
	}

	if(apo[padre] > apo[idx]) {
		double tmp=apo[idx];
		apo[idx]=apo[padre];
		apo[padre]=tmp;
		insertarEnPos(apo, padre+1);
	}
}

void reestructurarRaiz(double *apo, int pos, int tamapo) {
	int minhijo;
	if (2*pos+1 < tamapo) {
		minhijo=2*pos+1;
		if ((minhijo+1 < tamapo) && (apo[minhijo] > apo[minhijo+1])) minhijo++;
		if (apo[pos]>apo[minhijo]) {
			double tmp = apo[pos];
			apo[pos]=apo[minhijo];
			apo[minhijo]=tmp;
			reestructurarRaiz(apo, minhijo, tamapo);
		}
	}
}



int main(int argc, char *argv[]) {
	
	double *v;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new double[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando Burbuja para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		reestructurarRaiz(v, int((n-2)/2), n-2); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (ns): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}


void OrdenaBurbuja(int *v, int n) {
	
	int i, j, aux;
	bool haycambios= true;
	
	i= 0;
	while (haycambios) {
		
	 haycambios=false; // Suponemos vector ya ordenado
	 for (j= n-1; j>i; j--) { // Recorremos vector de final a i
		 
		 if (v[j-1]>v[j]) { // Dos elementos consecutivos mal ordenados
		  aux= v[j]; // Los intercambiamos
		  v[j]= v[j-1];
		  v[j-1]= aux;
		  haycambios= true; // Al intercambiar, hay cambio
		 }
	 }
	 i++;
	}
}



