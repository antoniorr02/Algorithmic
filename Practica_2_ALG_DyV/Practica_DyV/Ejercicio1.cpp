#include <iostream>

using namespace std;

int multiplicador(int i, int j) {
	int suma = 0;
	if (j == 0 || i == 0) return 0;
	if (i == 1) return j;
	if (j == 1) return i;
	for (int n = 0; n < i; n++) {
		suma += j;
	}
	return suma;
}

int multiplicadorDyV(int i, int j) {
	if (j == 0 || i == 0) return 0;
	if (i == 1) return j;
	if (j == 1) return i;

	int aux, resultado=0, izquierda, derecha;

    int mitad = j / 2;

    if (j%2 == 0) aux = 0;
    else aux = 1;

    izquierda = multiplicadorDyV(i, mitad);
    derecha = multiplicadorDyV(i, mitad + aux);
    resultado = izquierda + derecha;

    return resultado;
}

////////////////////////////////////////////////////////////
// NO ES DyV

int multiplicadorRecursivo(int i, int j, const int copia_i) {
	if (j == 0 || i == 0) return 0;
	if (i == 1) return j;
	if (j == 1) return i;

	i += copia_i;
	multiplicadorRecursivo(i, j-1, copia_i);
}

//////////////////////////////////////////////////////////////

int main () {

	cout << "Prueba para algoritmo básico: " << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 5; j > 0; j--) {
			cout << "Resultado de la multiplicación de " << i << " - " << j << ": " << multiplicador(i, j) << endl;
		}
	}
	cout << endl << endl << "Prueba para algoritmo DyV: " << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 5; j > 0; j--) {
			cout << "Resultado de la multiplicación de " << i << " - " << j << ": " << multiplicadorDyV(i, j) << endl;
		}
	}

	return 0;
}