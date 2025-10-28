#ifndef EDACAL_CALCULATOR_HPP
#define EDACAL_CALCULATOR_HPP

#include <iosfwd>
#include <sstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace edacal {

// Calculadora interactiva basada en arboles de expresion que soporta
// asignaciones, conversion a prefijo/postfijo y visualizacion de valores.
class Calculator {
public:
    // Construye una nueva calculadora inicializando la variable especial "ans".
    Calculator();
    // Procesa una linea leida del usuario y escribe las respuestas en el flujo.
    // Devuelve false solo cuando se solicita terminar la sesion.
    bool procesarLinea(const std::string& line, std::ostream& os);
    // Ciclo interactivo completo de la calculadora, leyendo hasta EOF o "exit".
    void ejecutarRepl(std::istream& is, std::ostream& os);

private:
    // Tipos de token reconocidos por el analizador lexico.
    enum class TokenType {
        Number,
        Identifier,
        Operator,
        LParen,
        RParen
    };

    // Token individual producido por la fase de tokenizacion.
    struct Token {
        TokenType type;
        std::string text;
        bool unary;
    };

    // Tipos de nodo que puede contener el arbol de expresion.
    enum class NodeKind {
        Number,
        Identifier,
        Operator
    };

    // Nodo del arbol de expresion que almacena operadores, numeros y variables.
    struct ExpressionNode {
        NodeKind kind;
        std::string value;
        bool unary;
        std::unique_ptr<ExpressionNode> left;
        std::unique_ptr<ExpressionNode> right;

        ExpressionNode(NodeKind kind, std::string value, bool unary = false);
    };

    // Tabla de simbolos con los valores de cada variable conocida.
    std::unordered_map<std::string, long long> variables_;
    // Puntero al ultimo arbol evaluado, usado por show/prefix/postfix.
    std::unique_ptr<ExpressionNode> lastExpression_;

    // Utilidades varias para normalizar cadenas y validar identificadores.
    static std::string recortar(const std::string& text);
    static bool esIdentificador(const std::string& text);
    // Fases del procesador de expresiones: tokenizacion, conversion a postfijo,
    // construccion de arbol y evaluacion.
    std::vector<Token> tokenizar(const std::string& expression, std::string& error) const;
    std::vector<Token> aPostfijo(const std::vector<Token>& tokens, std::string& error) const;
    std::unique_ptr<ExpressionNode> construirArbol(const std::vector<Token>& postfix, std::string& error) const;
    long long evaluar(const ExpressionNode* node, std::string& error) const;
    long long aplicarOperador(const ExpressionNode* node, long long left, long long right, std::string& error) const;
    long long aplicarOperadorUnario(const ExpressionNode* node, long long operand, std::string& error) const;
    // Ayudantes matematicos y de formato para los operadores.
    static long long potenciaEntera(long long base, long long exp);
    static bool esAsociativoDerecha(const Token& token);
    static int precedencia(const Token& token);
    void imprimirArbol(const ExpressionNode* node, const std::string& prefix, bool isRight, std::ostream& os) const;
    void aPrefijo(const ExpressionNode* node, std::vector<std::string>& output) const;
    void aPostfijo(const ExpressionNode* node, std::vector<std::string>& output) const;
    std::string generarSalidaConversion(const std::unique_ptr<ExpressionNode>& node, bool prefix) const;
    // Manejadores especificos para cada tipo de comando expuesto al usuario.
    bool manejarComandoMostrar(std::istringstream& iss, std::ostream& os);
    bool manejarComandoPrefijoPostfijo(const std::string& command, std::istringstream& iss, std::ostream& os);
    bool manejarExpresion(const std::string& expression, std::ostream& os);
};

} // namespace edacal

#endif // EDACAL_CALCULATOR_HPP
