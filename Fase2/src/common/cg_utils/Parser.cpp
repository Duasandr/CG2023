//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include <stdexcept>
#include "Parser.h"

namespace cg_utils {
    using std::cerr;
    using std::domain_error;

    /**
     * Parses a string into an integer.
     * @param str
     * @return
     * @throws std::domain_error when string is not a valid integer
     */
    int Parser::ParseInt(const char *str) {
        int res = 0;
        char *rest;

        res = static_cast<int>(strtol(str, &rest, 10));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }

    /**
     * Parses a string into a float.
     * @param str
     * @return
     * @throws std::domain_error when string is not a valid float
     */
    float Parser::ParseFloat(const char *str) {
        float res = 0.0f;
        char *rest;

        res = static_cast<float>(strtof(str, &rest));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }
} // cg_engine