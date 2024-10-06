/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** syntax
*/

#include "syntax.hpp"

Syntax::Syntax(const std::vector<Token> &tokens, const std::vector<std::string> &lines)
    : tokens(tokens), lines(lines) {}

void Syntax::raise_error(size_t where, const std::string &error, const std::string &hint)
{
    std::cerr << "[\033[1;31mSYNTAX-ERROR\033[0m]\n"
              << "[\033[03;33mLine\033[0m]\t(" << where << ")\n\t"
              << lines[where] << "\n"
              << "[\033[03;33mRaise\033[0m]\n\t" << error << "\n"
              << "[\033[03;33mHint\033[0m]\n\t" << hint
              << std::endl;
}

int Syntax::check()
{
    for (size_t i = 0; i < tokens.size(); ++i) {

        switch (tokens[i].type) {
            case TokenType::METHOD:
                if (!is_valid_method(i)) {
                    return ERROR;
                }
                break;
            case TokenType::UNKNOWN:
                raise_error(tokens[i].line_number, UNKNOWN_TOKEN, HINT_DELIMITER);
            default:
                break;
        }

    }
    return SUCCESS;
}

bool Syntax::is_valid_method(size_t position)
{
    if (position + 1 >= tokens.size() && tokens[position].type != TokenType::DELIMITER) {
        return false;
    }
    if (tokens[position + 1].value != "(") {
        raise_error(tokens[position].line_number, INVALID_METHOD_CALL, HINT_PARENTHESIS);
        return false;
    }
    if (tokens[position + 2].type != TokenType::DELIMITER) {
        if (tokens[position + 2].type == TokenType::LITERAL
            && tokens[position + 3].type == TokenType::DELIMITER) {
            return true;
        }
        raise_error(tokens[position].line_number, INVALID_METHOD_CALL, HINT_QUOTES);
        return false;
    }
    return true;
}
