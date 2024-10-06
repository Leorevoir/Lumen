/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** identifier
*/

#include "interpreter.hpp"

void Interpreter::assign_if_valid(const std::string &to_assign)
{
    if (tokens[current_position - 2].type == TokenType::OPERATOR
        && tokens[current_position - 3].type == TokenType::IDENTIFIER) {
        identifier_return_assignment(tokens[current_position - 3], to_assign);
    }
}

void Interpreter::identifier_assignment(const Token &token)
{
    if (tokens[current_position].value != "=") {
        return;
    }
    if (tokens[current_position + 1].type != TokenType::LITERAL) {
        return;
    }
    symbol_table[token.value] = tokens[current_position + 1].value;
    ++current_position;
    return;
}

void Interpreter::identifier_return_assignment(const Token &token, const std::string &to_assign = "")
{
    if (!to_assign.empty()) {
        symbol_table[token.value] = to_assign;
        ++current_position;
        return;
    }
    if (tokens[current_position].value != "=") {
        return;
    }
    if (tokens[current_position + 1].type != TokenType::IDENTIFIER) {
        return;
    }
    if (tokens[current_position + 2].type == TokenType::METHOD) {
        return;
    }
    symbol_table[token.value] = symbol_table[tokens[current_position + 1].value];
    ++current_position;
}

void Interpreter::handle_identifier(const Token &token)
{
    std::string var_name = token.value;

    ++current_position;
    /*
     * if the next token is an operator, then it's (maybe) a variable assignment
     */
    if (tokens[current_position].type == TokenType::OPERATOR) {
        identifier_assignment(token);
        identifier_return_assignment(token);
    }
    if (tokens[current_position].type == TokenType::METHOD) {
        handle_method(var_name, tokens[current_position].value);
        ++current_position;
    }
}
