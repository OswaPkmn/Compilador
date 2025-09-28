#include <iostream>
#include <cstring>

using namespace std;

// Tamaño máximo predefinido para las tablas
const int MAX_ELEMENTOS = 100;

// Estructura para las variables
struct Variable {
    char nombre[50];
    int tipo_serial;
    int variable_serial;
};

// Estructura para los tipos de datos
struct TipoDeDato {
    char nombre[50];
    char identificador;
    int tipo_serial;
};

// Estructura para las operaciones
struct Operacion {
    char nombre[50];
    char simbolo;
    int nivel;
};

// Arreglos estáticos globales
Variable variables[MAX_ELEMENTOS];
TipoDeDato tipos_datos[MAX_ELEMENTOS];
Operacion operaciones[MAX_ELEMENTOS];

// Contadores de elementos
int num_variables = 0;
int num_tipos_datos = 0;
int num_operaciones = 0;

// Funciones para gestionar los arreglos
void agregarVariable(const char* nombre, int tipo_serial);
void agregarTipoDeDato(const char* nombre, char identificador);
void agregarOperacion(const char* nombre, char simbolo, int nivel);
void mostrarDatos();

// Funciones de apoyo
bool esLetra(char c);
bool esDigito(char c);
bool esAlfanumerico(char c);
bool esEspacio(char c);

void analizarCodigo(const char* codigo);

int main() {
    // Inicialización de las tablas de símbolos y operadores
    agregarTipoDeDato("entero", 'i');
    agregarTipoDeDato("flotante", 'f');
    agregarTipoDeDato("cadena", 's');

    agregarVariable("edad", 0);
    agregarVariable("pi", 1);
    agregarVariable("nombre", 2);

    agregarOperacion("asignacion", '=', 1);
    agregarOperacion("suma", '+', 2);
    agregarOperacion("multiplicacion", '*', 3);
    agregarOperacion("resta", '-', 2);
    agregarOperacion("division", '/', 3);

    mostrarDatos();

    char input_codigo[256];
    cout << "\n----------------------------------------\n";
    cout << "Ingresa una linea de codigo para analizar (ej: int numero = 10;): " << endl;
    cin.getline(input_codigo, 256);

    cout << "\nAnalisis Lexico:\n";
    analizarCodigo(input_codigo);

    // No se necesita liberar memoria con arreglos estáticos
    return 0;
}

// ---
void agregarVariable(const char* nombre, int tipo_serial) {
    if (num_variables < MAX_ELEMENTOS) {
        strcpy(variables[num_variables].nombre, nombre);
        variables[num_variables].tipo_serial = tipo_serial;
        variables[num_variables].variable_serial = num_variables;
        num_variables++;
    } else {
        cout << "Error: Límite de variables alcanzado." << endl;
    }
}

void agregarTipoDeDato(const char* nombre, char identificador) {
    if (num_tipos_datos < MAX_ELEMENTOS) {
        strcpy(tipos_datos[num_tipos_datos].nombre, nombre);
        tipos_datos[num_tipos_datos].identificador = identificador;
        tipos_datos[num_tipos_datos].tipo_serial = num_tipos_datos;
        num_tipos_datos++;
    } else {
        cout << "Error: Límite de tipos de datos alcanzado." << endl;
    }
}

void agregarOperacion(const char* nombre, char simbolo, int nivel) {
    if (num_operaciones < MAX_ELEMENTOS) {
        strcpy(operaciones[num_operaciones].nombre, nombre);
        operaciones[num_operaciones].simbolo = simbolo;
        operaciones[num_operaciones].nivel = nivel;
        num_operaciones++;
    } else {
        cout << "Error: Límite de operaciones alcanzado." << endl;
    }
}

// El resto de las funciones se mantienen igual, ya que solo acceden a los arreglos
// y no necesitan lógica de gestión de memoria dinámica.

void mostrarDatos() {
    cout << "--- Variables ---" << endl;
    for (int i = 0; i < num_variables; ++i) {
        cout << "Serial: " << variables[i].variable_serial
             << ", Nombre: " << variables[i].nombre
             << ", Tipo Serial: " << variables[i].tipo_serial << endl;
    }
    cout << "\n--- Tipos de Datos ---" << endl;
    for (int i = 0; i < num_tipos_datos; ++i) {
        cout << "Serial: " << tipos_datos[i].tipo_serial
             << ", Nombre: " << tipos_datos[i].nombre
             << ", Identificador: " << tipos_datos[i].identificador << endl;
    }
    cout << "\n--- Operaciones ---" << endl;
    for (int i = 0; i < num_operaciones; ++i) {
        cout << "Nombre: " << operaciones[i].nombre
             << ", Simbolo: " << operaciones[i].simbolo
             << ", Nivel: " << operaciones[i].nivel << endl;
    }
}

bool esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool esDigito(char c) {
    return c >= '0' && c <= '9';
}

bool esAlfanumerico(char c) {
    return esLetra(c) || esDigito(c);
}

bool esEspacio(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void analizarCodigo(const char* codigo) {
    const char* ptr = codigo;
    char buffer[50];

    while (*ptr != '\0') {
        if (esEspacio(*ptr)) {
            ptr++;
            continue;
        }

        bool es_operador = false;
        for (int i = 0; i < num_operaciones; ++i) {
            if (*ptr == operaciones[i].simbolo) {
                cout << "'" << *ptr << "': Operador de " << operaciones[i].nombre << endl;
                es_operador = true;
                break;
            }
        }
        if (es_operador) {
            ptr++;
            continue;
        }

        if (esLetra(*ptr)) {
            int i = 0;
            const char* inicio_token = ptr;
            while (esAlfanumerico(*ptr) && i < 49) {
                buffer[i++] = *ptr++;
            }
            buffer[i] = '\0';

            bool es_tipo = false;
            for (int j = 0; j < num_tipos_datos; ++j) {
                if (strcmp(buffer, tipos_datos[j].nombre) == 0) {
                    cout << "'" << buffer << "': Tipo de dato '" << tipos_datos[j].nombre << "'" << endl;
                    es_tipo = true;
                    break;
                }
            }
            if (es_tipo) continue;

            bool es_variable = false;
            for (int j = 0; j < num_variables; ++j) {
                if (strcmp(buffer, variables[j].nombre) == 0) {
                    cout << "'" << buffer << "': Variable con serial " << variables[j].variable_serial << endl;
                    es_variable = true;
                    break;
                }
            }
            if (es_variable) continue;

            cout << "'" << buffer << "': Identificador (desconocido)" << endl;
            continue;
        }

        if (esDigito(*ptr)) {
            int i = 0;
            const char* inicio_token = ptr;
            while (esDigito(*ptr) && i < 49) {
                buffer[i++] = *ptr++;
            }
            buffer[i] = '\0';
            cout << "'" << buffer << "': Numero entero" << endl;
            continue;
        }

        if (*ptr != '\0') {
            cout << "'" << *ptr << "': Símbolo desconocido" << endl;
            ptr++;
        }
    }
}