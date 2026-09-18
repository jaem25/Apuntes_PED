#include <iostream>
#include <string>

struct Piloto {
    std::string nombre;
    int vueltas;
    float mejor_tiempo_vuelta;
    float tiempo_total;
    bool abandono;
};

int main() {
    int n = 0;
    std::cout << "Cantidad de pilotos participantes: ";
    std::cin >> n;

    Piloto* parrilla = new Piloto[n];

    for (int i = 0; i < n; i++) {
        std::cout << "Nombre del Piloto #" << (i + 1) << ": ";
        std::cin.ignore();
        std::getline(std::cin, parrilla[i].nombre);
        parrilla[i].vueltas = 0;
        parrilla[i].mejor_tiempo_vuelta = 99999.0;
        parrilla[i].tiempo_total = 0.0;
        parrilla[i].abandono = false;
    }

    int opcion = 0;
    do {
        std::cout << "\n--- CONTROL DE CARRERA ---\n";
        std::cout << "1. Registrar vuelta general\n";
        std::cout << "2. Ver clasificacion final y salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            for (int i = 0; i < n; i++) {
                if (!parrilla[i].abandono) {
                    std::cout << "\nPiloto: " << parrilla[i].nombre << "\n";
                    int estado = 0;
                    std::cout << "1: Completo vuelta | 2: Abandono carrera: ";
                    std::cin >> estado;

                    if (estado == 2) {
                        parrilla[i].abandono = true;
                        std::cout << parrilla[i].nombre << " ha abandonado la carrera.\n";
                    } else {
                        float t = 0.0;
                        std::cout << "Tiempo de la vuelta (segundos): ";
                        std::cin >> t;

                        parrilla[i].vueltas++;
                        parrilla[i].tiempo_total += t;
                        if (t < parrilla[i].mejor_tiempo_vuelta) {
                            parrilla[i].mejor_tiempo_vuelta = t;
                        }
                    }
                }
            }
        }
    } while (opcion != 2);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (parrilla[j].abandono && !parrilla[j + 1].abandono) {
                Piloto temp = parrilla[j];
                parrilla[j] = parrilla[j + 1];
                parrilla[j + 1] = temp;
            } else if (!parrilla[j].abandono && !parrilla[j + 1].abandono) {
                if (parrilla[j].tiempo_total > parrilla[j + 1].tiempo_total) {
                    Piloto temp = parrilla[j];
                    parrilla[j] = parrilla[j + 1];
                    parrilla[j + 1] = temp;
                }
            }
        }
    }

    int idx_vuelta_rapida = 0, idx_mas_vueltas = 0;
    for (int i = 1; i < n; i++) {
        if (parrilla[i].mejor_tiempo_vuelta < parrilla[idx_vuelta_rapida].mejor_tiempo_vuelta) {
            idx_vuelta_rapida = i;
        }
        if (parrilla[i].vueltas > parrilla[idx_mas_vueltas].vueltas) {
            idx_mas_vueltas = i;
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "          CLASIFICACION FINAL            \n";
    std::cout << "=========================================\n";
    for (int i = 0; i < n; i++) {
        std::cout << (i + 1) << ". " << parrilla[i].nombre;
        if (parrilla[i].abandono) {
            std::cout << " (ABANDONO - Vueltas: " << parrilla[i].vueltas << ")\n";
        } else {
            std::cout << " - Tiempo Total: " << parrilla[i].tiempo_total << "s (Vueltas: " << parrilla[i].vueltas << ")\n";
        }
    }

    std::cout << "\nVUELTA MAS RAPIDA: " << parrilla[idx_vuelta_rapida].nombre 
            << " (" << parrilla[idx_vuelta_rapida].mejor_tiempo_vuelta << "s)\n";
    std::cout << "PILOTO CON MAS VUELTAS: " << parrilla[idx_mas_vueltas].nombre 
            << " (" << parrilla[idx_mas_vueltas].vueltas << " vueltas)\n";

    delete[] parrilla;
    return 0;
}

/*9. Clasificación de una carrera
Se desea desarrollar un pequeño sistema para administrar los resultados de una
carrera automovilística. De cada piloto se registra su nombre, número de vueltas
completadas, mejor tiempo de vuelta, tiempo total de carrera y si abandonó o no.
Durante la carrera pueden registrarse nuevas vueltas para los pilotos.
Al finalizar, el programa deberá generar una clasificación. Los pilotos que hayan
completado la carrera deberán aparecer antes que aquellos que abandonaron. Entre
los pilotos que terminaron, deberá determinarse la posición utilizando su tiempo total.
También deberá mostrarse quién consiguió la vuelta más rápida y quién completó la
mayor cantidad de vueltas.*/