/*
** EPITECH PROJECT, 2024
** Lumen
** File description:
** interpreter
*/

#ifndef INTERPRETER_HPP_
    #define INTERPRETER_HPP_

#include "token.hpp"
#include <unordered_map>
#include <string>
#include <vector>


class Interpreter {
public:
    Interpreter(const std::vector<Token> &tokens);
    int interpret();
    void assign_if_valid(const std::string &to_assign = "");

private:
    const std::vector<Token> &tokens;
    size_t current_position;
    std::unordered_map<std::string, std::string> symbol_table;

    void handle_identifier(const Token &token);
    void handle_method(const std::string &var_name, const std::string &method);

    void identifier_assignment(const Token &token);
    void identifier_return_assignment(const Token &token, const std::string &to_assign);
};

#endif /* !INTERPRETER_HPP_ */
