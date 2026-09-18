#include <iostream>
using namespace std;

struct Producto {
    double precio;
    int cantidad;
};

// Prototipo
double calcularYModificarTotal(Producto* prod, int limiteCantidad, double nuevoPrecio);

int main() {
    Producto prod;
    int limite;
    double precioDescuento;

    cout << "Ingrese el precio base del producto: ";
    cin >> prod.precio;
    cout << "Ingrese la cantidad a llevar: ";
    cin >> prod.cantidad;

    cout << "Ingrese el límite de cantidad para aplicar oferta: ";
    cin >> limite;
    cout << "Ingrese el nuevo precio si supera el límite: ";
    cin >> precioDescuento;

    double total = calcularYModificarTotal(&prod, limite, precioDescuento);

    cout << "\nPrecio asignado por unidad: $" << prod.precio << endl;
    cout << "Monto total a pagar: $" << total << endl;

    return 0;
}

// Implementación
double calcularYModificarTotal(Producto* prod, int limiteCantidad, double nuevoPrecio) {
    if (prod == nullptr) return 0.0;

    if (prod->cantidad > limiteCantidad) {
        prod->precio = nuevoPrecio;
    }
    return prod->precio * prod->cantidad;
}