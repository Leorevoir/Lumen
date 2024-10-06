/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** method
*/

#include "interpreter.hpp"

std::vector<size_t> search_in_string(const std::string &str, char c)
{
    std::vector<size_t> occurrences;

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == c) {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}

void Interpreter::handle_method(const std::string &var_name, const std::string &method)
{
    /*
     * show() method simply prints the current value of the variable
     */
    if (method == ".show") {
        const std::string value = symbol_table[var_name];

        if (value.empty()) {
            std::cout << "undefined" << std::endl;
            return;
        }
        std::cout << static_cast<std::string>(value) << std::endl;
    }

    /*
     * search() method returns the index of every occurrence of the given character in the variable
     */
    if (method == ".search") {
        const std::string value = symbol_table[var_name];
        const char c = tokens[current_position + 2].value[0];
        const std::vector<size_t> occurrences = search_in_string(value, c);
        std::string result = "{";

        for (size_t i = 0; i < occurrences.size(); ++i) {
            result.append(std::to_string(occurrences[i]));
            if (i < occurrences.size() - 1) {
                result.append(", ");
            }
        }
        result.append("}");
        assign_if_valid(result);
    }

    /*
     * exists() method returns true if the variable is not empty else false
     */
    if (method == ".exists") {
        const std::string result = symbol_table[var_name].empty() ? "false" : "true";

        assign_if_valid(result);
    }

    /*
     * count() method returns the number of characters in the given variable
     */
    if (method == ".count") {
        const std::string result = std::to_string(symbol_table[var_name].length());

        assign_if_valid(result);
    }
}
