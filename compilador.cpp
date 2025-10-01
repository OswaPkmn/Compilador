#include <iostream>
#include <string>

using namespace std;

// --- TABLA DE VARIABLES ---
const int MAX_VARIABLES = 100;

struct Variable {
    char nombre;
    string tipo;
    bool ocupada;
};

Variable tablaVariables[MAX_VARIABLES];
int numVariables = 0;

void agregarVariable(char nombre, const string& tipo) {
    if (numVariables < MAX_VARIABLES) {
        tablaVariables[numVariables].nombre = nombre;
        tablaVariables[numVariables].tipo = tipo;
        tablaVariables[numVariables].ocupada = true;
        numVariables++;
    } else {
        cout << "Error: Tabla de variables llena." << endl;
    }
}

string buscarTipoVariable(char nombre) {
    for (int i = 0; i < numVariables; i++) {
        if (tablaVariables[i].nombre == nombre) {
            return tablaVariables[i].tipo;
        }
    }
    return "desconocido";
}

// --- TABLA DE OPERACIONES ---
const int MAX_OPERACIONES = 20;

struct Operacion {
    string nombre;
    char simbolo;
    int nivel;
    bool ocupada;
};

Operacion tablaOperaciones[MAX_OPERACIONES];
int numOperaciones = 0;

void agregarOperacion(const string& nombre, char simbolo, int nivel) {
    if (numOperaciones < MAX_OPERACIONES) {
        tablaOperaciones[numOperaciones].nombre = nombre;
        tablaOperaciones[numOperaciones].simbolo = simbolo;
        tablaOperaciones[numOperaciones].nivel = nivel;
        tablaOperaciones[numOperaciones].ocupada = true;
        numOperaciones++;
    } else {
        cout << "Error: Tabla de operaciones llena." << endl;
    }
}

int buscarNivelOperador(char simbolo) {
    for (int i = 0; i < numOperaciones; i++) {
        if (tablaOperaciones[i].simbolo == simbolo) {
            return tablaOperaciones[i].nivel;
        }
    }
    return -1;
}

// --- MATRIZ PARA LA EXPRESIÓN (ÁRBOL) ---
const int MAX_EXPRESION = 100;

struct NodoArbol {
    char simbolo;
    int izquierda;
    int derecha;
    string tipoElemento;
    string tipoDato;
    int valorNivel;
    bool ocupado;
};

NodoArbol tablaExpresion[MAX_EXPRESION];
int numNodos = 0;

void inicializarTablaExpresion() {
    for (int i = 0; i < MAX_EXPRESION; i++) {
        tablaExpresion[i].ocupado = false;
    }
    numNodos = 0;
}

int agregarNodo(char simbolo, const string& tipoElemento, int valorNivel, const string& tipoDato = "", int izq = -1, int der = -1) {
    if (numNodos < MAX_EXPRESION) {
        tablaExpresion[numNodos].simbolo = simbolo;
        tablaExpresion[numNodos].izquierda = izq;
        tablaExpresion[numNodos].derecha = der;
        tablaExpresion[numNodos].tipoElemento = tipoElemento;
        tablaExpresion[numNodos].tipoDato = tipoDato;
        tablaExpresion[numNodos].valorNivel = valorNivel;
        tablaExpresion[numNodos].ocupado = true;
        numNodos++;
        return numNodos - 1;
    }
    return -1;
}

// Función auxiliar para saber si un caracter es una letra
bool esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// --- LÓGICA DE PROCESAMIENTO (LA MAGIA) ---
int procesarExpresion(const string& expresion) {
    // Arrays para simular las pilas (sin usar la clase stack)
    int pilaOperadores[MAX_EXPRESION];
    int pilaOperandos[MAX_EXPRESION];
    int topOperadores = -1;
    int topOperandos = -1;

    for (char c : expresion) {
        if (c == ' ') continue;

        if (esLetra(c)) { // Es una variable
            string tipo = buscarTipoVariable(c);
            int nodo_idx = agregarNodo(c, "Variable", 0, tipo);
            if (nodo_idx != -1) {
                pilaOperandos[++topOperandos] = nodo_idx;
            }
        } else { // Es un operador
            int nivel_op = buscarNivelOperador(c);
            while (topOperadores >= 0 && buscarNivelOperador(tablaExpresion[pilaOperadores[topOperadores]].simbolo) >= nivel_op) {
                char op = tablaExpresion[pilaOperadores[topOperadores--]].simbolo;
                int der_idx = pilaOperandos[topOperandos--];
                int izq_idx = pilaOperandos[topOperandos--];
                int nuevo_nodo_idx = agregarNodo(op, "Operador", buscarNivelOperador(op), "", izq_idx, der_idx);
                pilaOperandos[++topOperandos] = nuevo_nodo_idx;
            }
            int nodo_op_idx = agregarNodo(c, "Operador", nivel_op);
            if (nodo_op_idx != -1) {
                pilaOperadores[++topOperadores] = nodo_op_idx;
            }
        }
    }

    // Vaciar la pila de operadores restante
    while (topOperadores >= 0) {
        char op = tablaExpresion[pilaOperadores[topOperadores--]].simbolo;
        int der_idx = pilaOperandos[topOperandos--];
        int izq_idx = pilaOperandos[topOperandos--];
        int nuevo_nodo_idx = agregarNodo(op, "Operador", buscarNivelOperador(op), "", izq_idx, der_idx);
        pilaOperandos[++topOperandos] = nuevo_nodo_idx;
    }

    return pilaOperandos[0];
}

// --- FUNCIONES DE IMPRESIÓN ---
void imprimirTablaVariables() {
    cout << "\n--- Tabla de Variables ---" << endl;
    for (int i = 0; i < numVariables; i++) {
        cout << "Nombre: " << tablaVariables[i].nombre << ", Tipo: " << tablaVariables[i].tipo << endl;
    }
}

void imprimirTablaOperaciones() {
    cout << "\n--- Tabla de Operaciones ---" << endl;
    for (int i = 0; i < numOperaciones; i++) {
        cout << "Nombre: " << tablaOperaciones[i].nombre << ", Simbolo: " << tablaOperaciones[i].simbolo << ", Nivel: " << tablaOperaciones[i].nivel << endl;
    }
}

void imprimirTablaExpresion() {
    cout << "\n--- Tabla de la Expresion ---" << endl;
    cout << "Indice | Simbolo | Izq | Der | Tipo | Nivel/Tipo Dato" << endl;
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < numNodos; i++) {
        cout << i << "      | " << tablaExpresion[i].simbolo << "       | " << tablaExpresion[i].izquierda << "   | " << tablaExpresion[i].derecha << "   | " << tablaExpresion[i].tipoElemento << "    | " << tablaExpresion[i].valorNivel << " / " << tablaExpresion[i].tipoDato << endl;
    }
}

void imprimirArbol(int indice, int nivel = 0) {
    if (indice == -1 || !tablaExpresion[indice].ocupado) {
        return;
    }
    imprimirArbol(tablaExpresion[indice].derecha, nivel + 1);
    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }
    cout << tablaExpresion[indice].simbolo << " (" << tablaExpresion[indice].tipoElemento << ")" << endl;
    imprimirArbol(tablaExpresion[indice].izquierda, nivel + 1);
}

// --- MAIN ---
int main() {
    // 1. Llenar tablas de variables y operaciones
    agregarVariable('a', "Int");
    agregarVariable('b', "Float");
    agregarVariable('c', "Int");
    agregarVariable('d', "Float");
    agregarVariable('e', "Int");

    agregarOperacion("Suma", '+', 1);
    agregarOperacion("Multiplicacion", '*', 2);
    agregarOperacion("Division", '/', 2);
    agregarOperacion("Resta",'-',1);

    // 2. Definir y procesar la expresión
    string expresion = "a+b*c-d/c";
    cout << "Expresion a procesar: " << expresion << endl;

    inicializarTablaExpresion();
    int raiz = procesarExpresion(expresion);

    // 3. Mostrar resultados
    imprimirTablaVariables();
    imprimirTablaOperaciones();
    imprimirTablaExpresion();
    cout << "\n--- Arbol de la Expresion ---" << endl;
    imprimirArbol(raiz);
    cout << "\nFin de la simulacion para la expresion: " << expresion << endl;

    return 0;
}