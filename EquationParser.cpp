#include "EquationParser.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <set>

EquationParser::EquationParser()
{
    // Initialize supported mathematical functions
    functions["sin"] = [](double x)
    { return std::sin(x); };
    functions["cos"] = [](double x)
    { return std::cos(x); };
    functions["tan"] = [](double x)
    { return std::tan(x); };
    functions["exp"] = [](double x)
    { return std::exp(x); };
    functions["log"] = [](double x)
    { return std::log(x); };
    functions["ln"] = [](double x)
    { return std::log(x); };
    functions["log10"] = [](double x)
    { return std::log10(x); };
    functions["sqrt"] = [](double x)
    { return std::sqrt(x); };
    functions["abs"] = [](double x)
    { return std::abs(x); };
    functions["floor"] = [](double x)
    { return std::floor(x); };
    functions["ceil"] = [](double x)
    { return std::ceil(x); };

    binaryFunctions["pow"] = [](double x, double y)
    { return std::pow(x, y); };
    binaryFunctions["min"] = [](double x, double y)
    { return std::min(x, y); };
    binaryFunctions["max"] = [](double x, double y)
    { return std::max(x, y); };
}

EquationParser::EquationParser(const std::string &eq) : EquationParser()
{
    setEquation(eq);
}

void EquationParser::setEquation(const std::string &eq)
{
    equation = normalizeEquation(eq);
}

void EquationParser::setVariable(const std::string &name, double value)
{
    variables[name] = value;
}

std::string EquationParser::normalizeEquation(const std::string &eq)
{
    std::string normalized = eq;

    // Remove spaces
    normalized.erase(std::remove(normalized.begin(), normalized.end(), ' '), normalized.end());

    // Replace common notations
    size_t pos = 0;
    while ((pos = normalized.find("**", pos)) != std::string::npos)
    {
        normalized.replace(pos, 2, "^");
    }

    // Convert e notation (2.5e-3) - leave it as is, will be handled by stod
    // Convert implicit multiplication: 2x -> 2*x, 2(x) -> 2*(x), (x)(y) -> (x)*(y)
    std::string result;
    for (size_t i = 0; i < normalized.length(); i++)
    {
        result += normalized[i];

        if (i < normalized.length() - 1)
        {
            char current = normalized[i];
            char next = normalized[i + 1];

            // Add * between: number and letter, number and (, ) and number, ) and letter, ) and (
            bool needsMult = false;

            if (std::isdigit(current) && std::isalpha(next))
                needsMult = true;
            else if (std::isdigit(current) && next == '(')
                needsMult = true;
            else if (current == ')' && std::isdigit(next))
                needsMult = true;
            else if (current == ')' && std::isalpha(next))
                needsMult = true;
            else if (current == ')' && next == '(')
                needsMult = true;
            else if (std::isalpha(current) && next == '(')
            {
                // Check if it's a function name by looking backwards from current position
                std::string funcName;
                int j = i;
                // Go back to find start of the word
                while (j >= 0 && std::isalpha(normalized[j]))
                {
                    j--;
                }
                j++; // Move forward to first letter

                // Extract the function name
                for (int k = j; k <= (int)i; k++)
                {
                    funcName += normalized[k];
                }

                // Check if it's a known function using static helper
                if (!isKnownFunctionName(funcName))
                {
                    needsMult = true;
                }
            }

            if (needsMult)
            {
                result += '*';
            }
        }
    }

    return result;
}

void EquationParser::tokenize()
{
    tokens.clear();
    size_t i = 0;

    while (i < equation.length())
    {
        char c = equation[i];

        // Skip whitespace
        if (std::isspace(c))
        {
            i++;
            continue;
        }

        // Numbers (including decimals and scientific notation)
        if (std::isdigit(c) || c == '.')
        {
            std::string numStr;
            while (i < equation.length() &&
                   (std::isdigit(equation[i]) || equation[i] == '.' ||
                    equation[i] == 'e' || equation[i] == 'E' ||
                    (equation[i] == '-' && (i > 0 && (equation[i - 1] == 'e' || equation[i - 1] == 'E')))))
            {
                numStr += equation[i++];
            }

            Token token;
            token.type = NUMBER;
            token.value = numStr;
            token.numValue = std::stod(numStr);
            tokens.push_back(token);
            continue;
        }

        // Variables and functions
        if (std::isalpha(c))
        {
            std::string name;
            while (i < equation.length() && (std::isalnum(equation[i]) || equation[i] == '_'))
            {
                name += equation[i++];
            }

            Token token;
            if (isFunction(name))
            {
                token.type = FUNCTION;
            }
            else
            {
                token.type = VARIABLE;
            }
            token.value = name;
            tokens.push_back(token);
            continue;
        }

        // Operators
        if (isOperator(c))
        {
            Token token;
            token.type = OPERATOR;
            token.value = c;
            tokens.push_back(token);
            i++;
            continue;
        }

        // Parentheses
        if (c == '(')
        {
            Token token;
            token.type = LPAREN;
            token.value = "(";
            tokens.push_back(token);
            i++;
            continue;
        }

        if (c == ')')
        {
            Token token;
            token.type = RPAREN;
            token.value = ")";
            tokens.push_back(token);
            i++;
            continue;
        }

        // Unknown character
        throw std::runtime_error(std::string("Unknown character: ") + c);
    }

    // Add END token
    Token endToken;
    endToken.type = END;
    tokens.push_back(endToken);
}

bool EquationParser::isOperator(char c) const
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

bool EquationParser::isFunction(const std::string &str) const
{
    return functions.find(str) != functions.end() ||
           binaryFunctions.find(str) != binaryFunctions.end();
}

bool EquationParser::isKnownFunctionName(const std::string &name)
{
    // Static list of all supported functions
    static const std::set<std::string> knownFunctions = {
        "sin", "cos", "tan", "exp", "log", "ln", "log10",
        "sqrt", "abs", "floor", "ceil", "pow", "min", "max"};

    return knownFunctions.find(name) != knownFunctions.end();
}

int EquationParser::getPrecedence(char op) const
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

double EquationParser::evaluate()
{
    tokenize();
    currentToken = 0;
    return parseExpression();
}

double EquationParser::evaluate(const std::map<std::string, double> &vars)
{
    variables = vars;
    return evaluate();
}

double EquationParser::evaluate(double x, double y, double z)
{
    variables["x"] = x;
    variables["y"] = y;
    variables["z"] = z;
    return evaluate();
}

double EquationParser::parseExpression()
{
    double result = parseTerm();

    while (currentToken < tokens.size() &&
           tokens[currentToken].type == OPERATOR &&
           (tokens[currentToken].value == "+" || tokens[currentToken].value == "-"))
    {
        std::string op = tokens[currentToken].value;
        currentToken++;
        double right = parseTerm();

        if (op == "+")
            result += right;
        else
            result -= right;
    }

    return result;
}

double EquationParser::parseTerm()
{
    double result = parsePower();

    while (currentToken < tokens.size() &&
           tokens[currentToken].type == OPERATOR &&
           (tokens[currentToken].value == "*" || tokens[currentToken].value == "/" || tokens[currentToken].value == "%"))
    {
        std::string op = tokens[currentToken].value;
        currentToken++;
        double right = parsePower();

        if (op == "*")
            result *= right;
        else if (op == "/")
        {
            if (right == 0)
                throw std::runtime_error("Division by zero");
            result /= right;
        }
        else
        { // %
            result = std::fmod(result, right);
        }
    }

    return result;
}

double EquationParser::parsePower()
{
    double result = parseUnary();

    if (currentToken < tokens.size() &&
        tokens[currentToken].type == OPERATOR &&
        tokens[currentToken].value == "^")
    {
        currentToken++;
        double exponent = parsePower(); // Right associative
        result = std::pow(result, exponent);
    }

    return result;
}

double EquationParser::parseUnary()
{
    if (currentToken < tokens.size() &&
        tokens[currentToken].type == OPERATOR &&
        (tokens[currentToken].value == "+" || tokens[currentToken].value == "-"))
    {
        std::string op = tokens[currentToken].value;
        currentToken++;
        double value = parseUnary();
        return (op == "-") ? -value : value;
    }

    return parsePrimary();
}

double EquationParser::parsePrimary()
{
    if (currentToken >= tokens.size())
        throw std::runtime_error("Unexpected end of expression");

    Token token = tokens[currentToken];

    // Number
    if (token.type == NUMBER)
    {
        currentToken++;
        return token.numValue;
    }

    // Variable
    if (token.type == VARIABLE)
    {
        currentToken++;
        if (variables.find(token.value) == variables.end())
        {
            throw std::runtime_error("Undefined variable: " + token.value);
        }
        return variables[token.value];
    }

    // Function
    if (token.type == FUNCTION)
    {
        std::string funcName = token.value;
        currentToken++;

        if (currentToken >= tokens.size() || tokens[currentToken].type != LPAREN)
            throw std::runtime_error("Expected '(' after function name");

        currentToken++; // Skip '('

        // Check if it's a binary function
        if (binaryFunctions.find(funcName) != binaryFunctions.end())
        {
            double arg1 = parseExpression();

            if (currentToken >= tokens.size() || tokens[currentToken].value != ",")
                throw std::runtime_error("Expected ',' in binary function");

            currentToken++; // Skip ','
            double arg2 = parseExpression();

            if (currentToken >= tokens.size() || tokens[currentToken].type != RPAREN)
                throw std::runtime_error("Expected ')' after function arguments");

            currentToken++; // Skip ')'

            return binaryFunctions[funcName](arg1, arg2);
        }
        else
        {
            double arg = parseExpression();

            if (currentToken >= tokens.size() || tokens[currentToken].type != RPAREN)
                throw std::runtime_error("Expected ')' after function argument");

            currentToken++; // Skip ')'

            if (functions.find(funcName) == functions.end())
                throw std::runtime_error("Unknown function: " + funcName);

            return functions[funcName](arg);
        }
    }

    // Parenthesized expression
    if (token.type == LPAREN)
    {
        currentToken++; // Skip '('
        double result = parseExpression();

        if (currentToken >= tokens.size() || tokens[currentToken].type != RPAREN)
            throw std::runtime_error("Expected ')'");

        currentToken++; // Skip ')'
        return result;
    }

    throw std::runtime_error("Unexpected token: " + token.value);
}

bool EquationParser::validate(std::string &errorMessage)
{
    try
    {
        // Try to tokenize
        tokenize();

        // Check for balanced parentheses
        int parenCount = 0;
        for (const auto &token : tokens)
        {
            if (token.type == LPAREN)
                parenCount++;
            if (token.type == RPAREN)
                parenCount--;
            if (parenCount < 0)
            {
                errorMessage = "Unbalanced parentheses";
                return false;
            }
        }

        if (parenCount != 0)
        {
            errorMessage = "Unbalanced parentheses";
            return false;
        }

        // Try to evaluate with dummy variables
        std::map<std::string, double> dummyVars;
        for (const auto &token : tokens)
        {
            if (token.type == VARIABLE)
            {
                dummyVars[token.value] = 1.0;
            }
        }

        evaluate(dummyVars);
        errorMessage = "";
        return true;
    }
    catch (const std::exception &e)
    {
        errorMessage = e.what();
        return false;
    }
}

std::vector<std::string> EquationParser::getVariables() const
{
    std::vector<std::string> vars;
    size_t i = 0;

    while (i < equation.length())
    {
        if (std::isalpha(equation[i]))
        {
            std::string name;
            while (i < equation.length() && (std::isalnum(equation[i]) || equation[i] == '_'))
            {
                name += equation[i++];
            }

            // Skip if it's a function
            if (!isFunction(name))
            {
                // Add only if not already in list
                if (std::find(vars.begin(), vars.end(), name) == vars.end())
                {
                    vars.push_back(name);
                }
            }
        }
        else
        {
            i++;
        }
    }

    return vars;
}