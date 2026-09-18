# Apuntes_PED
El sufijo consta de un punto seguido por un carácter o grupo de caracteres y se denomina extensión.No usar espacios en nombres de archivo (podemos separar las palabras con guiones medios o bajos).Utilizar sólo caracteres alfanuméricos.

Snake case, es la convención que compone las palabras separadas por barra baja ( underscore ) en vez de espacios y con la primera letra de cada palabra en minúscula. Es utilizado en nombres de variables y parámetros.
Pascal Case, la primera letra de cada palabra se escribe en mayúscula y las demás en minúsculas. Es utilizado para funciones, structs

# funciones
Subalgoritmos o Subprogramas

Definición y propósito: Son unidades de programa o módulos diseñados para ejecutar una tarea específica. Ayudan a resolver problemas complejos dividiéndolos en subproblemas más pequeños.

Tipos: Se dividen principalmente en funciones y procedimientos.

Reutilización de código: Se escriben una sola vez y pueden ser referenciados o llamados desde distintos puntos del programa, lo que evita la duplicación innecesaria de código.

Metodología: Utilizan la técnica de “divide y vencerás” (divide and conquer).

Tipos de funciones:
Internas o intrínsecas (estándar): Vienen incorporadas en el sistema o lenguaje de programación.
Externas (del usuario): Las define el programador cuando las funciones estándar no son suficientes para el cálculo deseado.

Objetivo principal: Diseñadas para realizar tareas específicas recibiendo argumentos y retornando un solo valor.
Definición: Los parámetros o argumentos son variables locales que ocupan un espacio de memoria reservado por el Sistema Operativo.

Parámetros formales: Se especifican en la definición de la función y se conocen como ficticios o mudos ("dummy").

Parámetros actuales o reales: Se utilizan al invocar o llamar a la función. Pueden ser constantes, variables, expresiones, valores de retorno o nombres de otras funciones o procedimientos.

# arreglos
Definición: Es un conjunto ordenado y finito de elementos homogéneos (todos los valores deben ser del mismo tipo de dato).

Estructura estática: Su tamaño se define al momento de la creación y no cambia durante la ejecución del programa.

Acceso por índice: Cada elemento se consulta utilizando su posición dentro del arreglo, comenzando habitualmente desde el índice 0.

Manejo de memoria: El compilador reserva un espacio continuo en memoria para almacenar sus elementos en direcciones consecutivas.

Clasificación:

Unidimensionales: Vectores.

Bidimensionales: Matrices.

1. Declaración de un arreglo

Concepto: Consiste en indicar el tipo de dato que almacenará, un nombre identificador y el tamaño que tendrá.

Regla: Todos los elementos dentro del arreglo deben ser del mismo tipo de dato.

Sintaxis:

C++
int arreglo[4];
2. Inicialización de un arreglo

Concepto: Consiste en asignar valores iniciales al arreglo desde su creación.

Regla: Los elementos se encierran entre llaves {} y se separan por comas ,. Si los datos son cadenas (string) o caracteres (char), los elementos se escriben entre comillas.

Con tamaño definido:

C++
int arreglo[4] = {1, 2, 3, 4};
Con tamaño implícito (se deduce automáticamente):

C++
int arreglo[] = {1, 2, 3, 4};

# struc 
Un struct (estructura) en C++ es un tipo de dato definido por el usuario que permite agrupar múltiples variables de diferentes tipos bajo un mismo nombre. Es fundamental para organizar datos relacionados.

Sintaxis básica y declaración

C++
#include <iostream>
#include <string>
using namespace std;

// Declaración de la estructura
struct Alumno {
    int codigo;
    string nombre;
    int anioNac;
}; // ¡No olvides el punto y coma al final!

int main() {
    // Declaración de una variable tipo struct
    Alumno alumno1;
    
    return 0;
}
Acceso y asignación de datos

Acceso a un campo: Se utiliza el operador punto (.) seguido del nombre de la variable y el miembro.

Asignación individual: alumno1.codigo = 45454;

Asignación completa (por lista):

C++
Alumno alumno2 = {4478, "Pedro", 1997};

Estructuras Anidadas
Una estructura puede incluir otra estructura previamente declarada dentro de sus propios miembros.

C++
#include <iostream>
#include <string>
using namespace std;

struct Direccion {
    string municipio;
    string departamento;
    int numeroCasa;
};

struct Alumno {
    int codigo;
    string nombre;
    int anioNac;
    Direccion dir; // Estructura anidada
};

int main() {
    Alumno alumno1;

    // Acceso a los campos anidados mediante puntos consecutivos (.)
    alumno1.dir.departamento = "San Salvador";
    alumno1.dir.municipio = "San Salvador Centro";
    alumno1.dir.numeroCasa = 12;

    cout << "Departamento: " << alumno1.dir.departamento << endl;
    return 0;
}
Recorrido con Bucles
Para procesar múltiples registros (arreglos de struct), se utilizan bucles (for, while o do-while):

C++
Alumno alumnos[3];

// Lectura de datos mediante un bucle
for (int i = 0; i < 3; i++) {
    cout << "Ingrese código del alumno " << i + 1 << ": ";
    cin >> alumnos[i].codigo;
    cout << "Ingrese departamento: ";
    cin >> alumnos[i].dir.departamento;
}

// Impresión de datos
for (int i = 0; i < 3; i++) {
    cout << "Alumno " << alumnos[i].codigo 
         << " vive en " << alumnos[i].dir.departamento << endl;
}

# vector 1. Arreglo Unidimensional Tradicional (Vector como Parámetro)
Cuando trabajas con arreglos estáticos de tipo int, char, float, etc.:

Paso por referencia implícito: A diferencia de las variables simples (como un int o float), los arreglos no se copian al pasarse a una función. Lo que recibe la función es la dirección de memoria del arreglo original.

Modificaciones directas: Si cambias el valor de una posición del arreglo dentro de la función, el cambio afectará directamente a la variable definida en la función main (o donde se haya declarado).

Restricción de retorno: Una función no puede retornar un arreglo, únicamente puede retornar un solo valor simple o un puntero/objeto.

Ejemplo:

C++
int calcularMayoresEdad(int edad[]) {
    int contador = 0;
    for (int i = 0; i < 5; i++) {
        if (edad[i] >= 18) {
            contador++;
        }
    }
    return contador;
}
2. Librería Estándar: std::vector
El tipo std::vector pertenece a la Librería Estándar de Plantillas (STL) y ofrece ventajas significativas sobre los arreglos estáticos:

Tamaño dinámico: Crece o se reduce de forma automática según las necesidades del programa durante la ejecución.

Gestión de memoria: Administra internamente el espacio en memoria, evitando desbordamientos de buffer manuales.

Métodos integrados: Ofrece funciones útiles como .push_back(), .pop_back(), .size(), .clear(), entre otros.

3. Utilidad complementaria: std::pair
En el contexto de la librería vector, se suele emplear la estructura std::pair para almacenar pares de datos vinculados (por ejemplo, coordenadas (x, y) o un usuario con su edad). Un std::vector<std::pair<int, string>> permite manejar listas compuestas por parejas de información.

# punteros y referencias

Punteros: Variables que almacenan la dirección de memoria de otra variable en lugar de su valor directo. Permiten acceder y manipular directamente los datos almacenados en esa ubicación de memoria.

Referencias: Alias o nombres alternativos para una variable ya existente, permitiendo trabajar sobre la misma dirección de memoria sin utilizar la sintaxis explícita de punteros.

Principales usos de los punteros:

Control directo de la memoria: Permiten acceder y modificar direcciones de memoria específicas.

Manipulación de variables: Facilitan el acceso y modificación de datos de forma eficiente.

Gestión de la memoria: Fundamentales para la asignación dinámica (reserva y liberación de memoria en tiempo de ejecución).

Estructuras de datos dinámicas: Base esencial para implementar listas enlazadas, árboles, grafos, pilas y colas.

Paso de parámetros por puntero: Permite modificar el valor original de una variable dentro de una función.

Programación de bajo nivel: Utilizados para interactuar directamente con el hardware y optimizar el rendimiento.

Operadores y Sintaxis Principal

Operador de dirección (&): Obtiene la dirección de memoria en la que está almacenada una variable.

Operador de indirección o desreferencia (*): Se utiliza tanto para declarar una variable de tipo puntero como para acceder o modificar el valor contenido en la dirección de memoria apuntada.

Declaración e Inicialización

Sintaxis de declaración: Se define especificando el tipo de dato, seguido del asterisco y el nombre del puntero (por ejemplo: int *ptr;).

Asignación de dirección: Se asigna la dirección de una variable existente usando el operador & (por ejemplo: ptr = &variable;).

Inicialización segura: Si un puntero no apunta a ninguna variable válida inmediatamente, debe inicializarse en NULL o nullptr para evitar punteros colgados (dangling pointers) o accesos indebidos a memoria.

Ejemplo representativo del flujo:

Se declara una variable entera x = 10;.

Se declara un puntero a entero int *p;.

Se asigna la dirección: p = &x; (ahora p guarda la posición de memoria de x).

Al imprimir *p, el programa devuelve el valor 10.

