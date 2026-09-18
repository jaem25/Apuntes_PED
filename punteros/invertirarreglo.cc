#include <iostream>
using namespace std;

// Prototipo
void invertirArreglo(int* arr, int tam);

int main() {
    int tam;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> tam;

    if (tam <= 0) return 0;

    int* numeros = new int[tam];

    for (int i = 0; i < tam; i++) {
        cout << "Elemento [" << i << "]: ";
        cin >> numeros[i];
    }

    invertirArreglo(numeros, tam);

    cout << "\nArreglo invertido: ";
    for (int i = 0; i < tam; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    delete[] numeros;
    return 0;
}

// Implementación
void invertirArreglo(int* arr, int tam) {
    int* inicio = arr;
    int* fin = arr + tam - 1;

    while (inicio < fin) {
        int temp = *inicio;
        *inicio = *fin;
        *fin = temp;

        inicio++;
        fin--;
    }
}