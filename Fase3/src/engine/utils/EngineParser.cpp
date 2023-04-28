//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include <stdexcept>
#include <string>
#include "CommonParser.h"
#include "utils/EngineParser.h"
#include "transform/translate/Translate.h"
#include "Rotate.h"
#include "Scale.h"

namespace cg_engine {
    using cg_utils::CommonParser;
    using std::cerr;
    using std::domain_error;
    using cg_math::Vec3f;
    using std::string;

    cg_math::Vec3f EngineParser::ParseVec3f(tinyxml2::XMLElement *tag) {
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
            x = CommonParser::ParseFloat(tag->Attribute("x"));
            y = CommonParser::ParseFloat(tag->Attribute("y"));
            z = CommonParser::ParseFloat(tag->Attribute("z"));
        }
        catch (domain_error &e) {
            cerr << "Error: " << e.what() << " is not a valid float" << std::endl;
            return {};
        }

        return {x, y, z};
    }

    cg_math::Vec3f EngineParser::ParseProjection(tinyxml2::XMLElement *tag) {
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
            x = CommonParser::ParseFloat(tag->Attribute("fov"));
            y = CommonParser::ParseFloat(tag->Attribute("near"));
            z = CommonParser::ParseFloat(tag->Attribute("far"));
        }
        catch (domain_error &e) {
            cerr << "Error: " << e.what() << " is not a valid float" << std::endl;
            return {};
        }

        return {x, y, z};
    }

    Transform* EngineParser::ParseTransform(tinyxml2::XMLElement *tag) {
        if(tag) {
            string name = tag->Name();

            if(name == "translate") {

            }

            if(name == "rotate") {
                return new Rotate(CommonParser::ParseFloat(tag->Attribute("angle")),
                                  CommonParser::ParseFloat(tag->Attribute("x")),
                                  CommonParser::ParseFloat(tag->Attribute("y")),
                                  CommonParser::ParseFloat(tag->Attribute("z")));
            }

            if(name == "scale") {
                return new Scale(CommonParser::ParseFloat(tag->Attribute("factor")));
            }
        }
    }

    Transform *EngineParser::ParseTranslate(tinyxml2::XMLElement *tag) {
        if(tag->Attribute("time")) {

        }
        return new Translate(CommonParser::ParseFloat(tag->Attribute("x")),
                                    CommonParser::ParseFloat(tag->Attribute("y")),
                                    CommonParser::ParseFloat(tag->Attribute("z")));;
    }
} // cg_engine