#include <iostream>
using namespace std;

struct Persona {
    int edad;
    double altura;
};

// Prototipo
void verificarEIntercambiar(Persona& p1, Persona& p2);

int main() {
    Persona p1, p2;

    cout << "Persona 1 - Ingrese edad y altura (ejemplo: 20 1.75): ";
    cin >> p1.edad >> p1.altura;

    cout << "Persona 2 - Ingrese edad y altura (ejemplo: 25 1.80): ";
    cin >> p2.edad >> p2.altura;

    verificarEIntercambiar(p1, p2);

    cout << "\nResultado tras evaluar:" << endl;
    cout << "Persona 1 -> Edad: " << p1.edad << ", Altura: " << p1.altura << endl;
    cout << "Persona 2 -> Edad: " << p2.edad << ", Altura: " << p2.altura << endl;

    return 0;
}

// Implementación
void verificarEIntercambiar(Persona& p1, Persona& p2) {
    if (p1.edad < p2.edad) {
        int tempEdad = p1.edad;
        p1.edad = p2.edad;
        p2.edad = tempEdad;
    }
}