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
    bool processLine(const std::string& line, std::ostream& os);
    // Ciclo interactivo completo de la calculadora, leyendo hasta EOF o "exit".
    void repl(std::istream& is, std::ostream& os);

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
    static std::string trim(const std::string& text);
    static bool isIdentifier(const std::string& text);
    // Fases del procesador de expresiones: tokenizacion, conversion a postfijo,
    // construccion de arbol y evaluacion.
    std::vector<Token> tokenize(const std::string& expression, std::string& error) const;
    std::vector<Token> toPostfix(const std::vector<Token>& tokens, std::string& error) const;
    std::unique_ptr<ExpressionNode> buildTree(const std::vector<Token>& postfix, std::string& error) const;
    long long evaluate(const ExpressionNode* node, std::string& error) const;
    long long applyOperator(const ExpressionNode* node, long long left, long long right, std::string& error) const;
    long long applyUnaryOperator(const ExpressionNode* node, long long operand, std::string& error) const;
    // Ayudantes matematicos y de formato para los operadores.
    static long long ipow(long long base, long long exp);
    static bool isRightAssociative(const Token& token);
    static int precedence(const Token& token);
    void printTree(const ExpressionNode* node, const std::string& prefix, bool isRight, std::ostream& os) const;
    void toPrefix(const ExpressionNode* node, std::vector<std::string>& output) const;
    void toPostfix(const ExpressionNode* node, std::vector<std::string>& output) const;
    std::string makeConversionOutput(const std::unique_ptr<ExpressionNode>& node, bool prefix) const;
    // Manejadores especificos para cada tipo de comando expuesto al usuario.
    bool handleShowCommand(std::istringstream& iss, std::ostream& os);
    bool handlePrefixPostfixCommand(const std::string& command, std::istringstream& iss, std::ostream& os);
    bool handleExpression(const std::string& expression, std::ostream& os);
};

} // namespace edacal

#endif // EDACAL_CALCULATOR_HPP
