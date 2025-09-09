#include <iostream>
#include <unordered_map>
using namespace std;

// Función para determinar el tipo de dato
string obtenerTipo(char c, unordered_map<char, string>& tablaTipos) {
    if (tablaTipos.find(c) != tablaTipos.end()) {
        return tablaTipos[c];
    } else if (isdigit(c)) {
        return "Número entero";
    } else if (isalpha(c)) {
        return "Identificador";
    } else {
        return "Desconocido";
    }
}

int main() {
    const char* expresion = "a+b*c-d/e";
    const char* ptr = expresion;

    // Tabla de tipos de operadores
    unordered_map<char, string> tablaTipos = {
        {'+', "Operador nivel 1"},
        {'-', "Operador nivel 1"},
        {'*', "Operador nivel 2"},
        {'/', "Operador nivel 2"}
    };

    cout << "Caracter\tTipo de dato" << endl;
    cout << "----------------------------------------" << endl;

    while (*ptr != '\0') {
        char c = *ptr;
        string tipo = obtenerTipo(c, tablaTipos);

        cout << c << "\t\t" << tipo << endl;
        ptr++;
    }

    return 0;
}