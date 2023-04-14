//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_PARSER_H
#define ENGINE_PARSER_H

#include "Vec3f.h"
#include "tinyxml2.h"

namespace cg_utils {

    /**
     * @brief Parser class is used to parse strings or tags into other types.
     */
    class Parser {
    public:
        /*
        * //////////////////////////////
        * // Static methods
        * //////////////////////////////
        */

        /**
        * Parses a string into an integer.
        * @param str
        * @return
        * @throws std::domain_error when string is not a valid integer
        */
        static int ParseInt(const char *str);
        /**
        * Parses a string into a float.
        * @param str
        * @return
        * @throws std::domain_error when string is not a valid float
        */
        static float ParseFloat(const char *str);

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
    };

} // cg_engine

#endif //ENGINE_PARSER_H
