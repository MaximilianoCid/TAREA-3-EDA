#ifndef EDACAL_CALCULATOR_HPP
#define EDACAL_CALCULATOR_HPP

#include <iosfwd>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace edacal {

class Calculator {
public:
    Calculator();
    bool processLine(const std::string& line, std::ostream& os);
    void repl(std::istream& is, std::ostream& os);

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

    static std::string trim(const std::string& text);
    static bool isIdentifier(const std::string& text);
    std::vector<Token> tokenize(const std::string& expression, std::string& error) const;
    std::vector<Token> toPostfix(const std::vector<Token>& tokens, std::string& error) const;
    std::unique_ptr<ExpressionNode> buildTree(const std::vector<Token>& postfix, std::string& error) const;
    long long evaluate(const ExpressionNode* node, std::string& error) const;
    long long applyOperator(const ExpressionNode* node, long long left, long long right, std::string& error) const;
    long long applyUnaryOperator(const ExpressionNode* node, long long operand, std::string& error) const;
    static long long ipow(long long base, long long exp);
    static bool isRightAssociative(const Token& token);
    static int precedence(const Token& token);
    void printTree(const ExpressionNode* node, const std::string& prefix, bool isRight, std::ostream& os) const;
    void toPrefix(const ExpressionNode* node, std::vector<std::string>& output) const;
    void toPostfix(const ExpressionNode* node, std::vector<std::string>& output) const;
    std::string makeConversionOutput(const std::unique_ptr<ExpressionNode>& node, bool prefix) const;
    bool handleShowCommand(std::istringstream& iss, std::ostream& os);
    bool handlePrefixPostfixCommand(const std::string& command, std::istringstream& iss, std::ostream& os);
    bool handleExpression(const std::string& expression, std::ostream& os);
};

} // namespace edacal

#endif // EDACAL_CALCULATOR_HPP
