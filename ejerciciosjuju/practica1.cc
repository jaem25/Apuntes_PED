#include <iostream>
#include <string>
#include <vector>
#include <random>

// Struct del Producto
struct Producto {
    int id;
    std::string nombre;
    float precio;
    int stock;
};

// Prototipos de funciones
int GenerarIDRandom();
void AgregarProducto(std::vector<Producto>& inventario);
void MostrarInventario(const std::vector<Producto>& inventario);
void BuscarID(const std::vector<Producto>& inventario);
void RegistrarVenta(std::vector<Producto>& inventario);

int main() {
    std::vector<Producto> inventario;
    int opcion = 0;

    do {
        std::cout << "\n---- Consola de Administración de Inventario y Ventas ----\n";
        std::cout << "1) Agregar producto\n";
        std::cout << "2) Mostrar inventario\n";
        std::cout << "3) Buscar producto por ID\n";
        std::cout << "4) Registrar venta\n";
        std::cout << "5) Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                AgregarProducto(inventario);
                break;
            case 2:
                MostrarInventario(inventario);
                break;
            case 3:
                BuscarID(inventario);
                break;
            case 4:
                RegistrarVenta(inventario);
                break;
            case 5: 
                std::cout << "\nSaliendo del sistema...\n";
                break;
            default:
                std::cout << "\nERROR: OPCION INVALIDA\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}

// Genera un ID aleatorio entre 1000 y 9999
int GenerarIDRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1000, 9999);
    return dist(gen);
}

void AgregarProducto(std::vector<Producto>& inventario) {
    char respuesta;
    std::cout << "¿Desea ingresar un producto? (s/n): ";
    std::cin >> respuesta;

    if (respuesta == 'n' || respuesta == 'N') {
        return;
    }

    Producto nuevoProducto;
    nuevoProducto.id = GenerarIDRandom();

    std::cout << "Nombre del producto: ";
    std::cin >> nuevoProducto.nombre;

    std::cout << "Precio del producto: ";
    std::cin >> nuevoProducto.precio;

    std::cout << "Stock del producto: ";
    std::cin >> nuevoProducto.stock;

    inventario.push_back(nuevoProducto);

    std::cout << "\n¡Producto agregado con exito! ID asignado: " << nuevoProducto.id << "\n";
}

void MostrarInventario(const std::vector<Producto>& inventario) {
    if (inventario.empty()) {
        std::cout << "\nEl inventario esta vacio.\n";
        return;
    }

    std::cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    for (size_t i = 0; i < inventario.size(); ++i) {
        std::cout << "ID: " << inventario[i].id << " | " << inventario[i].nombre << " | Precio: $" << inventario[i].precio << " | Disponibles: " << inventario[i].stock;
        
        if (inventario[i].stock == 0) {
            std::cout << " (AGOTADO)";
        }
        std::cout << "\n";
    }
}

void BuscarID(const std::vector<Producto>& inventario) {
    if (inventario.empty()) {
        std::cout << "\nEl inventario esta vacio.\n";
        return;
    }

    int id_ingresado;
    std::cout << "\nIngrese el ID del producto que desea buscar: ";
    std::cin >> id_ingresado;

    bool encontrado = false;

    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i].id == id_ingresado) {
            std::cout << "\n--- PRODUCTO ENCONTRADO ---\n";
            std::cout << "ID: " << inventario[i].id << "\n";
            std::cout << "Nombre: " << inventario[i].nombre << "\n";
            std::cout << "Precio: $" << inventario[i].precio << "\n";
            std::cout << "Stock: " << inventario[i].stock << "\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "\nNo se encontro ningun producto con el ID: " << id_ingresado << "\n";
    }
}

void RegistrarVenta(std::vector<Producto>& inventario) {
    if (inventario.empty()) { //muestra que esta vacio empty
        std::cout << "\nEl inventario esta vacio. No hay productos para vender.\n";
        return;
    }

    MostrarInventario(inventario);

    int id_seleccion = 0;
    std::cout << "\nIngrese el ID del producto que desea comprar: ";
    std::cin >> id_seleccion;

    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i].id == id_seleccion) {
            
            if (inventario[i].stock <= 0) {
                std::cout << "ERROR: No hay unidades disponibles de '" << inventario[i].nombre << "'.\n";
                return;
            }

            int cantidad = 0;
            std::cout << "Ingrese la cantidad a comprar: ";
            std::cin >> cantidad;

            if (cantidad <= 0) {
                std::cout << "ERROR: La cantidad debe ser mayor a 0.\n";
                return;
            }

            if (cantidad > inventario[i].stock) {
                std::cout << "ERROR: Stock insuficiente. Solo hay " << inventario[i].stock << " unidades.\n";
                return;
            }

            inventario[i].stock -= cantidad;
            float total = cantidad * inventario[i].precio;

            std::cout << "\n--- VENTA COMPLETADA ---";
            std::cout << "\nProducto: " << inventario[i].nombre;
            std::cout << "\nCantidad: " << cantidad;
            std::cout << "\nTotal a pagar: $" << total << "\n";
            std::cout << "¡Disfrute de su compra, tenga un lindo dia!\n";
            return;
        }
    }

    std::cout << "ERROR: El producto con ID " << id_seleccion << " no existe.\n";
}