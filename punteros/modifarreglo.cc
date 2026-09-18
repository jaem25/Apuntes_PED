#include <iostream>
using namespace std;

// Prototipo
void reemplazarNegativos(int* ptr, int tam);

int main() {
    int tam;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> tam;

    if (tam <= 0) return 0;

    int* datos = new int[tam];

    for (int i = 0; i < tam; i++) {
        cout << "Ingrese valor [" << i << "]: ";
        cin >> datos[i];
    }

    reemplazarNegativos(datos, tam);

    cout << "\nArreglo corregido (sin negativos): ";
    for (int i = 0; i < tam; i++) {
        cout << datos[i] << " ";
    }
    cout << endl;

    delete[] datos;
    return 0;
}

// Implementación
void reemplazarNegativos(int* ptr, int tam) {
    for (int i = 0; i < tam; i++) {
        if (*ptr < 0) {
            *ptr = 0;
        }
        ptr++;
    }
}