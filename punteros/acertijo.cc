#include <iostream>
#include <algorithm>
using namespace std;

// Prototipo
void resolverAcertijo(int* p1, int* p2, int* p3);

int main() {
    int num1, num2, num3;

    cout << "Ingrese el primer número: ";
    cin >> num1;
    cout << "Ingrese el segundo número: ";
    cin >> num2;
    cout << "Ingrese el tercer número: ";
    cin >> num3;

    resolverAcertijo(&num1, &num2, &num3);

    cout << "\nResultados asignados:" << endl;
    cout << "Primer número (Mayor): " << num1 << endl;
    cout << "Segundo número (Menor): " << num2 << endl;
    cout << "Tercer número (Diferencia Mayor - Menor): " << num3 << endl;

    return 0;
}

// Implementación
void resolverAcertijo(int* p1, int* p2, int* p3) {
    int v1 = *p1;
    int v2 = *p2;
    int v3 = *p3;

    int mayor = max({v1, v2, v3});
    int menor = min({v1, v2, v3});
    int diferencia = mayor - menor;

    *p1 = mayor;
    *p2 = menor;
    *p3 = diferencia;
}