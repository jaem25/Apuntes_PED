#include <iostream>
#include <string>
#include <vector>

struct Robot {
    std::string nombre;
    int victorias;
    int derrotas;
    int empates;
    int puntos;
};

// Declaración de funciones
void MostrarClasificacion(const std::vector<Robot>& torneo);
void RegistrarEnfrentamiento(std::vector<Robot>& torneo);
void MostrarReporteFinal(std::vector<Robot> torneo);

int main() {
    // Inicialización del torneo con participantes
    std::vector<Robot> torneo = {
        {"RoboCop", 0, 0, 0, 0},
        {"Terminator", 0, 0, 0, 0},
        {"Wall-E", 0, 0, 0, 0},
        {"Optimus", 0, 0, 0, 0}
    };

    int opcion = 0;

    do {
        std::cout << "\n=========================================\n";
        std::cout << "      SISTEMA DE TORNEO DE ROBOTS        \n";
        std::cout << "=========================================\n";
        std::cout << "1. Ver tabla de posiciones actual\n";
        std::cout << "2. Registrar resultado de enfrentamiento\n";
        std::cout << "3. Finalizar torneo y ver reporte final\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                MostrarClasificacion(torneo);
                break;
            case 2:
                RegistrarEnfrentamiento(torneo);
                break;
            case 3:
                MostrarReporteFinal(torneo);
                break;
            case 4:
                std::cout << "\nSaliendo del sistema de torneo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}

// 1. Muestra la lista de robots con sus estadísticas
void MostrarClasificacion(const std::vector<Robot>& torneo) {
    std::cout << "\n--- TABLA DE POSICIONES ---\n";
    for (size_t i = 0; i < torneo.size(); ++i) {
        std::cout << (i + 1) << ". " << torneo[i].nombre 
                << " | Puntos: " << torneo[i].puntos
                << " | V: " << torneo[i].victorias
                << " | E: " << torneo[i].empates
                << " | D: " << torneo[i].derrotas << "\n";
    }
}

// 2. Registra el combate entre dos robots y actualiza sus puntajes
void RegistrarEnfrentamiento(std::vector<Robot>& torneo) {
    MostrarClasificacion(torneo);

    int r1 = 0, r2 = 0;
    std::cout << "\nSeleccione el numero del primer robot: ";
    std::cin >> r1;
    std::cout << "Seleccione el numero del segundo robot: ";
    std::cin >> r2;

    // Validaciones de selección
    if (r1 < 1 || r1 > static_cast<int>(torneo.size()) || 
        r2 < 1 || r2 > static_cast<int>(torneo.size())) {
        std::cout << "ERROR: Uno o ambos robots seleccionados no existen.\n";
        return;
    }

    if (r1 == r2) {
        std::cout << "ERROR: Un robot no puede enfrentarse a si mismo.\n";
        return;
    }

    Robot& robot1 = torneo[r1 - 1];
    Robot& robot2 = torneo[r2 - 1];

    int resultado = 0;
    std::cout << "\n--- RESULTADO DEL COMBATE ---\n";
    std::cout << "1. Gano " << robot1.nombre << "\n";
    std::cout << "2. Gano " << robot2.nombre << "\n";
    std::cout << "3. Empate\n";
    std::cout << "Seleccione el resultado: ";
    std::cin >> resultado;

    switch (resultado) {
        case 1:
            robot1.victorias++;
            robot1.puntos += 3;
            robot2.derrotas++;
            std::cout << "\nVictoria registrada para " << robot1.nombre << " (+3 pts).\n";
            break;
        case 2:
            robot2.victorias++;
            robot2.puntos += 3;
            robot1.derrotas++;
            std::cout << "\nVictoria registrada para " << robot2.nombre << " (+3 pts).\n";
            break;
        case 3:
            robot1.empates++;
            robot1.puntos += 1;
            robot2.empates++;
            robot2.puntos += 1;
            std::cout << "\nEmpate registrado (+1 pt para cada uno).\n";
            break;
        default:
            std::cout << "ERROR: Opcion invalida.\n";
    }
}

// 3. Ordenamiento por Burbuja manual y reporte final
void MostrarReporteFinal(std::vector<Robot> torneo) {
    if (torneo.empty()) {
        std::cout << "\nNo hay robots en el torneo.\n";
        return;
    }

    int n = static_cast<int>(torneo.size());

    // --- ORDENAMIENTO POR BURBUJA (SIN USAR STD::SORT) ---
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // Criterio 1: Ordenar de mayor a menor por PUNTOS
            // Criterio 2 (Desempate): Si tienen los mismos puntos, ordenar por VICTORIAS
            if (torneo[j].puntos < torneo[j + 1].puntos || 
            (torneo[j].puntos == torneo[j + 1].puntos && torneo[j].victorias < torneo[j + 1].victorias)) {
                
                // Intercambio de estructuras (Swap manual)
                Robot aux = torneo[j];
                torneo[j] = torneo[j + 1];
                torneo[j + 1] = aux;
            }
        }
    }

    // Búsqueda del robot con mayor número de victorias
    int max_victorias = -1;
    int idx_max_victorias = 0;

    for (int i = 0; i < n; ++i) {
        if (torneo[i].victorias > max_victorias) {
            max_victorias = torneo[i].victorias;
            idx_max_victorias = i;
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "       CLASIFICACION FINAL DEL TORNEO    \n";
    std::cout << "=========================================\n";
    
    for (int i = 0; i < n; ++i) {
        std::cout << (i + 1) << " Posicion: " << torneo[i].nombre 
                << " | Puntos: " << torneo[i].puntos 
                << " | (V: " << torneo[i].victorias 
                << ", E: " << torneo[i].empates 
                << ", D: " << torneo[i].derrotas << ")\n";
    }

    std::cout << "\n-----------------------------------------\n";
    std::cout << "GANADOR DEL TORNEO (Mas puntos): " << torneo[0].nombre 
            << " con " << torneo[0].puntos << " puntos.\n";
    
    std::cout << "ROBOT CON MAS VICTORIAS:        " << torneo[idx_max_victorias].nombre 
            << " con " << torneo[idx_max_victorias].victorias << " victorias.\n";
    std::cout << "=========================================\n";
}

/*6. Torneo de robots
En un torneo participan varios robots que se enfrentan entre sí. De cada robot se
registra su nombre, cantidad de victorias, derrotas, empates y puntuación acumulada.
Cada victoria otorga 3 puntos, cada empate 1 punto y una derrota no otorga puntos.
El programa debe permitir registrar los resultados de los enfrentamientos y actualizar
automáticamente las estadísticas de los robots involucrados.
Al finalizar el torneo, deberá mostrarse una clasificación de los participantes ordenada
según su puntuación. También deberá identificarse al robot con mayor número de
victorias y al que haya obtenido la mayor cantidad de puntos.*/