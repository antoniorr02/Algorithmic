// Ejemplo de la ordenacion por burbuja sobre un vector de enteros

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
using namespace std;

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

pair<int, int> MaximoMinimoDyV(int * A, int Cini, int Cfin) {
	pair<int, int> resultados = {A[Cini],A[Cfin]};

	if(Cini < Cfin-1) {
		int mitad = (Cini + Cfin)/2;
		pair<int, int> resultados1 = MaximoMinimoDyV(A, Cini, mitad);
		pair<int, int>resultados2 = MaximoMinimoDyV(A, mitad + 1, Cfin);

		if(resultados1.first > resultados2.first) 
			resultados.first = resultados1.first;
		else
			resultados.first = resultados2.first;

		if(resultados1.second < resultados2.second) 
			resultados.second = resultados1.second;
		else
			resultados.second = resultados2.second;

	} else if (Cini	== Cfin) {
		resultados.first = A[Cini];
		resultados.second = A[Cini];
	} else {

		if(A[Cini] > A[Cfin]) 
			resultados.first = A[Cini];
		else
			resultados.first = A[Cfin];

		if(A[Cini] <= A[Cfin]) 
			resultados.second = A[Cini];
		else
			resultados.second = A[Cfin];
		
	}

	return resultados;
}
/*
pair<int, int> MaximoMinimoDyV(int * A, int Cini, int Cfin) {
    pair<int, int> minmax; // Minimo first y Maximo second
    if (Cini < Cfin - 1) {
        int mitad = (Cini + Cfin) / 2;
        pair<int, int> Inf = MaximoMinimoDyV(A, Cini, mitad);
        pair<int, int> Sup = MaximoMinimoDyV(A, mitad + 1, Cfin);
        minmax.second = (Inf.second < Sup.second) ? Sup.second : Inf.second;
        minmax.first = (Inf.first > Sup.first) ? Sup.first : Inf.first;
    } else if (Cini == Cfin) {
        minmax.second = A[Cini];
        minmax.first = A[Cini];
    } else {
        minmax.second = (A[Cini] < A[Cfin]) ? A[Cfin] : A[Cini];
        minmax.first = (A[Cini] > A[Cfin]) ? A[Cfin] : A[Cini];
    }
    return minmax;
}*/

void HeapSort(int *v, int n) {
	double * apo = new double [n];
	int tamapo=0;

	for (int i = 0; i < n; i++) {
		apo[tamapo] = v[i];
		tamapo++;
		insertarEnPos(apo, tamapo);
	}
	for (int i = 0; i < n; i++) {
		v[i]=apo[0];
		tamapo--;
		apo[0]=apo[tamapo];
		reestructurarRaiz(apo, 0, tamapo);
	}
	delete [] apo;
}


int main(int argc, char *argv[]) {
	
	double *v;
	int n, i, argumento;
    //chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
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

		for (i= 0; i<n; i++) {
			v[i]=n-i;
			//v[i]= rand()%n;
		}
		
		cerr << "Ejecutando Burbuja para tam. caso: " << n << endl;
		
		auto t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		//insertarEnPos(v, int(n/2));
		reestructurarRaiz(v, int(n/2), n); // Ejecutamos el algoritmo para tamaÒo de caso tam
		//OrdenaBurbuja(v, n);
		//insertarEnPos(v, int(n/2));
		//MaximoMinimoDyV(v, 0, n-1);
		//HeapSort(v, n);
		auto tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}



