#include <iostream>
using namespace std;

struct Cuenta {
    double saldo;
};

// Prototipo
bool realizarRetiro(Cuenta& c, double monto);

int main() {
    Cuenta cuenta;
    double retiro;

    cout << "Ingrese el saldo inicial de la cuenta: ";
    cin >> cuenta.saldo;

    cout << "Ingrese el monto que desea retirar: ";
    cin >> retiro;

    if (realizarRetiro(cuenta, retiro)) {
        cout << "Transacción exitosa. Saldo restante: $" << cuenta.saldo << endl;
    } else {
        cout << "Transacción fallida: fondos insuficientes o monto inválido." << endl;
    }

    return 0;
}

// Implementación
bool realizarRetiro(Cuenta& c, double monto) {
    if (monto > 0 && c.saldo >= monto) {
        c.saldo -= monto;
        return true;
    }
    return false;
}