#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
using namespace std;

const int Filas = 10;
const int Columnas = 10;
char matriz[Filas][Columnas];

bool Camino(int x, int y, int salida_x, int salida_y) { // funcion para encontrar el camino mas corto, devuelve si es verdadero o falso
    if (x == salida_x && y == salida_y) { // con este if podremos ver si llegamos a la salida del laberinto y por ende terminar el laberinto retornando un verdadero
        matriz[x][y] = '*';
        return true;
    }

    if (x < 0 || x >= Filas || y < 0 || y >= Columnas || matriz[x][y] == '1' || matriz[x][y] == '*') {
        return false;
    }

    matriz[x][y] = '*'; // marcamos la posicion actual

    //nos intentamos mover hacia las 4 direcciones posibles desde la posicion actual, si una de las 4 posiciones encuentra un camino (arriba, abajo, izquierda, derecha) valido se devuelve verdadero	
    if (Camino(x + 1, y, salida_x, salida_y) || Camino(x, y + 1, salida_x, salida_y) || Camino(x - 1, y, salida_x, salida_y) || Camino(x, y - 1, salida_x, salida_y)) {
        return true;
    }

    matriz[x][y] = '0'; // no encontro una salida, por lo que el camino es incorrecto, marcamos con un 0 la posicion
    return false;
}

void DetectarEntradaSalida(int& entrada_x, int& entrada_y, int& salida_x, int& salida_y) {

    for (int j = 0; j < Columnas; j++) { // buscamos si en la fila 0 hay una pared que contenga la entrada (representada con un 0)
        if (matriz[0][j] == '0') {
            entrada_x = 0;
            entrada_y = j;
            break;
        }
    }
    for (int i = 0; i < Filas; i++) { // buscamos si en la columna 0 hay una pared que contenga la entrada (representada con un 0)
        if (matriz[i][0] == '0') {
            entrada_x = i;
            entrada_y = 0;
            break;
        }
    }

    // Detectar salida
    for (int j = 0; j < Columnas; j++) {// buscamos si en la Fila inferior hay un 0 que represente la salida
        if (matriz[Filas - 1][j] == '0') {
            salida_x = Filas - 1;
            salida_y = j;
            break;
        }
    }
    for (int i = 0; i < Filas; i++) {
        if (matriz[i][Columnas - 1] == '0') {// buscamos si en la Columna derecha hay un 0 que represente la salida
            salida_x = i;
            salida_y = Columnas - 1;
            break;
        }
    }
}

void Leer_Laberinto() {
    string Nombre_archivo;
    string si = ".txt";

    cout << "Ingrese el nombre del archivo: ";
    cin >> Nombre_archivo;
    cout << endl;
    ifstream archivo((Nombre_archivo + si).c_str());
    char paredes = 219; //codigo ascii de las paredes

    if (!archivo.is_open()) { // la funcion is_opnen es propia de fstream
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    for (int i = 0; i < Filas; i++) { // pasamos los archivos desde el txt hacia la matriz
        for (int j = 0; j < Columnas; j++) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close(); // cerramos la lectura del txt

    int entrada_x, entrada_y, salida_x, salida_y;
    DetectarEntradaSalida(entrada_x, entrada_y, salida_x, salida_y); // llamamos a la funcion DetectarEntradaSalida para saber donde se ubica la entrada y salida del laberinto y poder comenzar el camino

    Camino(entrada_x, entrada_y, salida_x, salida_y);  // buscamos el camino

    ofstream archivo_solucion("Laberinto_solucion.txt"); // Nuevo archivo para escribir la solución

    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Columnas; j++) {
            if (matriz[i][j] == '1') {
                cout << paredes << paredes; // imprimimos las paredes del laberinto con el codigo ascii 219 el cual es un bloque, llamamos 2 veces a paredes para que se vea mas estetico
                archivo_solucion << "1 "; // guardamos en el archivo con un 1 para representar las paredes
            }
            else if (matriz[i][j] == '*') {
                cout << "**";  // imprimimos el camino con asteriscos
                archivo_solucion << "* "; // Guardamos el camino con asteriscos en el txt
            }
            else {
                cout << "  "; // imprimimos todos los posibles caminos con un espacio en blanco 
                archivo_solucion << "0 "; // Guardamos como 0 los espacios en blanco dentro del txt
            }
        }
        cout << endl;
        archivo_solucion << endl;
    }

    archivo_solucion.close();
}

int main() {
    Leer_Laberinto();
    return 0;
}


