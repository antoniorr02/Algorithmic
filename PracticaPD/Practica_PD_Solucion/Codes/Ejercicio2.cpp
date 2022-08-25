/**
 * Línea de ejecución: ./ejecutable 4 5 1 -1 0 0 0 0 1 -1 1 -1 0 1 1 1 1 0 1 1 1 1
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * Elementos de la matriz:
 * Bolsa de dinero --> 1.
 * Casilla vacia --> 0.
 * Muro --> -1.
 * Entrada --> -0.
 * Salida --> 0.
 */
//////////////////////////////////////////////////////// COMPROBAMOS LOS DATOS.

void ComprobarEntradasSalidas(vector<vector<int>> matriz, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			int elemento = matriz[i][j];
			if(elemento < -1 || elemento > 1) {
				cout << "Error: Hay algún elemento que no se corresponde a ninguno de los elementos posibles" << endl;
				cout << "Intervalo 1,1" << endl;
				exit(-1);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int ** allocate(int r, int c) {
    int ** block;
    // allocate memory into block
    block = new int * [r];
    for (int i = 0; i < r; i++) {
        block[i] = new int [c];
    }
    return block;
}

int MejorCasilla(int lado, int diagonal, int abajo) {
    int elegido;
    if (lado > diagonal) {
        if (lado > abajo)
            elegido = lado;
        else
            elegido = abajo;
    } else {
        if (abajo > diagonal)
            elegido = abajo;
        else
            elegido = diagonal;
    }        
    return elegido;
}

void InicializaraCero(int ** caminos, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			caminos[i][j] = -1;
		}
	}
}

void CaminoOptimo(vector<vector<int>> matriz, int ** caminos, int filas, int columnas) {

    InicializaraCero(caminos, filas, columnas);

/////////// Si encontramos un muro en la fila sabemos que las posiciones que le siguen son inaccesibles
    for (int j = columnas - 2; j >= 0; --j) {
        caminos[0][j] = matriz[0][j] + caminos[0][j-1];
        if (matriz[0][j] == -1) {
            for (; j >= 0; j--) {
                caminos[0][j] = -1;
            }
        }
    }

/////////// Si encontramos un muro en la columna sabemos que las posiciones que le siguen son inaccesibles
    caminos[0][columnas-1] = matriz[0][columnas-1];
    for (int i = 1; i < filas; ++i) {
        caminos[i][columnas - 1] = matriz[i][columnas - 1] + caminos[i-1][columnas-1];
        if (matriz[i][columnas - 1] == -1) {
            for (; i < filas; i++) {
                caminos[i][columnas - 1] = -1;
            }
        }
    }
    cout << endl;

//////////// Vamos iterando fila a fila y vamos sumando a la casilla en la que nos encontramos los 3 valores de los que podemos venir.

    for (int i = 1; i < filas; ++i) {
        for (int j = columnas - 2; 0 <= j; --j) {
            if (matriz[i][j] == -1) {
                caminos[i][j] = -1;
            } else if (caminos[i - 1][j] == -1 && caminos[i - 1][j + 1] == -1 && caminos[i][j + 1] == -1) {
                caminos[i][j] = -1;
            } else {
                caminos[i][j] = matriz[i][j] + MejorCasilla(caminos[i - 1][j], caminos[i - 1][j + 1], caminos[i][j + 1]);
            }
        }
    }
}

vector<pair<int, int>> GuardarCamino(int** caminos, int filas, int columnas) {
    vector<pair<int, int>> solucion;
    pair<int, int> aux;
    int i = filas - 1, j = 0;
    aux.first = i;
    aux.second =j;
    solucion.push_back(aux);
    while (i != 0 && j != columnas - 1) {
        if (caminos[i - 1][j] > caminos[i - 1][j + 1]) {
            if (caminos[i - 1][j] > caminos[i][j + 1]) {
                i--;
            } else {
                j++;
            }
        } else {
            if (caminos[i][j + 1] > caminos[i - 1][j + 1]) {
                j++;
            } else {
                i--;
                j++;
            }
        }
        aux.first = i;
        aux.second =j;
        solucion.push_back(aux);
    }
    return solucion;
}

int main(int argc, char * argv[]) {
	if (argc < 3) {
		cout << "Error en los argumentos: ./ejecutable filas * columnas" << endl;
		exit(-1);
	}
	int filas = stoi(argv[1]);
	int columnas = stoi(argv[2]);

	if (filas * columnas != argc - 3) {
		cout << "Número de elementos del matriz incorrecto: filas * columnas" << endl;
		exit(-1);
	}

	vector<vector<int>> matriz;
	vector<int> aux;

	int cont = 0;
	int n = 0;
	for (int i = 3; i < argc; i++) {
		aux.push_back(stoi(argv[i]));
		cont++;
		if (cont == columnas) {
			cont = 0;
			matriz.push_back(aux);
			aux.clear();
			n++;
		}
	}

	ComprobarEntradasSalidas(matriz, filas, columnas);

	cout << "Matriz: " << endl;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++)
			cout << " " << setw(3) << setprecision(2) << matriz[i][j];
		cout << endl;
	}

	int** caminos = allocate(filas, columnas);
	CaminoOptimo(matriz, caminos, filas, columnas);

    cout << "Matriz de caminos: " << endl;
	for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << " " << setw(2) << setprecision(2) << caminos[i][j];
        }
        cout << endl;
    }
    cout << endl;

    vector<pair<int, int>> posiciones = GuardarCamino(caminos, filas, columnas);

    cout << "El camino por el cual se recogen más bolsas de dinero será: ";
	for (int i = posiciones.size()-1; i >= 0; i--) 
		cout << "[" << posiciones[i].first << "," << posiciones[i].second << "]"; 
	cout << endl;

	return 0;
}