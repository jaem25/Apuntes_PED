#include <iostream>
#include <string>

struct Sensor {
    int id;
    std::string ubicacion;
    double temperatura;
    double humedad;
    bool funcionando;
};

const int CANTIDAD_SENSORES = 5;

// Declaración de funciones
void MostrarSensores(const Sensor sensores[], int tamano);
void ActualizarMediciones(Sensor sensores[], int tamano);
void ConsultarEstadoGeneral(const Sensor sensores[], int tamano);

int main() {
    // Inicialización del arreglo de sensores con datos base
    Sensor sensores[CANTIDAD_SENSORES] = {
        {101, "Servidores", 24.5, 45.0, true},
        {102, "Oficinas", 22.0, 35.0, true},
        {103, "Almacen", 36.5, 25.0, true},    // Alerta por Temp > 35 y Humedad < 30
        {104, "Laboratorio", 19.0, 50.0, false}, // Fuera de servicio
        {105, "Calderas", 38.0, 40.0, true}     // Alerta por Temp > 35
    };

    int opcion = 0;

    do {
        std::cout << "\n=========================================\n";
        std::cout << "      SISTEMA DE MONITOREO AMBIENTAL     \n";
        std::cout << "=========================================\n";
        std::cout << "1. Consultar estado general de la instalacion\n";
        std::cout << "2. Actualizar mediciones de sensores\n";
        std::cout << "3. Ver lista completa de sensores\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ConsultarEstadoGeneral(sensores, CANTIDAD_SENSORES);
                break;
            case 2:
                ActualizarMediciones(sensores, CANTIDAD_SENSORES);
                break;
            case 3:
                MostrarSensores(sensores, CANTIDAD_SENSORES);
                break;
            case 4:
                std::cout << "\nCerrando sistema de monitoreo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}

// Muestra el listado de todos los sensores registrados
void MostrarSensores(const Sensor sensores[], int tamano) {
    std::cout << "\n--- LISTADO DE SENSORES ---\n";
    for (int i = 0; i < tamano; ++i) {
        std::cout << "ID: " << sensores[i].id 
                << " | Ubicacion: " << sensores[i].ubicacion 
                << " | Estado: " << (sensores[i].funcionando ? "ACTIVO" : "FUERA DE SERVICIO") 
                << " | Temp: " << sensores[i].temperatura << " C"
                << " | Humedad: " << sensores[i].humedad << "%\n";
    }
}

// Permite seleccionar un sensor por su ID y actualizar sus lecturas
void ActualizarMediciones(Sensor sensores[], int tamano) {
    MostrarSensores(sensores, tamano);

    int id_buscar = 0;
    std::cout << "\nIngrese el ID del sensor a actualizar: ";
    std::cin >> id_buscar;

    int indice = -1;
    for (int i = 0; i < tamano; ++i) {
        if (sensores[i].id == id_buscar) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        std::cout << "ERROR: El sensor con ID " << id_buscar << " no existe.\n";
        return;
    }

    std::cout << "Ingrese la nueva temperatura (C): ";
    std::cin >> sensores[indice].temperatura;

    std::cout << "Ingrese la nueva humedad (%): ";
    std::cin >> sensores[indice].humedad;

    char resp;
    std::cout << "El sensor esta funcionando? (s/n): ";
    std::cin >> resp;
    sensores[indice].funcionando = (resp == 's' || resp == 'S');

    std::cout << "Mediciones actualizadas con exito para el sensor " << id_buscar << ".\n";
}

// Genera el reporte completo procesando las alertas y métricas
void ConsultarEstadoGeneral(const Sensor sensores[], int tamano) {
    double suma_temperatura = 0.0;
    int activos = 0;
    int fuera_servicio = 0;

    int idx_max_temp = -1;
    double max_temp = -999.0;

    std::cout << "\n=========================================\n";
    std::cout << "       REPORTE DEL ESTADO GENERAL        \n";
    std::cout << "=========================================\n";

    // Subsección: Alertas de parámetros desbordados (Temp > 35°C o Humedad < 30%)
    std::cout << "\n--- ALERTAS DETECTADAS ---\n";
    bool hay_alertas = false;

    for (int i = 0; i < tamano; ++i) {
        if (!sensores[i].funcionando) {
            fuera_servicio++;
            continue; // Los sensores fuera de servicio no cuentan para promedios ni max
        }

        activos++;
        suma_temperatura += sensores[i].temperatura;

        // Búsqueda del sensor activo con temperatura más alta
        if (sensores[i].temperatura > max_temp) {
            max_temp = sensores[i].temperatura;
            idx_max_temp = i;
        }

        // Verificación de condiciones de alerta
        bool alerta_temp = sensores[i].temperatura > 35.0;
        bool alerta_humedad = sensores[i].humedad < 30.0;

        if (alerta_temp || alerta_humedad) {
            hay_alertas = true;
            std::cout << "[ALERTA] Sensor " << sensores[i].id 
                    << " (" << sensores[i].ubicacion << "): ";
            
            if (alerta_temp && alerta_humedad) {
                std::cout << "Temperatura critica (" << sensores[i].temperatura << " C) Y Humedad baja (" << sensores[i].humedad << "%)\n";
            } else if (alerta_temp) {
                std::cout << "Temperatura critica (" << sensores[i].temperatura << " C)\n";
            } else {
                std::cout << "Humedad baja (" << sensores[i].humedad << "%)\n";
            }
        }
    }

    if (!hay_alertas) {
        std::cout << "No se presentan situaciones de alerta en los sensores activos.\n";
    }

    // Resumen estadístico
    std::cout << "\n--- METRICAS GENERALES ---\n";
    std::cout << "Sensores fuera de servicio: " << fuera_servicio << "\n";

    if (activos > 0) {
        double promedio_temp = suma_temperatura / activos;
        std::cout << "Temperatura promedio (sensores activos): " << promedio_temp << " C\n";
        std::cout << "Sensor con temperatura mas alta: ID " << sensores[idx_max_temp].id 
                << " en '" << sensores[idx_max_temp].ubicacion 
                << "' con " << sensores[idx_max_temp].temperatura << " C\n";
    } else {
        std::cout << "No hay sensores activos para calcular la temperatura promedio o maxima.\n";
    }
    std::cout << "=========================================\n";
}

/*3. Sistema de monitoreo ambiental
Una empresa ha instalado varios sensores en diferentes zonas de un edificio. Cada
sensor registra temperatura y humedad, además de contar con un identificador, una
ubicación y un estado que indica si se encuentra funcionando.
El programa debe permitir actualizar las mediciones de los sensores y consultar el
estado general de la instalación.
Se considera que existe una situación de alerta cuando la temperatura supera los 35 °C
o la humedad desciende por debajo del 30 %.
El sistema deberá determinar la temperatura promedio de los sensores activos,
identificar el sensor que registra la temperatura más alta, contar los sensores fuera de
servicio y mostrar cuáles presentan condiciones de alerta.*/