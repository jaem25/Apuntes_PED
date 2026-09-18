#include <iostream>
#include <string>

// Estructura que define un Dispositivo Electrónico
struct Dispositivo {
    std::string nombre;
    std::string tipo;       // Ej. Smartphone, Laptop, Tablet, Smartwatch
    float nivel_bateria;    // Porcentaje actual (0.0% - 100.0%)
    float consumo_por_hora; // Porcentaje de batería consumido por hora (%)
    bool esta_encendido;    // true = Encendido / Activo, false = Apagado / Inactivo
};

// Constante global para definir la cantidad fija de dispositivos
const int MAX_DISPOSITIVOS = 5;

// Declaración de funciones del sistema
void MostrarDispositivos(const Dispositivo lista[], int tamano);
void SimularPasoHoras(Dispositivo lista[], int tamano);
void ConsultarBateriaBaja(const Dispositivo lista[], int tamano);
void DeterminarMayorConsumo(const Dispositivo lista[], int tamano);
void ProyectarBateriaFutura(const Dispositivo lista[], int tamano);
void AlternarEstadoDispositivo(Dispositivo lista[], int tamano);

int main() {
    // Arreglo estático inicializado con datos base
    Dispositivo inventario[MAX_DISPOSITIVOS] = {
        {"Laptop Pro", "Portatil", 85.0f, 12.5f, true},
        {"Galaxy S24", "Smartphone", 18.0f, 8.0f, true},
        {"iPad Air", "Tablet", 50.0f, 6.0f, false},
        {"Watch GT", "Smartwatch", 15.0f, 2.5f, true},
        {"Drone X", "Dron", 100.0f, 40.0f, true}
    };

    int opcion = 0;

    do {
        std::cout << "\n=================================================\n";
        std::cout << "      SIMULADOR DE BATERIA Y CONSUMO DE ENERGIA   \n";
        std::cout << "=================================================\n";
        std::cout << "1. Consultar estado de todos los dispositivos\n";
        std::cout << "2. Simular paso del tiempo (Horas)\n";
        std::cout << "3. Consultar dispositivos con bateria critica (< 20%)\n";
        std::cout << "4. Determinar dispositivo con mayor consumo por hora\n";
        std::cout << "5. Proyectar bateria restante tras X horas\n";
        std::cout << "6. Encender / Apagar un dispositivo\n";
        std::cout << "7. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                MostrarDispositivos(inventario, MAX_DISPOSITIVOS);
                break;
            case 2:
                SimularPasoHoras(inventario, MAX_DISPOSITIVOS);
                break;
            case 3:
                ConsultarBateriaBaja(inventario, MAX_DISPOSITIVOS);
                break;
            case 4:
                DeterminarMayorConsumo(inventario, MAX_DISPOSITIVOS);
                break;
            case 5:
                ProyectarBateriaFutura(inventario, MAX_DISPOSITIVOS);
                break;
            case 6:
                AlternarEstadoDispositivo(inventario, MAX_DISPOSITIVOS);
                break;
            case 7:
                std::cout << "\nSaliendo del simulador energetico...\n";
                break;
            default:
                std::cout << "\nOpcion invalida. Por favor, intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}

// 1. Muestra el informe detallado de todos los dispositivos
void MostrarDispositivos(const Dispositivo lista[], int tamano) {
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "                       ESTADO DE DISPOSITIVOS                         \n";
    std::cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < tamano; ++i) {
        std::cout << (i + 1) << ". [" << lista[i].tipo << "] " << lista[i].nombre << "\n"
                << "   - Bateria: " << lista[i].nivel_bateria << "%\n"
                << "   - Consumo: " << lista[i].consumo_por_hora << "%/h\n"
                << "   - Estado:  " << (lista[i].esta_encendido ? "Encendido (Activo)" : "Apagado (Inactivo)") << "\n"
                << "----------------------------------------------------------------------\n";
    }
}

// 2. Simula el consumo de energía en horas para dispositivos activos
void SimularPasoHoras(Dispositivo lista[], int tamano) {
    int horas = 0;
    std::cout << "\nIngrese la cantidad de horas a simular: ";
    std::cin >> horas;

    if (horas <= 0) {
        std::cout << "La cantidad de horas debe ser mayor a 0.\n";
        return;
    }

    std::cout << "\nSimulando " << horas << " hora(s) de uso...\n";
    for (int i = 0; i < tamano; ++i) {
        if (lista[i].esta_encendido) {
            float consumo_total = lista[i].consumo_por_hora * horas;
            lista[i].nivel_bateria -= consumo_total;

            // Si la batería llega a 0% o menos, se apaga automáticamente
            if (lista[i].nivel_bateria <= 0.0f) {
                lista[i].nivel_bateria = 0.0f;
                lista[i].esta_encendido = false; // Deja de considerarse activo
                std::cout << "-> [ALERTA] " << lista[i].nombre << " agoto su bateria y se ha apagado.\n";
            }
        }
    }
    std::cout << "[OK] Simulacion completada con exito.\n";
}

// 3. Identifica dispositivos con batería inferior al 20%
void ConsultarBateriaBaja(const Dispositivo lista[], int tamano) {
    std::cout << "\n--- DISPOSITIVOS CON BATERIA CRITICA (< 20%) ---\n";
    bool hay_criticos = false;

    for (int i = 0; i < tamano; ++i) {
        if (lista[i].nivel_bateria < 20.0f) {
            std::cout << "- " << lista[i].nombre << " (" << lista[i].tipo << "): " 
                    << lista[i].nivel_bateria << "% de bateria restante ["
                    << (lista[i].esta_encendido ? "Encendido" : "Apagado") << "]\n";
            hay_criticos = true;
        }
    }

    if (!hay_criticos) {
        std::cout << "Todos los dispositivos tienen niveles de bateria superiores al 20%.\n";
    }
}

// 4. Determina qué dispositivo consume más energía por hora
void DeterminarMayorConsumo(const Dispositivo lista[], int tamano) {
    if (tamano <= 0) {
        std::cout << "No hay dispositivos registrados en el sistema.\n";
        return;
    }

    int idx_mayor = 0;
    for (int i = 1; i < tamano; ++i) {
        if (lista[i].consumo_por_hora > lista[idx_mayor].consumo_por_hora) {
            idx_mayor = i;
        }
    }

    std::cout << "\n--- DISPOSITIVO CON MAYOR CONSUMO ENERGETICO ---\n";
    std::cout << "Nombre:   " << lista[idx_mayor].nombre << "\n";
    std::cout << "Tipo:     " << lista[idx_mayor].tipo << "\n";
    std::cout << "Consumo:  " << lista[idx_mayor].consumo_por_hora << "% por hora\n";
    std::cout << "Bateria:  " << lista[idx_mayor].nivel_bateria << "%\n";
}

// 5. Calcula cuánta batería quedará disponible después de X horas (Proyección sin modificar datos)
void ProyectarBateriaFutura(const Dispositivo lista[], int tamano) {
    int horas = 0;
    std::cout << "\nIngrese las horas para la estimacion de bateria: ";
    std::cin >> horas;

    if (horas <= 0) {
        std::cout << "La cantidad de horas debe ser mayor a 0.\n";
        return;
    }

    std::cout << "\n--- PROYECCION DE BATERIA A " << horas << " HORAS ---\n";
    for (int i = 0; i < tamano; ++i) {
        if (lista[i].esta_encendido) {
            float consumo_proyectado = lista[i].consumo_por_hora * horas;
            float bateria_estimada = lista[i].nivel_bateria - consumo_proyectado;
            
            if (bateria_estimada <= 0.0f) {
                std::cout << "- " << lista[i].nombre << ": Se agotara completamente (0% estimado).\n";
            } else {
                std::cout << "- " << lista[i].nombre << ": Quedara con " << bateria_estimada << "% de bateria.\n";
            }
        } else {
            std::cout << "- " << lista[i].nombre << ": " << lista[i].nivel_bateria << "% (Inactivo, no consume).\n";
        }
    }
}

// 6. Permite cambiar manualmente el estado de encendido/apagado de un dispositivo
void AlternarEstadoDispositivo(Dispositivo lista[], int tamano) {
    MostrarDispositivos(lista, tamano);
    int seleccion = 0;

    std::cout << "Seleccione el numero del dispositivo a cambiar de estado: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > tamano) {
        std::cout << "ERROR: Seleccion fuera de rango.\n";
        return;
    }

    int idx = seleccion - 1;
    if (lista[idx].nivel_bateria <= 0.0f) {
        std::cout << "ERROR: No se puede encender " << lista[idx].nombre << " porque su bateria esta en 0%.\n";
        return;
    }

    lista[idx].esta_encendido = !lista[idx].esta_encendido;
    std::cout << "\n[OK] El dispositivo " << lista[idx].nombre << " ahora esta " 
            << (lista[idx].esta_encendido ? "ENCENDIDO" : "APAGADO") << ".\n";
}

/*7. Simulador de batería
Una empresa desea analizar el comportamiento energético de diferentes dispositivos
electrónicos. De cada dispositivo se conoce su nombre, tipo, nivel actual de batería,
consumo por hora y estado de funcionamiento.
El programa deberá permitir simular el paso de varias horas. Durante la simulación,
cada dispositivo que se encuentre encendido deberá consumir energía de acuerdo con
su consumo por hora.
Cuando un dispositivo llegue a 0 % de batería, deberá dejar de considerarse activo.
El sistema deberá permitir consultar el estado de todos los dispositivos, identificar
cuáles poseen un nivel de batería inferior al 20 %, determinar cuál consume más
energía y calcular cuánta batería queda disponible después de una determinada
cantidad de horas.*/