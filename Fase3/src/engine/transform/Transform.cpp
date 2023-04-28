//
// Created by Sandro Duarte on 19/03/2023.
//

#include "transform/Transform.h"
#include "transform/translate/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "utils/EngineParser.h"
#include <string>

namespace cg_engine {
    using std::string;
    using tinyxml2::XMLElement;
    using cg_engine::EngineParser;

    Transform *Transform::Create(tinyxml2::XMLElement *tag) {



        return nullptr;
    }
} // cg_engine