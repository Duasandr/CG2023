//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H
#include "tinyxml2.h"

namespace cg_engine {

    class Transform {
    public:
        Transform() = default;
        virtual ~Transform() =default;

        static Transform *Create(tinyxml2::XMLElement *tag);

        virtual void Apply() = 0;
    };

} // cg_engine

#endif //ENGINE_TRANSFORM_H
