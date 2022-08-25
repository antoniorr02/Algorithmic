#include <iostream>
#include <vector>

using namespace std;

/**
 * Elementos de la matriz:
 * Salida y llegada --> 0
 * Dificultad en rango de 1 a INFINITO.
 */

void ComprobarEntradasSalidas(const vector<vector<int>> & matriz, int filas, int columnas) {
	if (matriz[0][columnas-1] != 0 || matriz[filas-1][0] != 0) {
		cout << "Error en la posición de las casillas salida-llegada del terreno" << endl;
		exit(-1);
	}

	int control = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			int elemento = matriz[i][j];
			if(elemento == 0) {
				control++;
			}
			if(elemento < 0) {
				cout << "Error: No puede haber dificultad negativa, mínimo será 1" << endl;
				exit(-1);
			}
			if (control > 2) {
				cout << "Error: Se ha utilizado más de una entrada o más de una salida" << endl;
				exit(-1);
			}
		}
	}
}

int ** allocate(int r, int c) {
    int ** block;
    // allocate memory into block
    block = new int * [r];
    for (int i = 0; i < r; i++) {
        block[i] = new int [c];
    }
    return block;
}

void InicializarMenosUno(int ** solucion, int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			solucion[i][j] = -1;
		}
	}
}

int CaminoGreedy(const vector<vector<int>> & matriz, int ** solucion, int filas, int columnas) {
	int suma_dificultades = 0;
	for (int i = filas-1; i >= 0;) {
		for (int j = 0; j < columnas;) {
			solucion[i][j] = matriz[i][j];
			// Posibilidades: matriz[i-1][j], matriz[i-1][j-1] o matriz[i][j-1]
			int lado = 1e6;
			int diagonal = 1e6;
			int arriba = 1e6;
			// Comprobamos que existen los valores superiores.
			if (i-1 >= 0)
				arriba = matriz[i-1][j];
			if (i-1 >= 0 && j + 1 < filas)
				diagonal = matriz[i-1][j+1];
			if (j + 1 < filas)
				lado = matriz[i][j+1];

			// Vemos que valor es menor para hacer el greedy
			if (lado == 1e6 && diagonal == 1e6 && arriba == 1e6) {
				j++; i--;
			} else {
				if (arriba < diagonal && arriba < lado) {
					solucion[i-1][j] = arriba;
					suma_dificultades += arriba;
					i--;
				} else if (diagonal <= arriba && diagonal <= lado) {
					solucion[i-1][j+1] = diagonal;
					suma_dificultades += diagonal;
					i--; j++;
				} else if (lado < arriba && lado < diagonal) {
					solucion[i][j+1] = lado;
					suma_dificultades += lado;
					j++;
				}
			}
		}
	}
	return suma_dificultades;
}

void copy(int **dest, int **org, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            dest[i][j] = org[i][j];
        }
    }
}

void Dibujar(int ** solucion, int filas, int columnas) {
	cout << endl << "El camino por el que tendrá terrenos con menos dificultad para llegar será: " << endl;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			cout << solucion[i][j] << " ";
		}
		cout << endl;
	}
}

void CaminoFinal(vector<vector<int>> matriz, int ** solucion, int filas, int columnas, int valor_camino_actual) {

	///////////////////////////////////// MAL!
	/*int aux = 0;
	int ** solucion_temp = allocate(filas, columnas);
	InicializarMenosUno(solucion_temp, filas, columnas);
	for (int i = filas-1; i >= 0;) {
		for (int j = 0; j < columnas;) {
			int lado = 1e6;
			int diagonal = 1e6;
			int arriba = 1e6;
			if (i-1 >= 0)
				arriba = matriz[i-1][j];
			if (i-1 >= 0 && j + 1 < filas)
				diagonal = matriz[i-1][j+1];
			if (j + 1 < filas)
				lado = matriz[i][j+1];

			int valor = matriz[i][j];
			if (valor >= 0)
				aux += valor;
				solucion_temp[i][j] = valor;
				Dibujar(solucion_temp, filas, columnas);
			if (aux < valor_camino_actual && diagonal == 0) {
				valor_camino_actual = aux;
			}
		}
	}*/
	////////////////////////////////////////////////////
}

void PosicionesOptimas(int ** solucion, vector<pair<int, int>> & camino, int filas, int columnas) {
	pair<int, int> pos;
	for (int i = filas-1; i >= 0; i--) {
		for (int j = 0; j < columnas; j++) {
			if (solucion[i][j] >= 0) {
				pos.first = i; 
				pos.second = j;
				camino.push_back(pos);
			}				
		}
	}
}

void CaminoOptimo(const vector<vector<int>> & matriz, vector<pair<int, int>> & camino, int filas, int columnas) {

	// INICIALIZO A -1 LA MATRIZ QUE QUEDARÁ CON EL CAMINO ÓPTIMO.
	int ** solucion = allocate(filas, columnas);
	InicializarMenosUno(solucion, filas, columnas);

	// OBTENGO UN CAMINO GREEDY BASE PARA EMPEZAR ALGORITMO
	int valor_camino_actual = CaminoGreedy(matriz, solucion, filas, columnas); 

	// COMPROBAMOS LA EXISTENCIA DE MAJORES SOLUCIONES Y EN CASO DE ENCONTRAR PEORES CORTAMOS DICHO CAMINO.
	CaminoFinal(matriz, solucion, filas, columnas, valor_camino_actual);

	// GUARDAMOS LAS POSICIONES POR LAS QUE PASARÁ EL MEJOR CAMINO.
	PosicionesOptimas(solucion, camino, filas, columnas);

	// DIBUJA EL CAMINO ÓPTIMO.
	Dibujar(solucion, filas, columnas);
	
}


int main(int argc, char * argv[]) {
	if (argc < 3) {
		cout << "Error en los argumentos: ./ejecutable filas * columnas" << endl;
		exit(-1);
	}
	int filas = stoi(argv[1]);
	int columnas = stoi(argv[2]);

	if (filas * columnas != argc - 3) {
		cout << "Número de elementos del terreno incorrecto: filas * columnas" << endl;
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

	cout << "Superficie: " << endl;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++)
			cout << matriz[i][j] << " ";
		cout << endl;
	}

	vector<pair<int, int>> camino;
	CaminoOptimo(matriz, camino, filas, columnas);

	cout << "Por lo que pasará por: ";
	for (int i = 0; i < camino.size(); i++) 
		cout  << "[" << camino[i].first << "," << camino[i].second << "]"; 
	cout << endl;

	return 0;
}