/**
 * Línea de ejecución: ./ejecutable 3 3 1 2 0 1 4 2 0 2 3
 */

#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

/**
 * Elementos de la matriz:
 * Salida y llegada --> 0
 * Dificultad en rango de 1 a INFINITO.
 */
void ComprobarEntradasSalidas(vector<vector<int>> matriz, int filas, int columnas) {
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ** allocate(int r, int c) {
    int ** block;
    // allocate memory into block
    block = new int * [r];
    for (int i = 0; i < r; i++) {
        block[i] = new int [c];
    }
    return block;
}

pair<int, int> ** allocate_pair(int r, int c) {
    pair<int, int> ** block;
    // allocate memory into block
    block = new pair<int, int> * [r];
    for (int i = 0; i < r; i++) {
        block[i] = new pair<int, int> [c];
    }
    return block;
}

int MejorCasilla(pair<int, int> ** temp, int lado, int diagonal, int arriba, int i, int j) {
    int elegido;
    if (lado < diagonal) {
        if(lado < arriba){
            elegido = lado;
            temp[i][j].first= i;
            temp[i][j].second= j-1;
        }else{
            elegido = arriba;
            temp[i][j].first= i+1;
            temp[i][j].second= j;
        }
    } else {
        if(arriba < diagonal) {
            elegido = arriba;
            temp[i][j].first= i+1;
            temp[i][j].second= j;
        } else {
            elegido = diagonal;
            temp[i][j].first= i+1;
            temp[i][j].second= j-1;
        }
    }
    return elegido;
}

vector <pair <int, int>> recuperarCamino(pair<int, int> ** temp, int filas, int fila_pos, int columna_pos){
    vector <pair <int, int>> solucion;
    pair <int, int> aux;
    int i = temp[fila_pos][columna_pos].first;
    int j = temp[fila_pos][columna_pos].second;
 
    if(i != filas-1 || j  != 0) {
        solucion= recuperarCamino(temp, filas, i, j);
        aux.first = i;
        aux.second = j;
        solucion.push_back(aux);
    }
    
    return solucion;
}

void setValues(int ** caminos, int filas, int columnas, int value = 1000) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            caminos[i][j] = value;
        }
    }
    caminos[filas-1][0]= 0; // Llegada
    caminos[0][columnas-1]= 0; // Salida
}

vector <pair <int, int>> CaminoOptimo(vector<vector<int>> terreno, int filas, int columnas){
	int ** caminos = allocate(filas, columnas);
    pair<int, int> ** temp = allocate_pair(filas, columnas);
    vector <pair <int, int>> solucion;
    pair <int, int> aux;

    setValues(caminos, filas, columnas);

    for(int i=filas-2; i>=0; --i){
        caminos[i][0] = terreno[i][0] + terreno[i+1][0];
        temp[i][0].first = i+1;
        temp[i][0].second = 0;
    }
    
    for(int i= 1; i < columnas; i++){
        caminos[filas-1][i]= terreno[filas-1][i] + terreno[filas-1][i-1];
        temp[filas-1][i].first = filas-1;
        temp[filas-1][i].second = i-1;
    }

    for(int i = filas-2; i >= 0; i--){
        for(int j= 1; j<columnas; j++){
            caminos[i][j]= terreno[i][j] + MejorCasilla(temp, caminos[i][j-1], caminos[i+1][j-1], caminos[i+1][j], i, j);
        }
    }
    
    solucion = recuperarCamino(temp, filas, 0, columnas-1);

    cout << endl << "Los caminos obtenidos son: " << endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << " " << setw(3) << setprecision(2) << caminos[i][j];
        }
        cout << endl;
    }

    return solucion;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			cout << " " << setw(3) << setprecision(2) << matriz[i][j];
		cout << endl;
	}

	vector<pair<int, int>> posiciones = CaminoOptimo(matriz, filas, columnas);
    pair <int, int> in_out;
	if(posiciones.size()>0){
        in_out.first = filas-1;
        in_out.second = 0;
        posiciones.insert(posiciones.begin(), in_out);
        in_out.first = 0;
        in_out.second = columnas-1;
        posiciones.push_back(in_out);
    }

    cout << endl << "El camino por el que tendrá terrenos con menos dificultad para llegar será: ";
	for (int i = 0; i < posiciones.size(); i++) 
		cout << "[" << posiciones[i].first << "," << posiciones[i].second << "]"; 
	cout << endl;

	return 0;
}