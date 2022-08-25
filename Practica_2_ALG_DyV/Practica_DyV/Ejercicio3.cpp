#include <iostream>

using namespace std;

bool existe(int n) {
	if (n <= 5) return false;
	bool encontrado = false;
	int valor = 0;
	for(int i = 0; valor <= n; i++) {
		valor = i*(i+1)*(i+2);
		if (valor == n) encontrado = true;
	}
	return encontrado;
}

bool existeDyV(const int n, int izquierda, int derecha) {
	
	if (n <= 5) return false;
 	
    int centro = (izquierda + derecha) / 2;
    int valor = centro*(centro+1)*(centro+2);
 
    if (valor == n) return true;
    
    if (izquierda == derecha || izquierda > derecha) return false;
    if (valor > n)
        derecha = centro-1;
    else
        izquierda = centro+1;
    
    return existeDyV(n, izquierda, derecha);
}

int main() {
	cout << "Ejecución para algoritmo básico: " << endl;
	for (int i = 0; i < 211; i+=6) {
		if (existe(i)) cout << i << ": tiene 3 consecutivos que lo forman" << endl;
		if (!existe(i)) cout << i << ": NO tiene 3 consecutivos que lo forman" << endl;
	}

	cout << endl << "Ejecución para algoritmo DyV: " << endl;
	for (int i = 0; i < 211; i+=6) {
		if (existeDyV(i,0, i)) cout << i << ": tiene 3 consecutivos que lo forman" << endl;
		if (!existeDyV(i, 0, i)) cout << i << ": NO tiene 3 consecutivos que lo forman" << endl;
	}
}