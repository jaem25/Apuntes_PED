#include <iostream>
using namespace std;

struct Rectangulo {
    double ancho;
    double alto;
};

// Prototipos
void corregirDimensiones(Rectangulo& r);
double calcularArea(const Rectangulo& r);

int main() {
    Rectangulo rect;

    cout << "Ingrese el ancho del rectángulo: ";
    cin >> rect.ancho;
    cout << "Ingrese el alto del rectángulo: ";
    cin >> rect.alto;

    corregirDimensiones(rect);
    double area = calcularArea(rect);

    cout << "\nDimensiones finales corregidas: " << rect.ancho << " x " << rect.alto << endl;
    cout << "Área calculada: " << area << endl;

    return 0;
}

// Implementaciones
void corregirDimensiones(Rectangulo& r) {
    if (r.ancho < 0) r.ancho = 0;
    if (r.alto < 0) r.alto = 0;
}

double calcularArea(const Rectangulo& r) {
    return r.ancho * r.alto;
}