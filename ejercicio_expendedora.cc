#include <iostream>
#include <string>
#include <vector>

struct Producto {
    std::string nombre;
    double precio;
    int cantidad_disponible;
    int unidades_vendidas;
};

// Declaración de funciones
void ConsultarProductos(const std::vector<Producto>& inventario);
void RealizarCompra(std::vector<Producto>& inventario, double& ingresos_totales);
void ReabastecerProducto(std::vector<Producto>& inventario);
void MostrarReporteFinal(const std::vector<Producto>& inventario, double ingresos_totales);

int main() {
    // Inicialización del vector con productos
    std::vector<Producto> inventario = {
        {"Agua Mineral", 1.00, 5, 0},
        {"Gaseosa", 1.50, 4, 0},
        {"Papas Fritas", 1.25, 3, 0},
        {"Chocolate", 2.00, 2, 0},
        {"Galletas", 1.10, 6, 0}
    };

    double ingresos_totales = 0.0;
    int opcion = 0;

    do {
        std::cout << "\n====================================\n";
        std::cout << "        MAQUINA EXPENDEDORA         \n";
        std::cout << "====================================\n";
        std::cout << "1. Consultar productos disponibles\n";
        std::cout << "2. Comprar un producto\n";
        std::cout << "3. Reabastecer un producto\n";
        std::cout << "4. Finalizar operacion y ver reporte\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ConsultarProductos(inventario);
                break;
            case 2:
                RealizarCompra(inventario, ingresos_totales);
                break;
            case 3:
                ReabastecerProducto(inventario);
                break;
            case 4:
                std::cout << "\nCerrando sistema de la maquina...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    MostrarReporteFinal(inventario, ingresos_totales);

    return 0;
}

void ConsultarProductos(const std::vector<Producto>& inventario) {
    std::cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    for (size_t i = 0; i < inventario.size(); ++i) {
        std::cout << (i + 1) << ". " << inventario[i].nombre << " | Precio: $" << inventario[i].precio 
                << " | Disponibles: " << inventario[i].cantidad_disponible;
        
        if (inventario[i].cantidad_disponible == 0) {
            std::cout << " (AGOTADO)";
        }
        std::cout << "\n";
    }
}

void RealizarCompra(std::vector<Producto>& inventario, double& ingresos_totales) {
    ConsultarProductos(inventario);

    int seleccion = 0;
    std::cout << "\nSeleccione el numero del producto que desea comprar: ";
    std::cin >> seleccion;

    // Validación 1: Verificar que el producto exista
    if (seleccion < 1 || seleccion > static_cast<int>(inventario.size())) {
        std::cout << "ERROR: El producto seleccionado no existe.\n";
        return;
    }

    Producto& p = inventario[seleccion - 1];

    // Validación 2: Verificar disponibilidad de unidades
    if (p.cantidad_disponible <= 0) {
        std::cout << "ERROR: No hay unidades disponibles de '" << p.nombre << "'.\n";
        return;
    }

    p.cantidad_disponible--;
    p.unidades_vendidas++;
    ingresos_totales += p.precio;

    std::cout << "Venta completada con exito. Entregando: " << p.nombre << "\n";
}

void ReabastecerProducto(std::vector<Producto>& inventario) {
    ConsultarProductos(inventario);

    int seleccion = 0;
    std::cout << "\nSeleccione el numero del producto a reabastecer: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > static_cast<int>(inventario.size())) {
        std::cout << "ERROR: El producto no existe.\n";
        return;
    }

    int cantidad = 0;
    std::cout << "Ingrese la cantidad de unidades a agregar: ";
    std::cin >> cantidad;

    if (cantidad <= 0) {
        std::cout << "ERROR: La cantidad debe ser mayor a cero.\n";
        return;
    }

    inventario[seleccion - 1].cantidad_disponible += cantidad;

    std::cout << "Reabastecimiento exitoso. Nuevo stock de "<< inventario[seleccion - 1].nombre << ": " 
            << inventario[seleccion - 1].cantidad_disponible << " unidades.\n";
}

void MostrarReporteFinal(const std::vector<Producto>& inventario, double ingresos_totales) {
    int total_vendidos = 0;
    int max_vendidos = 0;
    std::string producto_mas_vendido = "Ninguno";

    for (const auto& p : inventario) {
        total_vendidos += p.unidades_vendidas;

        if (p.unidades_vendidas > max_vendidos) {
            max_vendidos = p.unidades_vendidas;
            producto_mas_vendido = p.nombre;
        }
    }

    std::cout << "\n====================================\n";
    std::cout << "          REPORTE FINAL             \n";
    std::cout << "====================================\n";
    std::cout << "Cantidad total de productos vendidos: " << total_vendidos << "\n";
    std::cout << "Ingresos totales generados: $" << ingresos_totales << "\n";
    
    if (max_vendidos > 0) {
        std::cout << "Producto mas vendido: " << producto_mas_vendido << " (" << max_vendidos << " unidades)\n";
    } else {
        std::cout << "No se realizaron ventas\n";
    }
    std::cout << "====================================\n";
}

/*Máquina expendedora
Una máquina expendedora contiene una cantidad limitada de productos. Cada
producto tiene un nombre, precio, cantidad disponible y un registro de cuántas
unidades se han vendido.
El usuario debe poder consultar los productos disponibles y seleccionar uno para
realizar una compra. El sistema debe verificar que el producto exista y que haya
unidades disponibles antes de completar la venta.
También debe existir una opción para reabastecer productos. Al finalizar la operación,
el programa deberá mostrar información como el producto más vendido*/