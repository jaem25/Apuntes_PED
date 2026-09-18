#include <iostream>
#include <string>
#include <vector>

struct Dron {
    int id;
    std::string modelo;
    double bateria;             // Porcentaje de 0.0 a 100.0
    double distancia_total;     // Distancia acumulada en km
    bool disponible;            // true = Disponible, false = Ocupado
};

// Consumo estimado: 2% de batería por cada kilómetro recorrido
const double CONSUMO_POR_KM = 2.0;

// Declaración de funciones
void ConsultarFlota(const std::vector<Dron>& flota);
void AsignarMision(std::vector<Dron>& flota);
void ConsultarMayorDistancia(const std::vector<Dron>& flota);

int main() {
    // Inicialización de la flota con datos base
    std::vector<Dron> flota = {
        {1, "DJI Mavic 3", 100.0, 12.5, true},
        {2, "Phantom 4", 45.0, 48.0, true},
        {3, "Matrice 300", 15.0, 80.2, true},    // Batería baja
        {4, "Air 2S", 80.0, 5.0, false},        // Ocupado / En mantenimiento
        {5, "Inspire 2", 90.0, 30.0, true}
    };

    int opcion = 0;

    do {
        std::cout << "\n=========================================\n";
        std::cout << "      SISTEMA DE CONTROL DE DRONES       \n";
        std::cout << "=========================================\n";
        std::cout << "1. Consultar estado de la flota\n";
        std::cout << "2. Asignar mision a un dron\n";
        std::cout << "3. Consultar dron con mayor distancia\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ConsultarFlota(flota);
                break;
            case 2:
                AsignarMision(flota);
                break;
            case 3:
                ConsultarMayorDistancia(flota);
                break;
            case 4:
                std::cout << "\nCerrando sistema de control de drones...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}

// 1. Mostrar el listado completo de la flota
void ConsultarFlota(const std::vector<Dron>& flota) {
    std::cout << "\n--- ESTADO DE LA FLOTA ---\n";
    for (const auto& d : flota) {
        std::cout << "ID: " << d.id 
                << " | Modelo: " << d.modelo 
                << " | Bateria: " << d.bateria << "%"
                << " | Dist. Total: " << d.distancia_total << " km"
                << " | Estado: " << (d.disponible ? "DISPONIBLE" : "OCUPADO / NO DISPONIBLE") 
                << "\n";
    }
}

// 2. Procesar la asignación de una misión aplicando las 3 validaciones
void AsignarMision(std::vector<Dron>& flota) {
    ConsultarFlota(flota);

    int id_buscar = 0;
    std::cout << "\nIngrese el ID del dron para la mision: ";
    std::cin >> id_buscar;

    int indice = -1;
    for (size_t i = 0; i < flota.size(); ++i) {
        if (flota[i].id == id_buscar) {
            indice = static_cast<int>(i);
            break;
        }
    }

    // VALIDACIÓN 1: Verificar existencia
    if (indice == -1) {
        std::cout << "ERROR: El dron con ID " << id_buscar << " no existe.\n";
        return;
    }

    Dron& d = flota[indice];

    // VALIDACIÓN 2: Verificar disponibilidad
    if (!d.disponible) {
        std::cout << "ERROR: El dron " << d.id << " (" << d.modelo << ") esta OCUPADO o fuera de servicio.\n";
        return;
    }

    double distancia = 0.0;
    std::cout << "Ingrese la distancia de la mision (km): ";
    std::cin >> distancia;

    if (distancia <= 0) {
        std::cout << "ERROR: La distancia debe ser mayor a cero.\n";
        return;
    }

    double bateria_requerida = distancia * CONSUMO_POR_KM;

    // VALIDACIÓN 3: Verificar suficiencia de batería
    if (d.bateria < bateria_requerida) {
        std::cout << "ERROR: Bateria insuficiente. Se requiere " << bateria_requerida 
                << "% pero el dron solo tiene " << d.bateria << "%.\n";
        return;
    }

    // Inicio de la misión
    std::cout << "\n[MISION INICIADA] Despegando dron " << d.id << "...\n";
    d.disponible = false; // Se marca como ocupado

    // Finalización de la misión (actualización de métricas)
    d.bateria -= bateria_requerida;
    d.distancia_total += distancia;
    d.disponible = true; // Vuelve a estar disponible

    std::cout << "[MISION COMPLETADA] El dron ha regresado exitosamente.\n";
    std::cout << "Nueva bateria restante: " << d.bateria << "%\n";
    std::cout << "Nueva distancia total acumulada: " << d.distancia_total << " km\n";
}

// 3. Buscar e identificar el dron con más kilómetros recorridos
void ConsultarMayorDistancia(const std::vector<Dron>& flota) {
    if (flota.empty()) {
        std::cout << "\nNo hay drones registrados en la flota.\n";
        return;
    }

    double max_distancia = -1.0;
    int idx_max = 0;

    for (size_t i = 0; i < flota.size(); ++i) {
        if (flota[i].distancia_total > max_distancia) {
            max_distancia = flota[i].distancia_total;
            idx_max = static_cast<int>(i);
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "    DRON CON MAYOR DISTANCIA ACUMULADA   \n";
    std::cout << "=========================================\n";
    std::cout << "ID:               " << flota[idx_max].id << "\n";
    std::cout << "Modelo:           " << flota[idx_max].modelo << "\n";
    std::cout << "Bateria actual:   " << flota[idx_max].bateria << "%\n";
    std::cout << "Distancia Total:  " << flota[idx_max].distancia_total << " km\n";
    std::cout << "=========================================\n";
}

/*5. Control de drones
Una empresa utiliza una flota de drones para realizar diferentes misiones. Cada dron
posee un identificador, modelo, porcentaje de batería, distancia total recorrida y un
estado que indica si se encuentra disponible.
Para realizar una misión se debe especificar una distancia determinada. El dron
seleccionado deberá disponer de suficiente batería para completar dicha misión.
Al iniciar una misión, el dron deja de estar disponible y su batería disminuye según la
distancia que debe recorrer. Al finalizar, vuelve a estar disponible y la distancia
recorrida se acumula en su historial.
El sistema deberá impedir que un dron ocupado o con batería insuficiente sea
seleccionado. También deberá permitir consultar cuál ha sido el dron con mayor
distancia acumulada.
*/