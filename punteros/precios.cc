#include <iostream>
using namespace std;

// Prototipo
void aplicarAumento(double* arr, int tam);

int main() {
    int tam;
    cout << "Ingrese la cantidad de productos: ";
    cin >> tam;

    if (tam <= 0) return 0;

    double* precios = new double[tam];

    for (int i = 0; i < tam; i++) {
        cout << "Ingrese el precio del producto " << i + 1 << ": ";
        cin >> precios[i];
    }

    aplicarAumento(precios, tam);

    cout << "\nPrecios ajustados (+10%):" << endl;
    for (int i = 0; i < tam; i++) {
        cout << "Producto " << i + 1 << ": $" << precios[i] << endl;
    }

    delete[] precios;
    return 0;
}

// Implementación
void aplicarAumento(double* arr, int tam) {
    double* ptr = arr;
    for (int i = 0; i < tam; i++) {
        *ptr *= 1.10;
        ptr++;
    }
}