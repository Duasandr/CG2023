//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include <stdexcept>
#include "CommonParser.h"

namespace cg_utils {
    using std::cerr;
    using std::domain_error;

    int CommonParser::ParseInt(const char *str) {
        int res;
        char *rest;

        res = static_cast<int>(strtol(str, &rest, 10));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }

    float CommonParser::ParseFloat(const char *str) {
        float res;
        char *rest;

        res = static_cast<float>(strtof(str, &rest));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }

    bool CommonParser::ParseBool(const char *str) {
        if(strcmp(str, "True") == 0) {
            return true;
        }
        else if(strcmp(str, "False") == 0) {
            return false;
        }
        else {
            throw domain_error(str);
        }
    }
} // cg_engine