//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_PARSER_H
#define ENGINE_PARSER_H

#include "Vec3f.h"
#include "tinyxml2.h"
#include "Transform.h"
#include "Window.h"

namespace cg_engine {

    /**
     * @brief EngineParser class is used to parse strings or tags into other types.
     */
    class EngineParser {
    public:
        /**
         * Parses a XML tag into a Vec3f.
         * @param tag tag to be parsed.
         * @return Vec3f containing the values of the tag.
         */
        static cg_math::Vec3f ParseVec3f(tinyxml2::XMLElement *tag);
        /**
         * @brief Parses a XML tag into a Vec3f.
         * @details Parses a XML tag into a Vec3f. The tag must have the attributes fov, near and far.
         * @param tag tag to be parsed.
         * @return
         */
        static cg_math::Vec3f ParseProjection(tinyxml2::XMLElement *tag);

        static Window* ParseWindow(tinyxml2::XMLElement *tag);


        static Transform* ParseTransform(tinyxml2::XMLElement *tag);
        static Transform* ParseTranslate(tinyxml2::XMLElement *tag);
        static Transform* ParseTranslateCurve(tinyxml2::XMLElement *tag);
        static Transform* ParseRotate(tinyxml2::XMLElement *tag);
        static Transform* ParseScale(tinyxml2::XMLElement *tag);
    };

} // cg_engine

#endif //ENGINE_PARSER_H
