#include <iostream>
using namespace std;

// Prototipo
void clasificarNumeros(const int* arr, int tam, int* pos, int* neg, int* ceros);

int main() {
    int tam;
    cout << "Ingrese la cantidad de números a evaluar: ";
    cin >> tam;

    if (tam <= 0) return 0;

    int* numeros = new int[tam];
    for (int i = 0; i < tam; i++) {
        cout << "Ingrese el número " << i + 1 << ": ";
        cin >> numeros[i];
    }

    int positivos, negativos, ceros;
    clasificarNumeros(numeros, tam, &positivos, &negativos, &ceros);

    cout << "\nResultados:" << endl;
    cout << "Cantidad de positivos: " << positivos << endl;
    cout << "Cantidad de negativos: " << negativos << endl;
    cout << "Cantidad de ceros: " << ceros << endl;

    delete[] numeros;
    return 0;
}

// Implementación
void clasificarNumeros(const int* arr, int tam, int* pos, int* neg, int* ceros) {
    *pos = 0;
    *neg = 0;
    *ceros = 0;

    for (int i = 0; i < tam; i++) {
        if (*(arr + i) > 0) {
            (*pos)++;
        } else if (*(arr + i) < 0) {
            (*neg)++;
        } else {
            (*ceros)++;
        }
    }
}