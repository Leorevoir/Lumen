/*
** EPITECH PROJECT, 2024
** Lumen
** File description:
** arguments
*/

#include "base.hpp"
#include <string.h>

bool parse_flags(char *flag, bool *verbose)
{
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
        std::cout << "Usage: " << flag << " <file.lu>" << std::endl;
        return true;
    }
    if (strcmp(flag, "-v") == 0 || strcmp(flag, "--verbose") == 0) {
        *verbose = true;
        return true;
    }
    return false;
}

int parse_arguments(int argc, char **argv, bool *verbose)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file.lu>" << std::endl;
        return ERROR;
    }
    for (int i = 2; i < argc; ++i) {
        if (argv[i][0] == '-' && parse_flags(argv[i], verbose)) {
            continue;
        } else {
            return ERROR;
        }
    }
    return SUCCESS;
}

