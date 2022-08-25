#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

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

    string salida;
    double *v;
	int n, argumento;

    // Comprobar validez de la llamada
    if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}

    // Obtener argumentos
    salida = argv[1];

    ofstream a(salida);
    if (!a.is_open()) {
        cerr << "Fail creating " << salida << " file" << endl;
    }

    vector<chrono::nanoseconds> times;
    vector<int> sizes;
    int k = 0;
    	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new double[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int i= 0; i<n; i++)
			v[i]=n-i;
			//v[i]= rand()%n;

		srand(time(NULL));
		int pos = rand()%n;

        // Chrono start, operation to measure, chrono stop
        auto start = chrono::high_resolution_clock::now();
        while (k <= 10) {
        	reestructurarRaiz(v, int(n/2), n);
            //HeapSort(v, n);
            k++;
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>((stop - start)/k);
        // Hago la media de ejecutar 10 veces lo mismo para conseguir valores más estables.
        k = 0;

        // Info storing
        times.push_back(duration);
        sizes.push_back(n);
    }

    // Printing
    cout << "Sizes: ";
    for (int i = 0; i < sizes.size(); ++i){
        cout << sizes[i] << ",";
    }
    cout << endl;
    cout << "Times: ";
    for (int i = 0; i < times.size(); ++i){
        cout << times[i].count() << ",";
    }
    cout << endl;
    for (int i = 0; i < times.size(); ++i){
        a << sizes[i] << "," << times[i].count() << endl;
    }
    return 0;
}