//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_PARSER_H
#define ENGINE_PARSER_H

namespace cg_utils {

    class Parser {
    public:
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
    };

} // cg_engine

#endif //ENGINE_PARSER_H
