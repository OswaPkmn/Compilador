#include <iostream>
#include <cstring> // Incluido por si acaso, aunque no es estrictamente necesario para este ejemplo

using namespace std;

// Estructura para las variables
struct Variable {
    char nombre[50];
    int tipo_serial; // Referencia al numero serial del tipo de dato
    int variable_serial;
};

// Estructura para los tipos de datos
struct TipoDeDato {
    char nombre[50];
    char identificador; // Por ejemplo, 'i' para int, 'f' para float
    int tipo_serial;
};

// Estructura para las operaciones
struct Operacion {
    char nombre[50];
    char simbolo;
    int nivel; // Nivel de precedencia
};

// Variables globales para los arreglos dinámicos
Variable* variables = nullptr;
TipoDeDato* tipos_datos = nullptr;
Operacion* operaciones = nullptr;

// Contadores de elementos
int num_variables = 0;
int num_tipos_datos = 0;
int num_operaciones = 0;

// Funciones para gestionar los arreglos dinámicos
void agregarVariable(const char* nombre, int tipo_serial);
void agregarTipoDeDato(const char* nombre, char identificador);
void agregarOperacion(const char* nombre, char simbolo, int nivel);
void mostrarDatos();
void liberarMemoria();

int main() {
    // Ejemplo de uso de las funciones
    agregarTipoDeDato("entero", 'i');
    agregarTipoDeDato("flotante", 'f');
    agregarTipoDeDato("cadena", 's');

    agregarVariable("edad", 0); // El serial 0 corresponde a "entero"
    agregarVariable("pi", 1); // El serial 1 corresponde a "flotante"
    agregarVariable("nombre", 2); // El serial 2 corresponde a "cadena"

    agregarOperacion("asignacion", '=', 1);
    agregarOperacion("suma", '+', 2);
    agregarOperacion("multiplicacion", '*', 3);

    mostrarDatos();

    // Editar un elemento (ejemplo)
    operaciones[0].nivel = 10;
    cout << "\nNivel de la operacion 'asignacion' ha sido actualizado a: " << operaciones[0].nivel << endl;

    liberarMemoria();

    return 0;
}

void agregarVariable(const char* nombre, int tipo_serial) {
    Variable* nuevo_variables = new Variable[num_variables + 1];

    // Copiar los datos existentes
    for (int i = 0; i < num_variables; ++i) {
        nuevo_variables[i] = variables[i];
    }

    // Agregar el nuevo elemento
    strcpy(nuevo_variables[num_variables].nombre, nombre);
    nuevo_variables[num_variables].tipo_serial = tipo_serial;
    nuevo_variables[num_variables].variable_serial = num_variables;

    // Liberar memoria antigua y actualizar el puntero
    delete[] variables;
    variables = nuevo_variables;
    num_variables++;
}