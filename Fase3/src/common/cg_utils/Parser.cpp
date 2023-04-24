//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include <stdexcept>
#include "Parser.h"

namespace cg_utils {
    using std::cerr;
    using std::domain_error;
    using cg_math::Vec3f;

    int Parser::ParseInt(const char *str) {
        int res;
        char *rest;

        res = static_cast<int>(strtol(str, &rest, 10));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }

    float Parser::ParseFloat(const char *str) {
        float res;
        char *rest;

        res = static_cast<float>(strtof(str, &rest));

        if(*rest != '\0') {
            throw domain_error(str);
        }

        return res;
    }

    cg_math::Vec3f Parser::ParseVec3f(tinyxml2::XMLElement *tag) {
        if (tag == nullptr) {
            cerr << "Error: tag is null" << std::endl;
            return {};
        }

        float x;
        float y;
        float z;

        if (tag->FindAttribute("x") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute x" << std::endl;
            return {};
        }

        if (tag->FindAttribute("y") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute y" << std::endl;
            return {};
        }

        if (tag->FindAttribute("z") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute z" << std::endl;
            return {};
        }

        try {
            x = Parser::ParseFloat(tag->Attribute("x"));
            y = Parser::ParseFloat(tag->Attribute("y"));
            z = Parser::ParseFloat(tag->Attribute("z"));
        }
        catch (domain_error &e) {
            cerr << "Error: " << e.what() << " is not a valid float" << std::endl;
            return {};
        }

        return {x, y, z};
    }

    cg_math::Vec3f Parser::ParseProjection(tinyxml2::XMLElement *tag) {
        if (tag == nullptr) {
            cerr << "Error: tag is null" << std::endl;
            return {};
        }

        if (tag->FindAttribute("fov") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute fov" << std::endl;
            return {};
        }

        if (tag->FindAttribute("near") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute near" << std::endl;
            return {};
        }

        if (tag->FindAttribute("far") == nullptr) {
            cerr << "Error: tag " << tag->Name() << " has no attribute far" << std::endl;
            return {};
        }

        float x;
        float y;
        float z;

        try {
            x = Parser::ParseFloat(tag->Attribute("fov"));
            y = Parser::ParseFloat(tag->Attribute("near"));
            z = Parser::ParseFloat(tag->Attribute("far"));
        }
        catch (domain_error &e) {
            cerr << "Error: " << e.what() << " is not a valid float" << std::endl;
            return {};
        }

        return {x, y, z};
    }
} // cg_engine