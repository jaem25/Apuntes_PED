#include <iostream>
using namespace std;

// Prototipo
void intercambiar(int* a, int* b);

int main() {
    int x, y;

    cout << "Ingrese el primer número entero (A): ";
    cin >> x;
    cout << "Ingrese el segundo número entero (B): ";
    cin >> y;

    cout << "\nValores ingresados: A = " << x << ", B = " << y << endl;

    intercambiar(&x, &y);

    cout << "Valores intercambiados: A = " << x << ", B = " << y << endl;
    return 0;
}

// Implementación
void intercambiar(int* a, int* b) {
    if (a != nullptr && b != nullptr) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}