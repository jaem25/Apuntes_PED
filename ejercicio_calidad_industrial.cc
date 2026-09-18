#include <iostream>
#include <string>

struct Pieza {
    std::string codigo;
    float peso;
    float longitud;
    bool aprobada;
};

int main() {
    int n = 0;
    std::cout << "Numero de piezas a evaluar en la inspeccion: ";
    std::cin >> n;

    Pieza* lote = new Pieza[n];

    for (int i = 0; i < n; i++) {
        std::cout << "\n--- Inspeccionando Pieza #" << (i + 1) << " ---\n";
        std::cout << "Codigo: "; std::cin >> lote[i].codigo;
        std::cout << "Peso (Gramos [Valido: 90 - 110]): "; std::cin >> lote[i].peso;
        std::cout << "Longitud (Cm [Valido: 9.5 - 10.5]): "; std::cin >> lote[i].longitud;

        if (lote[i].peso >= 90.0f && lote[i].peso <= 110.0f &&
            lote[i].longitud >= 9.5f && lote[i].longitud <= 10.5f) {
            lote[i].aprobada = true;
        } else {
            lote[i].aprobada = false;
        }
    }

    int aprobadas = 0, defectuosas = 0, idx_mas_pesada = 0;
    float suma_peso = 0.0f;

    for (int i = 0; i < n; i++) {
        suma_peso += lote[i].peso;

        if (lote[i].aprobada) {
            aprobadas++;
        } else {
            defectuosas++;
        }

        if (lote[i].peso > lote[idx_mas_pesada].peso) {
            idx_mas_pesada = i;
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "     INFORME DE CONTROL DE CALIDAD       \n";
    std::cout << "=========================================\n";
    std::cout << "Piezas aprobadas:   " << aprobadas << "\n";
    std::cout << "Piezas defectuosas: " << defectuosas << "\n";
    std::cout << "Peso promedio:      " << (suma_peso / n) << " g\n";
    std::cout << "Pieza mas pesada:   Codigo " << lote[idx_mas_pesada].codigo 
            << " (" << lote[idx_mas_pesada].peso << " g)\n";

    delete[] lote;
    return 0;
}

/*11. Control de calidad industrial
Una fábrica produce una serie de piezas que posteriormente pasan por un proceso de
control de calidad. Para cada pieza se registra un código, peso, longitud y estado de
inspección.
Una pieza se considera defectuosa cuando su peso está fuera del rango permitido de
90 a 110 gramos, o cuando su longitud está fuera del rango de 9.5 a 10.5 centímetros.
El programa deberá analizar las piezas y determinar automáticamente cuáles cumplen
con los estándares establecidos.
Al finalizar, deberá mostrar la cantidad de piezas aprobadas y defectuosas, el peso
promedio de todas las piezas y la pieza que presentó el mayor peso.*/