#include <iostream>
using namespace std;

struct Numero {
    int valor;
};

// Prototipo
Numero* obtenerMayor(Numero* arr, int tam);

int main() {
    int tam;
    cout << "Ingrese la cantidad de números a comparar: ";
    cin >> tam;

    if (tam <= 0) return 0;

    Numero* lista = new Numero[tam];

    for (int i = 0; i < tam; i++) {
        cout << "Ingrese valor [" << i + 1 << "]: ";
        cin >> lista[i].valor;
    }

    Numero* mayorNum = obtenerMayor(lista, tam);

    if (mayorNum != nullptr) {
        cout << "\nEl número mayor ingresado es: " << mayorNum->valor << endl;
    }

    delete[] lista;
    return 0;
}

// Implementación
Numero* obtenerMayor(Numero* arr, int tam) {
    if (tam <= 0 || arr == nullptr) return nullptr;

    Numero* mayor = arr;
    for (int i = 1; i < tam; i++) {
        if ((arr + i)->valor > mayor->valor) {
            mayor = arr + i;
        }
    }
    return mayor;
}