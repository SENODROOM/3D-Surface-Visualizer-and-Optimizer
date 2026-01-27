#ifndef EQUATION_PARSER_H
#define EQUATION_PARSER_H

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <cmath>
#include <sstream>
#include <stdexcept>

class EquationParser
{
private:
    std::string equation;
    std::map<std::string, double> variables;

    // Token types for parsing
    enum TokenType
    {
        NUMBER,
        VARIABLE,
        OPERATOR,
        FUNCTION,
        LPAREN,
        RPAREN,
        END
    };

    struct Token
    {
        TokenType type;
        std::string value;
        double numValue;
    };

    std::vector<Token> tokens;
    size_t currentToken;

    // Supported functions
    std::map<std::string, std::function<double(double)>> functions;
    std::map<std::string, std::function<double(double, double)>> binaryFunctions;

    // Parsing methods
    void tokenize();
    double parseExpression();
    double parseTerm();
    double parseFactor();
    double parsePower();
    double parseUnary();
    double parsePrimary();

    bool isOperator(char c) const;
    bool isFunction(const std::string &str) const;
    int getPrecedence(char op) const;

    // Static helper for equation normalization
    static bool isKnownFunctionName(const std::string &name);

public:
    EquationParser();
    EquationParser(const std::string &eq);

    void setEquation(const std::string &eq);
    std::string getEquation() const { return equation; }

    // Set variable values
    void setVariable(const std::string &name, double value);

    // Evaluate the equation with current variable values
    double evaluate();

    // Evaluate with specific variable values
    double evaluate(const std::map<std::string, double> &vars);

    // Quick evaluation for x, y, z
    double evaluate(double x, double y, double z = 0);

    // Validate equation syntax
    bool validate(std::string &errorMessage);

    // Get list of variables used in equation
    std::vector<std::string> getVariables() const;

    // Normalize equation (convert common formats)
    static std::string normalizeEquation(const std::string &eq);
};

#endif