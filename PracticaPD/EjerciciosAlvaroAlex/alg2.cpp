#include <bits/stdc++.h>
#include <cstdio>
#define MURO -1
using namespace std;

void CaminosMax(int** tablero, int** caminos, int n_filas, int n_columnas);

vector<string> RecuperarSolucion(int** caminos, int n_filas, int n_columnas);

int MaximoDe3(int el1, int el2, int el3);

int main(int argc, char** argv) {
    int** tablero;
    int** caminos;
    int n_filas, n_columnas;

    cin >> n_filas >> n_columnas;

    tablero = new int* [n_filas];
    caminos = new int* [n_columnas];
    for (int i = 0; i < n_filas; ++i) {
        tablero[i] = new int[n_columnas];
        caminos[i] = new int[n_columnas];
    }

    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cin >> tablero[i][j];
        }
    }

    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << tablero[i][j] << "\t";
        }
        cout << endl;
    }

    CaminosMax(tablero, caminos, n_filas, n_columnas);

    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << caminos[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;

    vector<string> solucion = RecuperarSolucion(caminos, n_filas, n_columnas);

    for (int i = solucion.size(); i >= 0; --i) {
        cout << solucion[i] << " ";
    }
    cout << endl;
}

void CaminosMax(int** tablero, int** caminos, int n_filas, int n_columnas) {
    caminos[0][n_columnas - 1];
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            caminos[i][j] = 0;
        }
    }

    for (int j = n_columnas - 1; j >= 0; --j) {
        caminos[0][j] = tablero[0][j];
        if (tablero[0][j] == MURO) {
            for (; j >= 0; --j) {
                caminos[0][j] = MURO;
            }
        }
    }

    for (int i = 0; i < n_filas; ++i) {
        caminos[i][n_columnas - 1] = tablero[i][n_columnas - 1];
        if (tablero[i][n_columnas - 1] == MURO) {
            for (; i < n_filas; ++i) {
                caminos[i][n_columnas - 1] = MURO;
            }
        }
    }
    cout << endl;
    for (int i = 1; i < n_filas; ++i) {
        for (int j = n_columnas - 2; 0 <= j; --j) {
            if (tablero[i][j] == MURO) {
                caminos[i][j] = MURO;
            } else if (caminos[i - 1][j] == MURO && caminos[i - 1][j + 1] == MURO && caminos[i][j + 1] == MURO) {
                caminos[i][j] = MURO;
            } else {
                caminos[i][j] = tablero[i][j] + MaximoDe3(caminos[i - 1][j], caminos[i - 1][j + 1], caminos[i][j + 1]);
            }
        }
    }
}

int MaximoDe3(int el1, int el2, int el3) {
    int out;
    if (el1 > el2) {
        out = el1 > el3 ? el1 : el3;
    } else {
        out = el3 > el2 ? el3 : el2;
    }
    return out;
}

vector<string> RecuperarSolucion(int** caminos, int n_filas, int n_columnas) {
    int i = n_filas - 1, j = 0;
    vector<string> solucion;
    solucion.reserve(20);
    while (i != 0 && j != n_columnas - 1) {
        string aux;
        if (caminos[i - 1][j] > caminos[i - 1][j + 1]) {
            if (caminos[i - 1][j] > caminos[i][j + 1]) {
                aux = "abajo";
                i--;
            } else {
                aux = "izquierda";
                j++;
            }
        } else {
            if (caminos[i][j + 1] > caminos[i - 1][j + 1]) {
                aux = "izquierda";
                j++;
            } else {
                aux = "diagonal";
                i--;
                j++;
            }
        }
        solucion.push_back(aux);
    }
    for (; i > 0; --i) {
        solucion.push_back("abajo");
    }
    for (; j < n_columnas - 1; ++j) {
        solucion.push_back("izquierda");
    }
    return solucion;
}
