#include <iostream>
#include <string>
#include <vector>

struct Vehiculo {
    std::string placa;
    std::string tipo;
    std::string hora_entrada;
    bool dentro = false;
};

// Declaración de funciones
bool SolicitarDatosVehiculo(std::vector<Vehiculo>& flota);
void RegistrarSalidaVehiculo(std::vector<Vehiculo>& flota);
void MostrarEstadisticas(const std::vector<Vehiculo>& flota, int capacidad);

int main() {
    const int capacidad = 5;
    std::vector<Vehiculo> flota; // C++ gestiona la memoria automáticamente

    int opcion = 0;
    do {
        std::cout << "\n--- MENU ESTACIONAMIENTO ---\n";
        std::cout << "1. Registrar entrada de vehiculo\n";
        std::cout << "2. Registrar salida de vehiculo\n";
        std::cout << "3. Mostrar estadisticas\n";
        std::cout << "4. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                if (SolicitarDatosVehiculo(flota)) {
                    // Vehículo registrado con éxito
                }
                break;

            case 2:
                RegistrarSalidaVehiculo(flota);
                break;

            case 3:
                MostrarEstadisticas(flota, capacidad);
                break;

            case 4:
                std::cout << "Saliendo del sistema...\n";
                break;

            default:
                std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    return 0; // Sin necesidad de delete[]
}

bool SolicitarDatosVehiculo(std::vector<Vehiculo>& flota) {
    std::string placa_ingresada;
    std::cout << "\nIngresar placa: ";
    std::cin >> placa_ingresada;

    // Validación de placa duplicada activa
    for (const auto& v : flota) {
        if (v.placa == placa_ingresada && v.dentro) {
            std::cout << "ERROR: La placa '" << placa_ingresada << "' ya esta registrada adentro.\n";
            return false;
        }
    }

    Vehiculo nuevo;
    nuevo.placa = placa_ingresada;
    std::cout << "Ingresar tipo: ";
    std::cin >> nuevo.tipo;
    std::cout << "Ingresar hora de entrada: ";
    std::cin >> nuevo.hora_entrada;
    nuevo.dentro = true;

    flota.push_back(nuevo);
    std::cout << "Vehiculo registrado con exito.\n";

    return true;
}

void RegistrarSalidaVehiculo(std::vector<Vehiculo>& flota) {
    if (flota.empty()) {
        std::cout << "No hay vehiculos registrados.\n";
        return;
    }

    std::string placa_retirar;
    std::cout << "\nIngresar placa a retirar: ";
    std::cin >> placa_retirar;

    for (auto& v : flota) {
        if (v.placa == placa_retirar && v.dentro) {
            v.dentro = false;
            std::cout << "Salida registrada con exito para la placa: " << placa_retirar << "\n";
            return;
        }
    }

    std::cout << "ERROR: No se encontro un vehiculo dentro con esa placa.\n";
}

void MostrarEstadisticas(const std::vector<Vehiculo>& flota, int capacidad) {
    int ocupados = 0;
    for (const auto& v : flota) {
        if (v.dentro) ocupados++;
    }
    int libres = capacidad - ocupados;
    float porcentaje = (static_cast<float>(ocupados) / capacidad) * 100.0f;

    std::cout << "\n--- ESTADISTICAS ---\n";
    std::cout << "Espacios ocupados: " << ocupados << "\n";
    std::cout << "Espacios libres: " << libres << "\n";
    std::cout << "Porcentaje de ocupacion: " << porcentaje << "%\n";
}

/*Sistema de estacionamiento
Una empresa administra un estacionamiento con capacidad limitada para vehículos.
De cada vehículo se necesita registrar información como su placa, tipo de vehículo,
hora de entrada y estado actual dentro del estacionamiento.
El programa debe permitir registrar nuevos vehículos siempre que existan espacios
disponibles. También debe permitir registrar la salida de un vehículo, localizar un
vehículo mediante su placa y consultar el estado actual del estacionamiento.
Al finalizar, el sistema deberá mostrar cuántos espacios están ocupados, cuántos
están libres y cuál es el porcentaje de ocupación. No debe ser posible registrar dos
vehículos con la misma placa simultáneamente.*/