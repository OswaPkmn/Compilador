#include <iostream>
#include <cctype>  // isalpha, isdigit
#include <cstring> // strlen

// Definimos niveles de precedencia
int nivelPrecedencia(char op) {
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    // Expresión aritmética
    std::string expr = "a+b*c-d/2";

    // Guardamos la expresión dinámicamente usando un apuntador
    char* ptrExpr = new char[expr.size() + 1]; // +1 para '\0'
    std::strcpy(ptrExpr, expr.c_str());

    std::cout << "Expresion guardada en apuntador: " << ptrExpr << std::endl;

    std::cout << "\nTokens encontrados:\n";
    for (size_t i = 0; i < strlen(ptrExpr); i++) {
        char c = ptrExpr[i];
        if (std::isalpha(c)) {
            std::cout << "Variable: " << c << std::endl;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            std::cout << "Operador: " << c
                      << " | Nivel: " << nivelPrecedencia(c) << std::endl;
        } else if (std::isdigit(c)) {
            std::cout << "Número: " << c << std::endl;
        }
    }

    // Liberamos memoria
    delete[] ptrExpr;

    return 0;
}
