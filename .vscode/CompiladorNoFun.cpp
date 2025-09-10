#include <iostream>
#include <string>
using namespace std;

int main() {
    string expresion = "a+b*c-d/e";

    // -----------------------------
    // TABLA DE TIPOS DE DATO
    // [id, nombre]
    string tablaTipos[2][2] = {
        {"1", "Número entero"},
        {"2", "Identificador"}
    };

    // -----------------------------
    // TABLA DE SÍMBOLOS
    // [variable, id_tipo]
    string tablaSimbolos[5][2] = {
        {"a", "2"},
        {"b", "2"},
        {"c", "2"},
        {"d", "2"},
        {"e", "2"}
    };

    // -----------------------------
    // TABLA DE OPERACIONES
    // [símbolo, nombre, nivel]
    string tablaOperaciones[4][3] = {
        {"+", "Suma", "1"},
        {"-", "Resta", "1"},
        {"*", "Multiplicación", "2"},
        {"/", "División", "2"}
    };

    cout << "Caracter\tTipo / Operación" << endl;
    cout << "------------------------------------------------" << endl;

    // Recorremos la expresión
    for (int i = 0; i < expresion.size(); i++) {
        string caracter(1, expresion[i]);
        bool encontrado = false;

        // Buscar en tabla de símbolos
        for (int j = 0; j < 5; j++) {
            if (tablaSimbolos[j][0] == caracter) {
                string idTipo = tablaSimbolos[j][1];
                for (int k = 0; k < 2; k++) {
                    if (tablaTipos[k][0] == idTipo) {
                        cout << caracter << "\t\t" << tablaTipos[k][1] << endl;
                        encontrado = true;
                        break;
                    }
                }
            }
        }

        // Buscar en tabla de operaciones
        if (!encontrado) {
            for (int j = 0; j < 4; j++) {
                if (tablaOperaciones[j][0] == caracter) {
                    cout << caracter << "\t\t" << tablaOperaciones[j][1]
                         << " (Nivel " << tablaOperaciones[j][2] << ")" << endl;
                    encontrado = true;
                    break;
                }
            }
        }

        // Si no está en ninguna tabla
        if (!encontrado) {
            cout << caracter << "\t\tDesconocido" << endl;
        }
    }

    return 0;
}
