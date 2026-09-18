#include <iostream>
#include <string>
using namespace std;

struct Estudiante {
    string nombre;
    double nota;
};

// Prototipo
const Estudiante& obtenerMejorEstudiante(const Estudiante& e1, const Estudiante& e2);

int main() {
    Estudiante e1, e2;

    cout << "Nombre del primer estudiante: ";
    cin >> e1.nombre;
    cout << "Nota de " << e1.nombre << ": ";
    cin >> e1.nota;

    cout << "Nombre del segundo estudiante: ";
    cin >> e2.nombre;
    cout << "Nota de " << e2.nombre << ": ";
    cin >> e2.nota;

    const Estudiante& mejor = obtenerMejorEstudiante(e1, e2);

    cout << "\nEl estudiante con mayor nota es: " 
        << mejor.nombre << " con una nota de " << mejor.nota << endl;

    return 0;
}

// Implementación
const Estudiante& obtenerMejorEstudiante(const Estudiante& e1, const Estudiante& e2) {
    return (e1.nota >= e2.nota) ? e1 : e2;
}