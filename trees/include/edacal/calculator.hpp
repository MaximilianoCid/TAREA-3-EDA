#ifndef EDACAL_CALCULATOR_HPP
#define EDACAL_CALCULATOR_HPP

#include <iosfwd>
#include <sstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace edacal {

class Calculator {
public:
    Calculator();
    bool procesarLinea(const std::string& line, std::ostream& os);
    void ejecutarRepl(std::istream& is, std::ostream& os);

private:
    enum class TokenType {
        Number,
        Identifier,
        Operator,
        LParen,
        RParen
    };
    struct Token {
        TokenType type;
        std::string text;
        bool unary;
    };
    enum class NodeKind {
        Number,
        Identifier,
        Operator
    };
    struct ExpressionNode {
        NodeKind kind;
        std::string value;
        bool unary;
        std::unique_ptr<ExpressionNode> left;
        std::unique_ptr<ExpressionNode> right;

        ExpressionNode(NodeKind kind, std::string value, bool unary = false);
    };
    std::unordered_map<std::string, long long> variables_;
    std::unique_ptr<ExpressionNode> lastExpression_;
    static std::string recortar(const std::string& text);
    static bool esIdentificador(const std::string& text);
    std::vector<Token> tokenizar(const std::string& expression, std::string& error) const;
    std::vector<Token> aposfix(const std::vector<Token>& tokens, std::string& error) const;
    std::unique_ptr<ExpressionNode> construirArbol(const std::vector<Token>& posfix, std::string& error) const;
    long long evaluar(const ExpressionNode* node, std::string& error) const;
    long long aplicarOperador(const ExpressionNode* node, long long left, long long right, std::string& error) const;
    long long aplicarOperadorUnario(const ExpressionNode* node, long long operand, std::string& error) const;
    static long long potenciaEntera(long long base, long long exp);
    static bool esAsociativoDerecha(const Token& token);
    static int precedencia(const Token& token);
    void imprimirArbol(const ExpressionNode* node, const std::string& prefix, bool isRight, std::ostream& os) const;
    void aPrefijo(const ExpressionNode* node, std::vector<std::string>& output) const;
    void aposfix(const ExpressionNode* node, std::vector<std::string>& output) const;
    std::string generarSalidaConversion(const std::unique_ptr<ExpressionNode>& node, bool prefix) const;
    bool manejarComandoMostrar(std::istringstream& iss, std::ostream& os);
    bool manejarComandoPrefijoposfix(const std::string& command, std::istringstream& iss, std::ostream& os);
    bool manejarExpresion(const std::string& expression, std::ostream& os);
};

} 

#endif
