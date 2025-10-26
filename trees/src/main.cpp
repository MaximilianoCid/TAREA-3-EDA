#include "edacal/calculator.hpp"

#include <iostream>

int main() {
    // Instanciamos la calculadora que mantiene las variables y el ultimo arbol.
    edacal::Calculator calculator;
    std::string line;
    // Prompt inicial para el usuario.
    std::cout << ">> " << std::flush;
    // Bucle principal: leer linea, procesarla y repetir hasta recibir "exit".
    while (std::getline(std::cin, line)) {
        if (!calculator.processLine(line, std::cout)) {
            break;
        }
        std::cout << ">> " << std::flush;
    }
    return 0;
}
