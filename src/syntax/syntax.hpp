/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** syntax
*/

#ifndef SYNTAX_HPP_
    #define SYNTAX_HPP_

    #include "token.hpp"

    /*
     * constants expressions for syntax error messages
     */
    constexpr char INVALID_METHOD_CALL[] = "Invalid method call.";
    constexpr char UNKNOWN_TOKEN[] = "Unknown token.";

    /*
     * constants expressions for syntax hint
     */
    constexpr char HINT_PARENTHESIS[] = "Did you forget to add parenthesis?";
    constexpr char HINT_QUOTES[] = "Did you forget to add quotes?";
    constexpr char HINT_DELIMITER[] = "Did you forget to add a delimiter?";


class Syntax {
public:
    Syntax(const std::vector<Token> &tokens, const std::vector<std::string> &lines);
    bool is_valid_method(size_t position);
    int check();

private:
    const std::vector<Token> &tokens;
    const std::vector<std::string> lines;
    void raise_error(size_t where, const std::string &error, const std::string &hint);
};

#endif /* !SYNTAX_HPP_ */
