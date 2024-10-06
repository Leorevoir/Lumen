/*
** EPITECH PROJECT, 2024
** Lumen
** File description:
** interpreter
*/

#include "interpreter.hpp"

Interpreter::Interpreter(const std::vector<Token>& tokens)
    : tokens(tokens), current_position(0) {}

int Interpreter::interpret()
{
    while (current_position < tokens.size()) {
        const Token &token = tokens[current_position];

        /*
         * add a switch case for each token type
         */
        switch (token.type) {
            case TokenType::IDENTIFIER:
                handle_identifier(token);
                break;
            default:
                break;
        }
        ++current_position;
    }
    return SUCCESS;
}
