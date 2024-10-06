/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** tokenizer
*/

#include "token.hpp"
#include "pattern.hpp"

#ifndef TOKENIZER_HPP_
    #define TOKENIZER_HPP_

class Tokenizer {
public:
    Tokenizer(const std::vector<std::string> &lines);
    void tokenize();
    void debug_token();
    const std::vector<Token>& get_tokens() const;

private:
    std::vector<std::string> lines;
    std::vector<Token> tokens;

    void process_line(const std::string &line, size_t line_number);
    bool is_method(PatternMatcher &matcher, size_t line_number);
    bool is_keyword(PatternMatcher &matcher, size_t line_number);
    bool is_operator(PatternMatcher &matcher, size_t line_number);
    bool is_delimiter(PatternMatcher &matcher, size_t line_number);
    bool is_identifier(PatternMatcher &matcher, const std::string &line, size_t line_number);
    void handle_literal(PatternMatcher &matcher, const std::string &line, size_t line_number);
    void add_token(TokenType type, const std::string &value, size_t position, size_t line_position);
};

#endif /* !TOKENIZER_HPP_ */
