#include <iostream>
#include <string>
using namespace std;

struct Producto {
    string nombre;
    double precio;
};

// Prototipo
const Producto* obtenerProductoMasCaro(const Producto* arr, int tam);

int main() {
    int tam;
    cout << "Ingrese la cantidad de productos a registrar: ";
    cin >> tam;

    if (tam <= 0) return 0;

    Producto* catalogo = new Producto[tam];

    for (int i = 0; i < tam; i++) {
        cout << "\nProducto " << i + 1 << " - Nombre: ";
        cin >> catalogo[i].nombre;
        cout << "Producto " << i + 1 << " - Precio: ";
        cin >> catalogo[i].precio;
    }

    const Producto* caro = obtenerProductoMasCaro(catalogo, tam);

    if (caro != nullptr) {
        cout << "\n--- Producto Más Caro ---" << endl;
        cout << "Nombre: " << caro->nombre << endl;
        cout << "Precio: $" << caro->precio << endl;
    }

    delete[] catalogo;
    return 0;
}

// Implementación
const Producto* obtenerProductoMasCaro(const Producto* arr, int tam) {
    if (tam <= 0 || arr == nullptr) return nullptr;

    const Producto* masCaro = arr;
    for (int i = 1; i < tam; i++) {
        if ((arr + i)->precio > masCaro->precio) {
            masCaro = arr + i;
        }
    }
    return masCaro;
}