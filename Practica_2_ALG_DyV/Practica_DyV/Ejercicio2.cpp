#include <iostream>
#include <cmath>

using namespace std;

bool CuadradoPerfecto(int n) {
	bool cuadrado_perfecto = false;
	if (n == 0 || n == 1) cuadrado_perfecto = true;
	else {
		int valor = 0;
		for (int i = 2; valor <= n; i++) {
			valor = i*i;
			if (valor == n) cuadrado_perfecto = true;
		}
	}
	return cuadrado_perfecto;
}

/**
 * @brief Comprueba si un número es cuadrado perfecto.
 * 
 * @param n Número a comprobar.
 * @param izquierda Necesariamente será 0.
 * @param derecha Necesariamente será n.
 * @return true En caso de verificarse que es cuadrado perfecto.
 * @return false En caso no ser cuadrado perfecto.
 */
bool CuadradoPerfectoDyV(const int n, int izquierda, int derecha) {
	
	if (n == 0 || n == 1) return true;
 	
    int centro = (izquierda + derecha) / 2;
    int valor = centro*centro;
 
    if (valor == n) return true;
    
    if (izquierda == derecha) return false;
    if (valor > n)
        derecha = centro-1;
    else
        izquierda = centro+1;
    
    return CuadradoPerfectoDyV(n, izquierda, derecha);
}  

/////////////////////////////////////////////////////////////
//NO VALIDOS AL NO PODER UTILIZAR LA LIBRERIA CMATH

bool CuadradoPerfecto_conCmath1(int n) {
	bool cuadrado_perfecto = false;
	for (int i = 0; i <= int(sqrt(n)); i++) {
		if (n == pow(i, 2)) {
			cuadrado_perfecto = true;
			i = n;
		}
	}
	return cuadrado_perfecto;
}

bool CuadradoPerfecto_conCmath2(int n) {
	bool cuadrado_perfecto = false;
	if (sqrt(n)-int(sqrt(n))== 0) cuadrado_perfecto = true;
	return cuadrado_perfecto;
} 

//////////////////////////////////////////////////////////////

int main() {
	cout << "Ejecución para algoritmo básico: " << endl;
	for (int i = 0; i < 10; i++) {
		int valor = pow(i, 2);
		if (CuadradoPerfecto(valor)) cout << valor << ": es cuadrado perfecto" << endl;
		valor++;
		if (!CuadradoPerfecto(valor)) cout << valor << ": NO es cuadrado perfecto" << endl;
	}
	cout << endl;
	cout << "Ejecución para algoritmo DyV: " << endl;
	for (int i = 0; i < 10; i++) {
		int valor = pow(i, 2);
		if (CuadradoPerfectoDyV(valor, 0, valor)) cout << valor << ": es cuadrado perfecto" << endl;
		valor++;
		if (!CuadradoPerfectoDyV(valor, 0, valor)) cout << valor << ": NO es cuadrado perfecto" << endl;
	}
}