#include "edacal/calculator.hpp"
#include "edacal/stack.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace edacal {

Calculator::ExpressionNode::ExpressionNode(NodeKind kind, std::string value, bool unary)
    : kind(kind), value(std::move(value)), unary(unary), left(nullptr), right(nullptr) {}

Calculator::Calculator() : variables_(), lastExpression_(nullptr) {
    variables_["ans"] = 0;
}

bool Calculator::procesarLinea(const std::string& line, std::ostream& os) {
    std::string trimmed = recortar(line);
    if (trimmed.empty()) {
        return true;
    }
    if (trimmed == "exit") {
        return false;
    }

    std::istringstream iss(trimmed);
    std::string command;
    iss >> command;

    if (command == "show") {
        return manejarComandoMostrar(iss, os);
    }
    if (command == "tree") {
        if (!lastExpression_) {
            os << "No hay expresion para mostrar" << std::endl;
            return true;
        }
        imprimirArbol(lastExpression_.get(), "", false, os);
        return true;
    }
    if (command == "prefix" || command == "posfix") {
        return manejarComandoPrefijoposfix(command, iss, os);
    }

    return manejarExpresion(trimmed, os);
}


void Calculator::ejecutarRepl(std::istream& is, std::ostream& os) {
    std::string line;
    while (true) {
        os << ">> " << std::flush;
        if (!std::getline(is, line)) {
            break;
        }
        if (!procesarLinea(line, os)) {
            break;
        }
    }
}

std::string Calculator::recortar(const std::string& text) {
    auto it_begin = std::find_if_not(text.begin(), text.end(), [](unsigned char ch) { return std::isspace(ch); });
    auto it_end = std::find_if_not(text.rbegin(), text.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
    if (it_begin >= it_end) {
        return "";
    }
    return std::string(it_begin, it_end);
}

bool Calculator::esIdentificador(const std::string& text) {
    if (text.empty()) {
        return false;
    }
    if (!(std::isalpha(static_cast<unsigned char>(text.front())) || text.front() == '_')) {
        return false;
    }
    for (char ch : text) {
        if (!(std::isalnum(static_cast<unsigned char>(ch)) || ch == '_')) {
            return false;
        }
    }
    return true;
}

std::vector<Calculator::Token> Calculator::tokenizar(const std::string& expression, std::string& error) const {
    std::vector<Token> tokens;
    for (size_t i = 0; i < expression.size();) {
        char ch = expression[i];
        if (std::isspace(static_cast<unsigned char>(ch))) {
            ++i;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            size_t j = i + 1;
            while (j < expression.size() && std::isdigit(static_cast<unsigned char>(expression[j]))) {
                ++j;
            }
            tokens.push_back({TokenType::Number, expression.substr(i, j - i), false});
            i = j;
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(ch)) || ch == '_') {
            size_t j = i + 1;
            while (j < expression.size() && (std::isalnum(static_cast<unsigned char>(expression[j])) || expression[j] == '_')) {
                ++j;
            }
            size_t k = j;
            while (k < expression.size() && std::isspace(static_cast<unsigned char>(expression[k]))) {
                ++k;
            }
            if (k < expression.size() && expression[k] == '(') {
                tokens.push_back({TokenType::Function, expression.substr(i, j - i), false});
            } else {
                tokens.push_back({TokenType::Identifier, expression.substr(i, j - i), false});
            }
            i = j;
            continue;
        }
        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                tokens.push_back({TokenType::Operator, std::string(1, ch), false});
                ++i;
                break;
            case '(':
                tokens.push_back({TokenType::LParen, std::string(1, ch), false});
                ++i;
                break;
            case ')':
                tokens.push_back({TokenType::RParen, std::string(1, ch), false});
                ++i;
                break;
            default:
                error = std::string("Caracter invalido en la expresion: ") + ch;
                return {};
        }
    }
    return tokens;
}

bool Calculator::esAsociativoDerecha(const Token& token) {
    if (token.unary) {
        return true;
    }
    return token.text == "^";
}

int Calculator::precedencia(const Token& token) {
    if (token.unary) {
        return 4;
    }
    if (token.text == "^") {
        return 3;
    }
    if (token.text == "*" || token.text == "/" || token.text == "%") {
        return 2;
    }
    if (token.text == "+" || token.text == "-") {
        return 1;
    }
    return 0;
}

std::vector<Calculator::Token> Calculator::aposfix(const std::vector<Token>& inputTokens, std::string& error) const {
    std::vector<Token> output;
    Pila<Token> pilaOperadores;
    Token prevToken{TokenType::Operator, "", false};

    for (size_t i = 0; i < inputTokens.size(); ++i) {
        Token token = inputTokens[i];
        if (token.type == TokenType::Operator && (token.text == "+" || token.text == "-")) {
            bool isUnary = prevToken.type == TokenType::Operator || prevToken.type == TokenType::LParen;
            if (i == 0) {
                isUnary = true;
            }
            token.unary = isUnary;
        }

        switch (token.type) {
            case TokenType::Number:
            case TokenType::Identifier:
                output.push_back(token);
                prevToken = token;
                break;
            case TokenType::Function:
                pilaOperadores.apilar(token);
                prevToken = token;
                break;
            case TokenType::Operator: {
                while (!pilaOperadores.estaVacia()) {
                    const Token& top = pilaOperadores.cima();
                    if (top.type != TokenType::Operator) {
                        break;
                    }
                    int topPrec = precedencia(top);
                    int tokenPrec = precedencia(token);
                    bool rightAssoc = esAsociativoDerecha(token);
                    if ((rightAssoc && tokenPrec < topPrec) || (!rightAssoc && tokenPrec <= topPrec)) {
                        output.push_back(top);
                        pilaOperadores.desapilar();
                    } else {
                        break;
                    }
                }
                pilaOperadores.apilar(token);
                prevToken = token;
                break;
            }
            case TokenType::LParen:
                pilaOperadores.apilar(token);
                prevToken = token;
                break;
            case TokenType::RParen: {
                bool matched = false;
                while (!pilaOperadores.estaVacia()) {
                    Token top = pilaOperadores.desapilar();
                    if (top.type == TokenType::LParen) {
                        matched = true;
                        break;
                    }
                    output.push_back(top);
                }
                if (!matched) {
                    error = "Parentesis desbalanceados";
                    return {};
                }
                if (!pilaOperadores.estaVacia() && pilaOperadores.cima().type == TokenType::Function) {
                    output.push_back(pilaOperadores.desapilar());
                }
                prevToken = token;
                break;
            }
        }
    }

    while (!pilaOperadores.estaVacia()) {
        Token top = pilaOperadores.desapilar();
        if (top.type == TokenType::LParen || top.type == TokenType::RParen) {
            error = "Parentesis desbalanceados";
            return {};
        }
        output.push_back(top);
    }

    return output;
}

std::unique_ptr<Calculator::ExpressionNode> Calculator::construirArbol(const std::vector<Token>& posfix, std::string& error) const {
    Pila<std::unique_ptr<ExpressionNode>> pila;
    for (const Token& token : posfix) {
        if (token.type == TokenType::Number) {
            pila.apilar(std::unique_ptr<ExpressionNode>(new ExpressionNode(NodeKind::Number, token.text)));
        } else if (token.type == TokenType::Identifier) {
            pila.apilar(std::unique_ptr<ExpressionNode>(new ExpressionNode(NodeKind::Identifier, token.text)));
        } else if (token.type == TokenType::Function) {
            if (pila.estaVacia()) {
                error = "Funcion sin argumentos";
                return nullptr;
            }
            auto arg = pila.desapilar();
            std::unique_ptr<ExpressionNode> node(new ExpressionNode(NodeKind::Function, token.text, false));
            node->right = std::move(arg);
            pila.apilar(std::move(node));
        } else if (token.type == TokenType::Operator) {
            if (token.unary) {
                if (pila.estaVacia()) {
                    error = "Operacion unaria invalida";
                    return nullptr;
                }
                auto operand = pila.desapilar();
                std::unique_ptr<ExpressionNode> node(new ExpressionNode(NodeKind::Operator, token.text, true));
                node->right = std::move(operand);
                pila.apilar(std::move(node));
            } else {
                if (pila.tamano() < 2) {
                    error = "Operacion invalida";
                    return nullptr;
                }
                auto right = pila.desapilar();
                auto left = pila.desapilar();
                std::unique_ptr<ExpressionNode> node(new ExpressionNode(NodeKind::Operator, token.text, false));
                node->left = std::move(left);
                node->right = std::move(right);
                pila.apilar(std::move(node));
            }
        }
    }

    if (pila.tamano() != 1) {
        error = "Expresion invalida";
        return nullptr;
    }
    return pila.desapilar();
}

long long Calculator::evaluar(const ExpressionNode* node, std::string& error) const {
    if (!node) {
        error = "Expresion vacia";
        return 0;
    }
    switch (node->kind) {
        case NodeKind::Number:
            try {
                return std::stoll(node->value);
            } catch (const std::exception&) {
                error = "Numero fuera de rango";
                return 0;
            }
        case NodeKind::Identifier: {
            auto it = variables_.find(node->value);
            if (it == variables_.end()) {
                error = "Variable no definida: " + node->value;
                return 0;
            }
            return it->second;
        }
        case NodeKind::Function: {
            long long operand = evaluar(node->right.get(), error);
            if (!error.empty()) {
                return 0;
            }
            return aplicarFuncion(node, operand, error);
        }
        case NodeKind::Operator: {
            if (node->unary) {
                long long operand = evaluar(node->right.get(), error);
                if (!error.empty()) {
                    return 0;
                }
                return aplicarOperadorUnario(node, operand, error);
            }
            long long left = evaluar(node->left.get(), error);
            if (!error.empty()) {
                return 0;
            }
            long long right = evaluar(node->right.get(), error);
            if (!error.empty()) {
                return 0;
            }
            return aplicarOperador(node, left, right, error);
        }
    }
    error = "Tipo de nodo desconocido";
    return 0;
}

long long Calculator::aplicarOperador(const ExpressionNode* node, long long left, long long right, std::string& error) const {
    if (node->value == "+") {
        return left + right;
    }
    if (node->value == "-") {
        return left - right;
    }
    if (node->value == "*") {
        return left * right;
    }
    if (node->value == "/") {
        if (right == 0) {
            error = "Division por cero";
            return 0;
        }
        return left / right;
    }
    if (node->value == "%") {
        if (right == 0) {
            error = "Modulo por cero";
            return 0;
        }
        return left % right;
    }
    if (node->value == "^") {
        if (right < 0) {
            error = "Exponentes negativos no soportados";
            return 0;
        }
        return potenciaEntera(left, right);
    }
    error = "Operador desconocido: " + node->value;
    return 0;
}

long long Calculator::aplicarOperadorUnario(const ExpressionNode* node, long long operand, std::string& error) const {
    if (node->value == "+") {
        return operand;
    }
    if (node->value == "-") {
        return -operand;
    }
    error = "Operador unario desconocido: " + node->value;
    return 0;
}

long long Calculator::aplicarFuncion(const ExpressionNode* node, long long operand, std::string& error) const {
    if (node->value == "sqrt") {
        if (operand < 0) {
            error = "sqrt: argumento negativo";
            return 0;
        }
        double r = std::sqrt(static_cast<double>(operand));
        return static_cast<long long>(std::floor(r));
    }
    error = "Funcion desconocida: " + node->value;
    return 0;
}

long long Calculator::potenciaEntera(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1LL) {
            result *= base;
        }
        base *= base;
        exp >>= 1LL;
    }
    return result;
}

void Calculator::imprimirArbol(const ExpressionNode* node, const std::string& prefix, bool isRight, std::ostream& os) const {
    if (!node) {
        return;
    }
    if (node->right) {
        imprimirArbol(node->right.get(), prefix + (isRight ? "        " : "│       "), true, os);
    }
    os << prefix;
    if (!prefix.empty()) {
        os << (isRight ? "┌────" : "└────");
    }
    os << node->value;
    if (node->unary) {
        os << "(u)";
    }
    os << '\n';
    if (node->left) {
        imprimirArbol(node->left.get(), prefix + (isRight ? "│       " : "        "), false, os);
    }
}

void Calculator::aPrefijo(const ExpressionNode* node, std::vector<std::string>& output) const {
    if (!node) {
        return;
    }
    output.push_back(node->value);
    if (node->left) {
        aPrefijo(node->left.get(), output);
    }
    if (node->right) {
        aPrefijo(node->right.get(), output);
    }
}

void Calculator::aposfix(const ExpressionNode* node, std::vector<std::string>& output) const {
    if (!node) {
        return;
    }
    if (node->left) {
        aposfix(node->left.get(), output);
    }
    if (node->right) {
        aposfix(node->right.get(), output);
    }
    output.push_back(node->value);
}

std::string Calculator::generarSalidaConversion(const std::unique_ptr<ExpressionNode>& node, bool prefix) const {
    if (!node) {
        return "";
    }
    std::vector<std::string> tokens;
    if (prefix) {
        aPrefijo(node.get(), tokens);
    } else {
        aposfix(node.get(), tokens);
    }
    std::ostringstream oss;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i > 0) {
            oss << ' ';
        }
        oss << tokens[i];
    }
    return oss.str();
}

bool Calculator::manejarComandoMostrar(std::istringstream& iss, std::ostream& os) {
    std::string variable;
    if (!(iss >> variable)) {
        if (!lastExpression_) {
            os << "No hay expresion para mostrar" << std::endl;
            return true;
        }
        imprimirArbol(lastExpression_.get(), "", false, os);
        return true;
    }
    std::string extra;
    if (iss >> extra) {
        os << "Uso: show <variable>" << std::endl;
        return true;
    }
    auto it = variables_.find(variable);
    if (it == variables_.end()) {
        os << "Variable no definida: " << variable << std::endl;
    } else {
        os << variable << " = " << it->second << std::endl;
    }
    return true;
}

bool Calculator::manejarComandoPrefijoposfix(const std::string& command, std::istringstream& iss, std::ostream& os) {
    std::string expression;
    std::getline(iss, expression);
    expression = recortar(expression);

    if (expression.empty()) {
        if (!lastExpression_) {
            os << "No hay expresion cargada" << std::endl;
            return true;
        }
        os << generarSalidaConversion(lastExpression_, command == "prefix") << std::endl;
        return true;
    }

    std::string error;
    auto tokens = tokenizar(expression, error);
    if (!error.empty()) {
        os << error << std::endl;
        return true;
    }
    auto posfix = aposfix(tokens, error);
    if (!error.empty()) {
        os << error << std::endl;
        return true;
    }
    auto tree = construirArbol(posfix, error);
    if (!error.empty() || !tree) {
        if (error.empty()) {
            error = "Expresion invalida";
        }
        os << error << std::endl;
        return true;
    }
    os << generarSalidaConversion(tree, command == "prefix") << std::endl;
    return true;
}

bool Calculator::manejarExpresion(const std::string& expression, std::ostream& os) {
    size_t depth = 0;
    size_t assignIndex = std::string::npos;
    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];
        if (ch == '(') {
            ++depth;
        } else if (ch == ')') {
            if (depth == 0) {
                os << "Parentesis desbalanceados" << std::endl;
                return true;
            }
            --depth;
        } else if (ch == '=' && depth == 0) {
            if (assignIndex != std::string::npos) {
                os << "Solo se admite una asignacion por linea" << std::endl;
                return true;
            }
            assignIndex = i;
        }
    }
    if (depth != 0) {
        os << "Parentesis desbalanceados" << std::endl;
        return true;
    }

    std::string variable;
    std::string rhs = expression;
    if (assignIndex != std::string::npos) {
        variable = recortar(expression.substr(0, assignIndex));
        rhs = recortar(expression.substr(assignIndex + 1));
        if (!esIdentificador(variable)) {
            os << "Identificador invalido para asignacion" << std::endl;
            return true;
        }
        if (variable == "ans") {
            os << "'ans' es de solo lectura" << std::endl;
            return true;
        }
    }

    std::string error;
    auto tokens = tokenizar(rhs, error);
    if (!error.empty()) {
        os << error << std::endl;
        return true;
    }
    auto posfix = aposfix(tokens, error);
    if (!error.empty()) {
        os << error << std::endl;
        return true;
    }
    auto tree = construirArbol(posfix, error);
    if (!error.empty() || !tree) {
        if (error.empty()) {
            error = "Expresion invalida";
        }
        os << error << std::endl;
        return true;
    }

    std::string evalError;
    long long result = evaluar(tree.get(), evalError);
    if (!evalError.empty()) {
        os << evalError << std::endl;
        return true;
    }

    if (!variable.empty()) {
        variables_[variable] = result;
    }
    lastExpression_ = std::move(tree);
    if (!variable.empty()) {
        os << variable << " = " << result << std::endl;
    } else {
        variables_["ans"] = result;
        os << "ans = " << result << std::endl;
    }
    return true;
}

}
