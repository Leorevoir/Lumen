/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** tokenizer
*/

#include "tokenizer.hpp"

Tokenizer::Tokenizer(const std::vector<std::string> &lines)
    : lines(lines) {}

/* for each line in lines vector tokenize it */
void Tokenizer::tokenize()
{
    size_t line_number = 0;

    for (auto &line: lines) {
        process_line(line, line_number);
        line_number++;
    }
}

/* look for tokens in a line, skip spaces and comments */
void Tokenizer::process_line(const std::string &line, size_t line_number)
{
    PatternMatcher matcher(line);

    while (!matcher.is_end()) {
        matcher.skip_whitespace();

        if (matcher.match(__comment))
            break;
        if (is_method(matcher, line_number)) {
            continue;
        }
        if (matcher.match('"') || matcher.match('\'')) {
            handle_literal(matcher, line, line_number);
            continue;
        }
        if (is_keyword(matcher, line_number) || is_operator(matcher, line_number))
            continue;
        if (is_delimiter(matcher, line_number))
            continue;
        if (is_identifier(matcher, line, line_number))
            continue;
        add_token(TokenType::UNKNOWN, matcher.current_substring(1), matcher.get_position(), line_number);
        matcher.match(*matcher.current_substring(1).begin());
    }
}

/* look for methods */
bool Tokenizer::is_method(PatternMatcher &matcher, size_t line_number)
{
    if (!matcher.match('.')) {
        return false;
    }
    for (const auto &method : __methods) {
        if (matcher.match(method.substr(1))) {
            add_token(TokenType::METHOD, method, matcher.get_position() - method.length(), line_number);
            return true;
        }
    }
    return false;
}

/* look for keywords */
bool Tokenizer::is_keyword(PatternMatcher &matcher, size_t line_number)
{
    for (const auto &keyword : __keywords) {
        if (matcher.match(keyword)) {
            add_token(TokenType::KEYWORD, keyword, matcher.get_position() - keyword.length(), line_number);
            return true;
        }
    }
    return false;
}

/* look for operators */
bool Tokenizer::is_operator(PatternMatcher &matcher, size_t line_number)
{
    for (const auto &op : __operators) {
        if (matcher.match(op)) {
            add_token(TokenType::OPERATOR, op, matcher.get_position() - op.length(), line_number);
            return true;
        }
    }
    return false;
}

/* look for delimiters */
bool Tokenizer::is_delimiter(PatternMatcher &matcher, size_t line_number)
{
    for (const auto &delim : __delimiters) {
        if (matcher.match(delim)) {
            add_token(TokenType::DELIMITER, std::string(1, delim), matcher.get_position() - 1, line_number);
            return true;
        }
    }
    return false;
}


/* look for literals */
void Tokenizer::handle_literal(PatternMatcher &matcher, const std::string &line, size_t line_number)
{
    char quote = line[matcher.get_position() - 1];
    size_t start_pos = matcher.get_position() - 1;
    auto end_it = std::find(line.begin() + start_pos + 1, line.end(), quote);
    size_t literal_length = 0;
    size_t literal_start = 0;

    if (end_it != line.end()) {
        literal_start = start_pos + 1;
        literal_length = std::distance(line.begin() + literal_start, end_it);
        std::string literal_value = line.substr(literal_start, literal_length);
        add_token(TokenType::LITERAL, literal_value, start_pos, line_number);
        matcher.set_position(end_it + 1);
    } else {
        add_token(TokenType::UNKNOWN, line.substr(start_pos), start_pos, line_number);
    }
}

/* look for identifier */
bool Tokenizer::is_identifier(PatternMatcher &matcher, const std::string &line, size_t line_number)
{
    size_t start_pos = 0;

    if (std::isalpha(static_cast<unsigned char>(*matcher.current_substring(1).begin()))
        || *matcher.current_substring(1).begin() == '_') {
        start_pos = matcher.get_position();
        while (!matcher.is_end()
            && (std::isalnum(static_cast<unsigned char>(*matcher.current_substring(1).begin()))
            || *matcher.current_substring(1).begin() == '_')) {
            matcher.match(*matcher.current_substring(1).begin());
        }
        std::string identifier = line.substr(start_pos, matcher.get_position() - start_pos);
        add_token(TokenType::IDENTIFIER, identifier, start_pos, line_number);
        return true;
    }
    return false;
}

void Tokenizer::add_token(TokenType type, const std::string &value, size_t position, size_t line_number)
{
    tokens.emplace_back(type, value, position, line_number);
}

const std::vector<Token>& Tokenizer::get_tokens() const
{
    return tokens;
}

/*
 * facultative debug function
 */
void Tokenizer::debug_token()
{
    const int type_width = 15;
    const int value_width = 30;
    const int position_width = 10;

    std::cout << "_______________________________________________________" << std::endl;
    std::cout << "Token Debug Info:\n" << std::endl;
    std::cout << std::setw(type_width) << "Type"
              << std::setw(value_width) << "Value"
              << std::setw(position_width) << "Position"
              << std::endl;
    std::cout << "_______________________________________________________" << std::endl;
    for (const auto &token: tokens) {
        std::cout << std::setw(type_width) << debug_type(token.type)
                  << std::setw(value_width) << token.value
                  << std::setw(position_width) << token.position
                  << std::endl;
    }
    std::cout << "_______________________________________________________" << std::endl;
}
