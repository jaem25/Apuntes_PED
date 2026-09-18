#include <iostream>
#include <string>
#include <cstdlib> // Necesario para std::rand y std::srand
#include <ctime>   // Necesario para std::time

struct Bicicleta {
    int id;
    std::string tipo;
    float kilometraje;
    int alquileres;
    bool disponible;
};

int main() {
    // Inicializar la semilla para generar numeros aleatorios
    std::srand(std::time(0));

    int n = 0;
    std::cout << "Cantidad de bicicletas en la flota: ";
    std::cin >> n;

    Bicicleta* flota = new Bicicleta[n];

    for (int i = 0; i < n; i++) {
        std::cout << "\n--- Registrando Bicicleta #" << (i + 1) << " ---\n";
        
        // Genera un ID aleatorio entre 1000 y 9999
        flota[i].id = 1000 + std::rand() % 9000; 
        std::cout << "ID (generado automaticamente): " << flota[i].id << "\n";

        std::cout << "Tipo: "; 
        std::cin.ignore(); 
        std::getline(std::cin, flota[i].tipo);
        
        flota[i].kilometraje = 0.0f;
        flota[i].alquileres = 0;
        flota[i].disponible = true;
    }

    int opcion = 0;
    do {
        std::cout << "\n--- ALQUILER DE BICICLETAS ---\n";
        std::cout << "1. Alquilar bicicleta\n";
        std::cout << "2. Devolver bicicleta\n";
        std::cout << "3. Ver reporte y salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            int id_b = 0;
            std::cout << "Ingrese ID de la bicicleta a alquilar: ";
            std::cin >> id_b;

            bool existe = false;
            for (int i = 0; i < n; i++) {
                if (flota[i].id == id_b) {
                    existe = true;
                    if (!flota[i].disponible) {
                        std::cout << "ERROR: La bicicleta ya esta alquilada.\n";
                    } else {
                        flota[i].disponible = false;
                        std::cout << "[OK] Bicicleta alquilada exitosamente.\n";
                    }
                    break;
                }
            }
            if (!existe) std::cout << "ERROR: ID no encontrado.\n";

        } else if (opcion == 2) {
            int id_b = 0;
            std::cout << "Ingrese ID de la bicicleta a devolver: ";
            std::cin >> id_b;

            bool existe = false;
            for (int i = 0; i < n; i++) {
                if (flota[i].id == id_b) {
                    existe = true;
                    if (flota[i].disponible) {
                        std::cout << "ERROR: La bicicleta ya figura como disponible.\n";
                    } else {
                        float km = 0.0f;
                        std::cout << "Ingrese kilometros recorridos: ";
                        std::cin >> km;

                        flota[i].kilometraje += km;
                        flota[i].alquileres++;
                        flota[i].disponible = true;
                        std::cout << "[OK] Devolucion procesada correctamente.\n";
                    }
                    break;
                }
            }
            if (!existe) std::cout << "ERROR: ID no encontrado.\n";
        }
    } while (opcion != 3);

    int idx_mas_alquilada = 0, idx_mas_km = 0;
    for (int i = 1; i < n; i++) {
        if (flota[i].alquileres > flota[idx_mas_alquilada].alquileres) idx_mas_alquilada = i;
        if (flota[i].kilometraje > flota[idx_mas_km].kilometraje) idx_mas_km = i;
    }

    std::cout << "\n=========================================\n";
    std::cout << "          REPORTE DE ALQUILERES          \n";
    std::cout << "=========================================\n";
    std::cout << "Bicicleta mas alquilada: ID " << flota[idx_mas_alquilada].id 
            << " (" << flota[idx_mas_alquilada].alquileres << " alquileres)\n";
    std::cout << "Bicicleta con mayor kilometraje: ID " << flota[idx_mas_km].id 
            << " (" << flota[idx_mas_km].kilometraje << " km)\n";

    delete[] flota;
    return 0;
}

/*8. Sistema de alquiler de bicicletas
Una empresa de alquiler dispone de una flota de bicicletas. Cada bicicleta posee un
identificador, tipo, kilometraje acumulado, cantidad de alquileres realizados y un
estado que indica si está disponible.
El programa debe permitir que un cliente alquile una bicicleta disponible y
posteriormente registre su devolución indicando los kilómetros recorridos durante el
alquiler.
Una bicicleta que se encuentre alquilada no puede volver a ser alquilada hasta que sea
devuelta.
El sistema deberá mantener actualizado el kilometraje y el número de alquileres de
cada bicicleta. Al finalizar, deberá mostrar cuál ha sido la bicicleta más utilizada y cuál
acumula el mayor kilometraje.*/