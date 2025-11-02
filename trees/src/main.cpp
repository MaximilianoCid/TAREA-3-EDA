#include "edacal/calculator.hpp"

#include <iostream>

int main() {
    // Instanciamos la calculadora que mantiene las variables y el ultimo arbol.
    edacal::Calculator calculadora;
    std::string line;
   
    std::cout<<"Bienvenido a EdaCal" << std::endl;
    std::cout << ">> " << std::flush;
    // Bucle principal: leer linea, procesarla y repetir hasta recibir "exit".
    while (std::getline(std::cin, line)) {
        if (!calculadora.procesarLinea(line, std::cout)) {
            break;
        }
        std::cout << ">> " << std::flush;
    }
    return 0;
}
