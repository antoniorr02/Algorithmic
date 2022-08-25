/**
 * Línea de ejecución: ./ejecutable prueba2.txt español aleman
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
private:
    int ** _data; //array of double
    vector<string> rowLabels; //Language for row labels
    vector<string> colLabels; //Language for col labels

    

public:

    /**
     * @brief Set the Values object (default to 0)
     * 
     * @param value 
     */
    void setValues(int value = 1000) {
        for (int i = 0; i < rowLabels.size(); i++) {
            for (int j = 0; j < colLabels.size(); j++) {
                _data[i][j] = value;
            }
        }
    }

    /**
     * @brief Set languages availables (without repetitions)
     * 
     * @param labels 
     */
    void setLabels(vector<string> labels) {
        for (int i = 0; i < labels.size()-2; i++) {
            if (insertado(labels[i]) == -1) {
                rowLabels.push_back(labels[i]);
                colLabels.push_back(labels[i]);
            }
        }
    }

    void getLabels() {
        for (int i = 0; i < rowLabels.size(); i++)
            cout << rowLabels[i] << " ";
        cout << endl;
        for (int i = 0; i < colLabels.size(); i++)
            cout << colLabels[i] << " ";
        cout << endl;
    }

    const vector<string> & gettRowLabels() {
    	return rowLabels;
    }

    const vector<string> & gettColLabels() {
    	return colLabels;
    }

    /**
     * @brief Check if exist an element.
     * 
     * @param language to search
     * @return int Pos of the language.
     */
    int insertado(string & language) {
        for (int i = 0; i < rowLabels.size(); i++) {
            if (rowLabels[i] == language) return i;
        }
        return -1;
    }

    /** 
     * @brief this method reserve memory to allocate a 2D matrix of size r x c.
     * @param r number of rows
     * @param c number of cols
     * @return the pointer to the memory block containing the data
     */
    int ** allocate(int r, int c) {
        int ** block;
        // allocate memory into block
        block = new int * [r];
        for (int i = 0; i < r; i++) {
            block[i] = new int [c];
        }
        return block;
    }

    /**
     * @brief Free the memory allocated for the matrix, i.e., pointed by _data.
     * @post _data is set to nullptr 
     */
    void deallocate() {
	    if (_data != nullptr) {
	        for (int i = 0; i < rowLabels.size(); i++) {
	            delete[] _data[i];
	            _data[i] = nullptr;
	        }
	        delete[] _data;
	    }
	    _data = nullptr;
	}

    /**
     * @brief Create de adyaceny matrix
     * 
     * @param labels Vector with the diferents languages.
     * @return Matrix 
     */
    void MatrizAdy(vector<string> labels) {
        setLabels(labels); // Inserto los idiomas en las filas y columnas
        _data = allocate(rowLabels.size(), colLabels.size()); // Reservo memoria para la matriz.
        setValues(); // Inicializo toda la matriz a 0.
        int row, col;
        for (int i = 0; i < labels.size(); i+=2) { // Avanzo de 2 en 2 por la forma en la que leeré del fichero de entrada.
            row = insertado(labels[i]);
            col = insertado(labels[i+1]);
            if (col != -1 && row != -1) {
                _data[row][col] = 1;
                _data[col][row] = 1;
            }
        } // Pongo a 1 las posiciones en las que existen diccionarios (bidireccional).
        //return *this;
    }

    int getValue(int row, int col) {
    	return _data[row][col];
    }

	/**
	 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
	 * It is assumed that org and dest have the memory properly allocated 
	 * @param dest destination matrix
	 * @param org  source matrix
	 * @param nrows number of rows
	 * @param ncols number of cols
	 * @param aux La he añadido para ahorrarme un bucle dentro del algoritmo.
	 */
	void copy(int **dest, int **org, int nrows, int ncols, int ** aux) {
	    for (int i = 0; i < nrows; i++) {
	        for (int j = 0; j < ncols; j++) {
	            dest[i][j] = org[i][j];
	            aux[i][j] = -1;
	        }
	    }
	}

	vector<int> Camino(int **valores, int pos_idioma_1, int pos_idioma_2) {
		vector<int> solucion;
		int valor = valores[pos_idioma_1][pos_idioma_2];
		if (valor != -1) {
			solucion = Camino(valores, pos_idioma_1, valor);
			solucion.push_back(valor);
		}
		return solucion;
	}

    vector<string> traduccionOptima(int pos_idioma_1, int pos_idioma_2) {
    	vector<string> solucion;
    	vector<int> solucion_num;
    	int **valores = allocate(rowLabels.size(), colLabels.size());
    	int **copia = allocate(rowLabels.size(), colLabels.size());
    	copy(copia, _data, rowLabels.size(), colLabels.size(), valores);
        for (int i = 0; i < rowLabels.size(); i++) 
            copia[i][i] = 0;

    	for (int k = 0; k < rowLabels.size(); k++) {
	    	for (int i = 0; i < rowLabels.size(); i++) {
	    		for (int j = 0; j < colLabels.size(); j++) {
	    			if (copia[i][k] + copia[k][j] < copia[i][j]) {
	    				int valor = copia[i][k] + copia[k][j];
	    				copia[i][j] = valor;
	    				valores[i][j] = k;
	    			}
	    		}
	    	}
	    }
	    //////////////////////////////////////// IMPRIME LA MATRIZ DE CAMINOS
        cout << "Matriz de caminos: " << endl;
	    for (int k = 0; k != rowLabels.size(); k++) {
	    	for (int i = 0; i < rowLabels.size(); i++) {
	    		cout << valores[k][i] << " ";
	    	}
	    	cout << endl;
	    }
        cout << endl;
	    //////////////////////////////////////////	    
	    solucion_num = Camino(valores, pos_idioma_1, pos_idioma_2);
	    for (int i = 0; i < solucion_num.size(); i++) {
	    	solucion.push_back(colLabels[solucion_num[i]]);
	    }

    	return solucion;
    }

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m);

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream & operator<<(ostream & flujo, const Matrix& m) {
    flujo << m.rowLabels.size() << " " << m.colLabels.size();
    flujo << setw(6) << std::right << "|" << "  ";
    for (int i = 0; i < m.colLabels.size(); i++)
        flujo << setw(6) << std::right << m.colLabels.at(i) << " ";
    flujo << endl << " ";

    for (int i = 0; i < m.rowLabels.size(); i++) {
        if (m.rowLabels.size() > 0)
            flujo << setw(9) << std::right << m.rowLabels.at(i);
        for (int j = 0; j < m.colLabels.size(); j++) {
            flujo << setw(7) << setprecision(2) << std::right << m._data[i][j] << " ";
        }
        flujo << endl;
    }
    return flujo;     
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
    // Comprobamos los argumentos de entrada.
    /**
     * El fichero de entrada debería tener una estructura tal que:
     *  Español Inglés
     *  Francés Aleman
     *  Portugués Italiano
     *  ...
     */
    if (argc < 4) {
        cout << "Error en los argumentos: ./ejecutable fichero_Diccionarios idioma_1 idioma_2" << endl;
        exit(-1);
    }

    // Hacemos la lectura de los datos de fichero en un vector.
    vector<string> labels;
    ifstream File1;
    File1.open(argv[1]);
    if (File1.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    char delimitador = ' ';
    while (!File1.eof()){
        string input1, input2;
        getline(File1, input1, delimitador);
        getline(File1, input2);
        labels.push_back(input1);
        labels.push_back(input2);
    }

    // Almacenamos nuestros datos en la matriz de adyacencia.
    
    Matrix matriz;
    matriz.MatrizAdy(labels);

    // Imprimimos nuestra matriz de adyacencia.
    cout << matriz << endl;

    // Comprobamos que ambos idiomas están entre los disponibles.
    string idioma_1 = argv[2];
    string idioma_2 = argv[3];
    int pos_idioma_1 = matriz.insertado(idioma_1);
    int pos_idioma_2 = matriz.insertado(idioma_2);
    // Caso base 1.
    if (pos_idioma_1 == -1 || pos_idioma_2 == -1) {
    	cout << "No existe traducción posible, alguno de los lenguajes seleccionados no aparece en ninguno de los diccionarios disponibles" << endl;
    	matriz.deallocate();
    	exit(-1);
    }

    // Comprobamos si hay traducción directa con el if, en caso contrario comprobaremos si es posible la indirecta.
    vector<string> solucion;
    int value = matriz.getValue(pos_idioma_1, pos_idioma_2);
    // Caso base 2.
    if (value == 1)
    	cout << "La traducción es posible y además es directa entre: " << idioma_1 << " y " << idioma_2 << endl;
    else {
    	// Caso general.
    	solucion = matriz.traduccionOptima(pos_idioma_1, pos_idioma_2);
    	if (!solucion.empty()) {
		    cout << "Resultando la traducción más corta posible mediante: " << idioma_1 << " ";
		    for (int i = 0;i < solucion.size(); i++) {
		    	cout << solucion[i] << " ";
		    }
            cout << idioma_2 << endl;
		} else 
			cout << "No hay traducción posible mediante los diccionarios disponibles" << endl;
	}

    matriz.deallocate();
}