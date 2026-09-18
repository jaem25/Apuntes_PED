#include <iostream>
using namespace std;

// Prototipo
void depositar(double* saldo, double cantidad);

int main() {
    double saldoCuenta, deposito;

    cout << "Ingrese el saldo inicial de la cuenta: ";
    cin >> saldoCuenta;

    cout << "Ingrese la cantidad a depositar: ";
    cin >> deposito;

    depositar(&saldoCuenta, deposito);

    cout << "Saldo actualizado: $" << saldoCuenta << endl;
    return 0;
}

// Implementación
void depositar(double* saldo, double cantidad) {
    if (saldo != nullptr && cantidad > 0) {
        *saldo += cantidad;
    }
}