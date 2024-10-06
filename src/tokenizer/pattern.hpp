/*
** EPITECH PROJECT, 2024
** lumen
** File description:
** pattern
*/

#include "base.hpp"

#ifndef PATTERN_HPP_
    #define PATTERN_HPP_

class PatternMatcher {
public:
    PatternMatcher(const std::string &line);
    
    bool match(const std::string &pattern);
    bool match(const char pattern);
    void skip_whitespace();
    bool is_end() const;
    size_t get_position() const;
    size_t get_last_match_length() const;
    std::string current_substring(size_t length) const;
    void set_position(std::string::const_iterator new_pos);

private:
    const std::string &line;
    std::string::const_iterator pos;
    size_t last_match_length;
};

#endif /* !PATTERN_HPP_ */
