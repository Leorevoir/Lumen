/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** pattern
*/

#include "pattern.hpp"

PatternMatcher::PatternMatcher(const std::string &line)
    : line(line), pos(line.begin()), last_match_length(0) {}

/* multiple pattern matching -> string */
bool PatternMatcher::match(const std::string &pattern)
{
    if (std::distance(pos, line.end()) >= static_cast<std::ptrdiff_t>(pattern.length())
        && std::string(pos, pos + pattern.length()) == pattern) {
        pos += pattern.length();
        last_match_length = pattern.length();
        return true;
    }
    return false;
}

/* single pattern matching -> char */
bool PatternMatcher::match(const char pattern)
{
    if (pos != line.end() && *pos == pattern) {
        ++pos;
        last_match_length = 1;
        return true;
    }
    return false;
}

void PatternMatcher::skip_whitespace()
{
    while (pos != line.end() && std::isspace(static_cast<unsigned char>(*pos))) {
        ++pos;
    }
    last_match_length = 0;
}

bool PatternMatcher::is_end() const
{
    return pos == line.end();
}

size_t PatternMatcher::get_position() const
{
    return std::distance(line.begin(), pos);
}

size_t PatternMatcher::get_last_match_length() const
{
    return last_match_length;
}

std::string PatternMatcher::current_substring(size_t length) const
{
    return std::string(pos, std::min(pos + length, line.end()));
}

void PatternMatcher::set_position(std::string::const_iterator new_pos)
{
    pos = new_pos;
}
