#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

static const int N = 3;

int MinimoDe3(int el1, int el2, int el3, vector<vector <pair <int , int>>> &ruta, int i, int j) {
    int out;
    if (el1 < el2) {
        if(el1 < el3){
            out = el1;
            ruta[i][j].first= i;
            ruta[i][j].second= j-1;
        }else{
            out = el3;
            ruta[i][j].first= i+1;
            ruta[i][j].second= j;
        }
    } else {
        if(el3 < el2){
            out = el3;
            ruta[i][j].first= i+1;
            ruta[i][j].second= j;
        }else{
            out = el2;
            ruta[i][j].first= i+1;
            ruta[i][j].second= j-1;
        }
    }
    return out;
}

vector <pair <int, int>> recuperarCamino(vector<vector<pair<int, int>>> &ruta, int fila, int columna){
    vector <pair <int, int>> solucion;
    pair <int, int> aux;
    int i = ruta[fila][columna].first;
    int j = ruta[fila][columna].second;
 
    if(i!=2 && j!= 0){
        solucion = recuperarCamino(ruta, i, j);
        aux.first = i;
        aux.second = j;
        solucion.push_back(aux);
            
    }
    
    return solucion;
}




vector <pair <int, int>> caminoMinimo(int** mapa, int** caminos, int nfilas, int ncolumnas){
    vector<vector<pair<int, int>>> ruta;
    vector <pair <int, int>> solucion;
    pair <int, int> aux;

    ruta.resize(nfilas);
    for(int i=0; i<nfilas; ++i){
        ruta[i].resize(ncolumnas);
    }

    for (int i = 0; i < nfilas; ++i) {
        for (int j = 0; j < ncolumnas; ++j) {
            caminos[i][j] = 1000;
        }
    }

    caminos[nfilas-1][0]= 0;
    caminos[0][ncolumnas-1]= 0;

    for(int i=nfilas-2; i>=0; --i){
        caminos[i][0]= mapa[i][0] + mapa[i+1][0];
        ruta[i][0].first = i+1;
        ruta[i][0].second = 0;
    }
    
    for(int i= 1; i<ncolumnas; ++i){
        caminos[nfilas-1][i]= mapa[nfilas-1][i]+mapa[nfilas-1][i-1];
        ruta[nfilas-1][i].first = nfilas-1;
        ruta[nfilas-1][i].second = i-1;
    }

    for(int i= nfilas-2; i>=0; --i){
        for(int j= 1; j<ncolumnas; ++j){
            caminos[i][j]= mapa[i][j] + MinimoDe3(caminos[i][j-1], caminos[i+1][j-1], caminos[i+1][j], ruta, i, j);
        }
    }
    
    solucion= recuperarCamino(ruta, 0, ncolumnas-1);

    return solucion;

}



int main(int argc, char** argv){
    int** mapa;
    int** caminos;
    int n_filas, n_columnas;
    vector <pair <int, int>> solucion;
    pair <int, int> aux;

    cin >> n_filas >> n_columnas;

    mapa = new int* [n_filas];
    caminos = new int* [n_columnas];
    for (int i = 0; i < n_filas; ++i) {
        mapa[i] = new int[n_columnas];
        caminos[i] = new int[n_columnas];
    }

    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cin >> mapa[i][j];
        }
    }

    cout << "El mapa es: " << endl;
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << mapa[i][j] << "\t";
        }
        cout << endl;
    }

    solucion= caminoMinimo(mapa, caminos, n_filas, n_columnas);
    if(solucion.size()>0){
        aux.first = 0;
        aux.second = 0;
        solucion.push_back(aux);
        aux.first = 2;
        aux.second = 0;
        solucion.insert(solucion.begin(), aux);
    }

    cout << "Los caminos obtenidos son: " << endl;
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << caminos[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "El camino minimo es: " << endl;
    for(int i= 0; i<solucion.size(); ++i){
        cout << "(" << solucion[i].first << ", " << solucion[i].second << ")\t";
    }
    cout<<endl;

    return 0;
}