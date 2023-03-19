//
// Created by Sandro Duarte on 19/03/2023.
//

#include "transform/Transform.h"
#include "transform/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "Parser.h"
#include <string>

namespace cg_engine {
    using std::string;
    using tinyxml2::XMLElement;

    Transform *Transform::Create(tinyxml2::XMLElement *tag) {

        if(tag) {
            string name = tag->Name();

            if(name == "translate") {
                return new Translate(Parser::ParseFloat(tag->Attribute("x")),
                                  Parser::ParseFloat(tag->Attribute("y")),
                                  Parser::ParseFloat(tag->Attribute("z")));
            }

            if(name == "rotate") {
                return new Rotate(Parser::ParseFloat(tag->Attribute("angle")),
                                    Parser::ParseFloat(tag->Attribute("x")),
                                     Parser::ParseFloat(tag->Attribute("y")),
                                     Parser::ParseFloat(tag->Attribute("z")));
            }

            if(name == "scale") {
                return new Scale(Parser::ParseFloat(tag->Attribute("factor")));
            }
        }

        return nullptr;
    }
} // cg_engine