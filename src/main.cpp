/*
** EPITECH PROJECT, 2024
** Lumen
** File description:
** main
*/

#include "tokenizer/tokenizer.hpp"
#include "interpreter/interpreter.hpp"
#include "syntax/syntax.hpp"

int parse_arguments(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file.lu>" << std::endl;
        return ERROR;
    }
    return SUCCESS;
}

int read_file(const std::string &filename, std::vector <std::string> &lines)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return ERROR;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return SUCCESS;
}

static const std::vector<Token> start_tokenizer(const std::vector<std::string> &lines)
{
    Tokenizer tokenizer(lines);

    tokenizer.tokenize();
    tokenizer.debug_token();
    return tokenizer.get_tokens();
}

static int start_interpreter(const std::vector<Token> &tokens)
{
    Interpreter interpreter(tokens);

    return interpreter.interpret();
}

static int start_syntax_checker(const std::vector<Token> &tokens, const std::vector<std::string> &lines)
{
    Syntax syntax(tokens, lines);

    return syntax.check();
}

int main(int argc, char **argv)
{
    int result = SUCCESS;
    std::vector <std::string> lines;

    if (parse_arguments(argc, argv) != SUCCESS) {
        return ERROR;
    }
    if (read_file(argv[1], lines) != SUCCESS) {
        return ERROR;
    }
    const auto &tokens = start_tokenizer(lines);
    result = start_syntax_checker(tokens, lines);
    if (result != SUCCESS) {
        return ERROR;
    }
    result = start_interpreter(tokens);
    return result;
}
