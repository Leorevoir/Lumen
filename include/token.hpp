/*
** EPITECH PROJECT, 2024
** Lumen
** File description:
** token
*/

#ifndef TOKEN_HPP_
    #define TOKEN_HPP_
    #include "base.hpp"

constexpr char __comment[] = "//";

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    DELIMITER,
    COMMENT,
    WHITESPACE,
    METHOD,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    size_t position;
    size_t line_number;

    Token(TokenType t, const std::string &v, size_t pos, size_t line_num)
        : type(t), value(v), position(pos), line_number(line_num) {}
};

static const std::vector<std::string> __keywords = {
    "function", "end"
};

static const std::vector<std::string> __operators = {
    "==", "!=", ">=", "<=", "=", "+", "-", "*", "/", "%"
};

static const std::vector<char> __delimiters = {
    '(', ')', ':', ','
};

static const std::vector<std::string> __methods = {
    ".show", ".split", ".search", ".exists", ".count"
};

inline const std::string debug_type(TokenType type)
{
    switch (type) {
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::LITERAL:
            return "LITERAL";
        case TokenType::OPERATOR:
            return "OPERATOR";
        case TokenType::DELIMITER:
            return "DELIMITER";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::WHITESPACE:
            return "WHITESPACE";
        case TokenType::UNKNOWN:
            return "UNKNOWN";
        case TokenType::METHOD:
            return "METHOD";
        default:
            return "UNKNOWN";
    }
}

#endif /* !TOKEN_HPP_ */

