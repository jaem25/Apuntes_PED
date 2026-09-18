#include <iostream>
#include <string>

struct Mision {
    std::string nombre;
    int dificultad;
    float recompensa;
    bool completada;
};

int main() {
    int n = 0;
    std::cout << "Cantidad de misiones a registrar: ";
    std::cin >> n;

    Mision* misiones = new Mision[n];

    for (int i = 0; i < n; i++) {
        std::cout << "\n--- Registrando Mision #" << (i + 1) << " ---\n";
        std::cout << "Nombre: "; std::cin.ignore(); std::getline(std::cin, misiones[i].nombre);
        std::cout << "Dificultad (1 a 10): "; std::cin >> misiones[i].dificultad;
        std::cout << "Recompensa ($): "; std::cin >> misiones[i].recompensa;
        misiones[i].completada = false;
    }

    int opcion = 0;
    do {
        std::cout << "\n--- GESTION DE MISIONES ---\n";
        std::cout << "1. Marcar mision como completada\n";
        std::cout << "2. Ver reporte y salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << "\n--- LISTA DE MISIONES ---\n";
            for (int i = 0; i < n; i++) {
                std::cout << (i + 1) << ". " << misiones[i].nombre 
                << " [" << (misiones[i].completada ? "COMPLETADA" : "PENDIENTE") << "]\n";
            }

            int sel = 0;
            std::cout << "Seleccione la mision a marcar: ";
            std::cin >> sel;

            if (sel >= 1 && sel <= n) {
                int idx = sel - 1;
                if (misiones[idx].completada) {
                    std::cout << "ERROR: Esta mision ya estaba completada.\n";
                } else {
                    misiones[idx].completada = true;
                    std::cout << "[EXITO] Mision completada! Recompensa agregada.\n";
                }
            } else {
                std::cout << "ERROR: Opcion invalida.\n";
            }
        }
    } while (opcion != 2);

    float total_recompensas = 0.0f;
    int completadas = 0, idx_mas_dificil = 0, idx_mas_recompensa = 0;

    std::cout << "\n--- MISIONES PENDIENTES ---\n";
    bool hay_pendientes = false;

    for (int i = 0; i < n; i++) {
        if (misiones[i].completada) {
            completadas++;
            total_recompensas += misiones[i].recompensa;
        } else {
            std::cout << "- " << misiones[i].nombre << " (Dificultad: " << misiones[i].dificultad << ")\n";
            hay_pendientes = true;
        }

        if (misiones[i].dificultad > misiones[idx_mas_dificil].dificultad) idx_mas_dificil = i;
        if (misiones[i].recompensa > misiones[idx_mas_recompensa].recompensa) idx_mas_recompensa = i;
    }

    if (!hay_pendientes) std::cout << "Felicidades! No quedan misiones pendientes.\n";

    std::cout << "\n=========================================\n";
    std::cout << "          ESTADISTICAS GENERALES         \n";
    std::cout << "=========================================\n";
    std::cout << "Total de recompensas obtenidas: $" << total_recompensas << "\n";
    std::cout << "Porcentaje de completitud: " << ((float)completadas / n) * 100.0f << "%\n";
    std::cout << "Mision con mayor dificultad: " << misiones[idx_mas_dificil].nombre 
            << " (Nivel " << misiones[idx_mas_dificil].dificultad << ")\n";
    std::cout << "Mision con mayor recompensa: " << misiones[idx_mas_recompensa].nombre 
            << " ($" << misiones[idx_mas_recompensa].recompensa << ")\n";

    delete[] misiones;
    return 0;
}

/*10. Administrador de misiones
Un videojuego contiene una serie de misiones que el jugador puede completar. Cada
misión tiene un nombre, nivel de dificultad, recompensa y estado de completada o
pendiente.
El programa debe permitir seleccionar misiones y marcarlas como completadas. Una
misión que ya fue completada no debe volver a otorgar su recompensa.
El sistema deberá calcular la cantidad total de recompensas obtenidas, determinar
qué porcentaje de las misiones ha completado el jugador y mostrar las misiones que
todavía están pendientes.
Finalmente, deberá identificar cuál es la misión de mayor dificultad y cuál proporciona
la mayor recompensa.*/